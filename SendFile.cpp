// g++ SendFile.cpp -o SendFile -lws2_32
#include<WinSock2.h>
#include<iostream>
#include<regex>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)

#include "client.h"


using namespace std;

int main(int argc, char* argv[]) {
    //.. 
    regex pattern("--(.*)=(.*)");
    
    //set default command line arguments
    string target = "127.0.0.1"; 
    string path   ="./";
    int bufferSize = 512;

    //..
    if (argc > 1) {
        target = (std::string) argv[1];
    }    

    for (size_t i=2; i<argc; i++) {
        std::string paramToSearch = argv[i];
        std::smatch matches;
        if (std::regex_match(paramToSearch, matches, pattern)) {
            auto it = matches.begin();
            ++it;

            if ((*it) == "path") {
                path = *(++it);
                continue;
            }

            if ((*it) == "buffer_size") {
                bufferSize = std::stoi(*(++it));
                continue;
            }

            }
        
    }
    
    cout << "Program name:" << argv[0] <<"\n";
    cout << "target: " << target << "\n";
    cout << "path: " << path << "\n";
    cout << "buffer size: " << bufferSize << "\n";

    Client client(target);
    client._connect();
    cout << client.receiveData() << "\n";
    char data[] = "Hello Im client";
    client.sendData(data);

    system("PAUSE");
    return 0;
}