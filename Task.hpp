//Own datatype-Task to store custom things -struct
#ifndef TASK_HPP
#define TASK_HPP
using namespace std;
#include<string>
#include<iostream>
#include<sstream>
//to read files we will include io.hpp
#include"../filehandling/IO.hpp"

enum class Action
{
    ENCRYPT,
    DECRYPT
};

struct Task
{
    string filepath;   // path of file
    fstream f_stream;  //content of file
    Action action;     // tell whether action will be encrypt or decrypt

    Task(fstream &&stream, Action act, string filepath):f_stream(move(stream)), action(act),filepath(filepath){} // telling what to store in what varibale

    //OTHER WAY OF DOING
    //{ filepath= filepath; action =act; }
    //&& means whenever the task is created we will take file stream, so the copy of file stream will not be created instead a temporary buffer will be created that can be passed or move  


    //SERIALISE
    string toString()
    {
        ostringstream oss;
        oss<<filepath<<","<<(action==Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");

        //suppose we have to encrypt test.txt
        // So a task of it will be created containing file path,action and file stream from IO
        // test.txt ENCRYPT f_stream
        //toString method will creat a string OF FILE PATH AND ACTION  "test.txt,ENCRYPT"
        return oss.str();
    }

    //DESERIALISE
    static Task fromString(const string &taskData)
    {
        istringstream iss(taskData);
        string filepath;
        string actionStr;

        //getline takes cin here iss is that 
        //iss will take file path till comma and put in filepath
        //iss will take action after comma and put in actionStr
        if(getline(iss, filepath,',') && getline(iss, actionStr,',') )
        {
            Action action ={ actionStr=="ENCRYPT" ? Action::ENCRYPT: Action::DECRYPT};

            //CREATING TASK
            //WILL USE FILEPATH to read file stream
            IO io(filepath);
            fstream f_stream= move(io.getFileStream());
            //move function- move ownership without referencing but actually putting it here

            if (f_stream.is_open())
            {
                //create task
                return Task(move(f_stream),action,filepath);
            }

            else
            {
                throw runtime_error("FAILED TO OPEN FILE: "+ filepath);
            }

        }
        //IF NOT ABLE TO DESRIALISE
        else
            {
                throw runtime_error("INVALID TASK DATA FORMAT: ");
            }
    }
};




#endif

//NOW WE WILL PASS THE TASK TO BE PUSHED IN QUEUE
//ENCRYPTION CLASS WILL BE CREATED WITH TASKS IN THE QUEUE CONTAINING ACTION FILE AND FILE PATH , PROCESSMANAGEMENT WILL CONSUME IT AND WILL CALL TO RUN CHILD PROCESSES (SERIALOISATION DESERIALISATION)