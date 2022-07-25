// g++ SendFile.cpp -o SendFile -lws2_32
#include<iostream>
#include<regex>
#include <sys/stat.h>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)

#include "client.h"


using namespace std;

string getFileName(string const & path);

int main(int argc, char* argv[]) {
    //.. 
    regex pattern("--(.*)=(.*)");
    
    //set default command line arguments
    string target = "127.0.0.1"; 
    string path   ="";
    string bufferSize = "512";

    //..
    if (argc > 1) {
        target = (std::string) argv[1];
    }    

    for (size_t i=0; i<argc; i++) {
        string paramToSearch = argv[i];
        smatch matches;
        if (std::regex_match(paramToSearch, matches, pattern)) {
            auto it = matches.begin();
            ++it;

            if ((*it) == "path") {
                path = *(++it);
                continue;
            }

            if ((*it) == "buffer_size") {
                bufferSize = *(++it);
                // bufferSize = std::stoi(*(++it));
                continue;
            }

            }
        
    }

    if (path ==""){
        cout << "No File"; 
        return 0;
    }
    
    cout << "Program name:" << argv[0] <<"\n";
    cout << "target: " << target << "\n";
    cout << "path: " << path << "\n";
    cout << "buffer size: " << bufferSize << "\n";

    cout << "\n\n TCP \n\n";
    string fileName = getFileName(path);

    Client client(target);
    client._connect();
    cout << client.receiveData() << "\n";
    
    //.. send  bufferSize
    char data1[bufferSize.length()+1];
    strcpy(data1, bufferSize.c_str());
    cout << data1 << "\n";
    client.sendData(data1);

    // send fileName
    char data2[fileName.length()+1];
    strcpy(data2, fileName.c_str());
    cout << data2 << "\n";
    client.sendData(data2);

    system("PAUSE");
    return 0;
}

string getFileName(string const & path){
    return path.substr(path.find_last_of("/\\") + 1);
}