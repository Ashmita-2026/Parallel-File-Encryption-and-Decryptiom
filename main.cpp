#include <iostream>
#include <filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[]) {
    string directory; //FROM WHERE FILE WILL BE TAKEN
    string action;

    cout << "Enter the directory path: ";
    getline(cin, directory);

    cout << "Enter the action (encrypt/decrypt): ";
    getline(cin, action);

    try 
    {
        if (fs::exists(directory) && fs::is_directory(directory)) //is_directory methods tells whether its a directory or a file
        {
            ProcessManagement processManagement;

            for (const auto& entry : fs::recursive_directory_iterator(directory)) //recursive_directory_iterator will take out all files from directory or sub directories
            {
                if (entry.is_regular_file()) 
                {
                    string filePath = entry.path().string();
                    IO io(filePath);
                    fstream f_stream = move(io.getFileStream());

                    if (f_stream.is_open()) 
                    {
                        Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                        auto task = make_unique<Task>(move(f_stream), taskAction, filePath); //making unique pointer of type task
                        processManagement.submitToQueue(move(task));
                    } 
                    
                    else 
                    {
                        cout << "Unable to open file: " << filePath << endl;
                    }
                }
            }

            //WHEN ALL FILES ARE READ EXECUTE THEM
            processManagement.executeTask();
        } 
        else 
        {
            cout << "Invalid directory path!" << endl;
        }
    } 
    
    catch (const fs::filesystem_error& ex) //FETCH EXCEPTION BY REFERENCE
    {
        cout << "Filesystem error: " << ex.what() << endl;
    }

    return 0;
}
