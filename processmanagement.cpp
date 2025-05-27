#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <atomic>
#include <mutex>
#include <memory>

// Constants
#define SHM_NAME "/independent_shared_memory"
#define MAX_TASKS 1000
#define TASK_STR_SIZE 256

// Mock Task class with toString()
class Task {
public:
    std::string filePath;
    std::string action;

    Task(const std::string& path, const std::string& act) : filePath(path), action(act) {}

    std::string toString() const {
        return filePath + "|" + action;
    }
};

// Shared memory structure
struct SharedMemory {
    char tasks[MAX_TASKS][TASK_STR_SIZE];
    std::atomic<int> front;
    std::atomic<int> rear;
    std::atomic<int> size;
};

// Global semaphores
sem_t* itemsSemaphore = nullptr;
sem_t* emptySlotsSemaphore = nullptr;
std::mutex queueLock;

class ProcessManagement {
private:
    int shmFd;
    SharedMemory* sharedMem;

public:
    ProcessManagement() {
        // Initialize semaphores
        itemsSemaphore = sem_open("/items_semaphore", O_CREAT, 0666, 0);
        emptySlotsSemaphore = sem_open("/empty_slots_semaphore", O_CREAT, 0666, MAX_TASKS);

        // Set up shared memory
        shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        ftruncate(shmFd, sizeof(SharedMemory));
        sharedMem = static_cast<SharedMemory*>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0));
        sharedMem->front = 0;
        sharedMem->rear = 0;
        sharedMem->size.store(0);
    }

    ~ProcessManagement() {
        munmap(sharedMem, sizeof(SharedMemory));
        shm_unlink(SHM_NAME);
        sem_close(itemsSemaphore);
        sem_close(emptySlotsSemaphore);
        sem_unlink("/items_semaphore");
        sem_unlink("/empty_slots_semaphore");
    }

    bool submitToQueue(std::unique_ptr<Task> task) {
        sem_wait(emptySlotsSemaphore);
        std::unique_lock<std::mutex> lock(queueLock);

        if (sharedMem->size.load() >= MAX_TASKS) {
            return false;
        }

        strncpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str(), TASK_STR_SIZE);
        sharedMem->rear = (sharedMem->rear + 1) % MAX_TASKS;
        sharedMem->size.fetch_add(1);
        lock.unlock();
        sem_post(itemsSemaphore);

        int pid = fork();
        if (pid < 0) {
            return false;
        } else if (pid == 0) {
            executeTask();
            exit(0);
        }

        return true;
    }

    void executeTask() {
        sem_wait(itemsSemaphore);
        std::unique_lock<std::mutex> lock(queueLock);

        char taskStr[TASK_STR_SIZE];
        strncpy(taskStr, sharedMem->tasks[sharedMem->front], TASK_STR_SIZE);
        sharedMem->front = (sharedMem->front + 1) % MAX_TASKS;
        sharedMem->size.fetch_sub(1);
        lock.unlock();
        sem_post(emptySlotsSemaphore);

        // Mock cryption execution
        std::cout << "Executing task: " << taskStr << std::endl;
    }
};

// Example main function
int main() {
    ProcessManagement pm;

    for (int i = 0; i < 3; ++i) {
        auto task = std::make_unique<Task>("file" + std::to_string(i) + ".txt", "ENCRYPT");
        pm.submitToQueue(std::move(task));
    }

    // Wait for child processes to finish
    for (int i = 0; i < 3; ++i) {
        wait(nullptr);
    }

    return 0;
}
