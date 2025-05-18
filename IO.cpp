//declare functions
#include<iostream>
#include<fstream>
using namespace std;
#include "IO.hpp"

//implementing the constructor of IO class
//constructor will ask file path to read files and will store that in varibale


IO::IO(const string &file_path)
{
    //input/output,ios, stream read write in binary
    file_stream.open(file_path,ios::in | ios::out | ios::binary);
    if(!file_stream.is_open())
    {
        cout<<"Unable To Open File"<<file_path<<endl;
    }
}


fstream IO::getFileStream()
{
    return move(file_stream);
}


//destructor
IO::~IO()
{
    //IO object out of memory,then close it.
    if(file_stream.is_open())
    {
        file_stream.close();
    }
}