//Header File
#ifndef IO_HPP
//io.hpp will get included in multiple classes but will get compiled only once
//it means will get included once rest will used in as reference
#define IO_HPP

#include<fstream>
#include<string>
#include<iostream>
using namespace std;

class IO
{
    public:
    //create constructor that takes file path (define it as const as file path doesnt change)
    IO(const string &file_path);
    //file path is passing by reference here

    //IO object once created goes into the memory and to remove that object we call destructor
    ~IO(); //destructor

    fstream getFileStream();//return file read to the private varibale created

    private:
    fstream file_stream;// private variable that will store the file read in the constructor returned by the fstream method

};




#endif