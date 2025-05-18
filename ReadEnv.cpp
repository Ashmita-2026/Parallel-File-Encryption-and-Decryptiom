//while encrypt and decrypt in same file
//READING ENVIRONMENT FLE
#include<iostream>
#include<string>
#include<fstream>
#include"IO.hpp"
#include<sstream>
using namespace std;

class ReadEnv
{
    public:
    string getEnv()
    {
        string env_path=".env";
        // why not../../..env?
        IO io(env_path);//creating io class to give file path and open file
        fstream f_stream = io.getFileStream();
        //stringstream class
        stringstream buffer;
        buffer<<f_stream.rdbuf();
        string content=buffer.str();
        return content;
    }

};
