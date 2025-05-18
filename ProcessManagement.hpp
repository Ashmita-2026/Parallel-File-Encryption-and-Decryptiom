#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP
#include "Task.hpp"
#include<queue>
#include<memory>
using namespace std;


class ProcessManagement
{
    public:
        ProcessManagement();
        bool submitToQueue(unique_ptr<Task> task);
        void executeTask();


    private:
        //only process management will be able to access it 
        queue<unique_ptr<Task>> taskQueue;
        //taskqueue is storing task pointers
        // will use unique pointer to have full control over task which it has and no one can change it through reference


};


#endif

//UNIQUE POINTER
//if a unique pointer is pointing to a mem location then no other pointer can point to that mem loc.
//no double free memory
//ownership belong to only one ptr and if u have to shift ownership use "move"(file handling) so that it doesnt get copied just ownership shifted.
//scope limited(auto memory free) (auto garbage collection).