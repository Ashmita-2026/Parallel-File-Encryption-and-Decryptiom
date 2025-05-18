//cryption.cpp will encrypt any file

#include "Cryption.hpp"
#include "../processes/Task.hpp"
//will deserialise the task and will take out the file path and wil do encryption and deacryption
#include "../fileHandling/ReadEnv.cpp"
using namespace std;

int executeCryption(const string& taskData) 

{
    Task task = Task::fromString(taskData);
    ReadEnv env;
    string envKey = env.getEnv();//read key
    int key = stoi(envKey); //convert to int
    if (task.action == Action::ENCRYPT) //if we want to encrypt
    {
        char ch;

        //IMPLEMENTING ENCRYPTION
        while (task.f_stream.get(ch)) //will read charactar one by one from file
        {
            ch = (ch + key) % 256; //we will add key to character and mod 256(value will always come in between 0-255 and ASCII character of that number will be written) any hashing can be done
            task.f_stream.seekp(-1, ios::cur); // seekp will take pointer back to h and make it current position and put character of h that we found hello -> h->8 = 8ello
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    } 


    //IMPLEMENTING DECRYPTION
    else 
    {
        char ch;
        while (task.f_stream.get(ch)) 
        {
            ch = (ch - key + 256) % 256;
            task.f_stream.seekp(-1, ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    return 0;
}