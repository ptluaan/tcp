// g++ RecvFile.cpp -o RecvFile -lws2_32
// #include<WinSock2.h>
#include<iostream>
#include<regex>
#include<fstream>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)
#include <algorithm>

#include "Server.h"
using namespace std;

int main(int argc, char* argv[]) {
    //.. 
    std::regex pattern("--(.*)=(.*)");
    
    //set default command line arguments
    std::string target = "127.0.0.1"; 
    std::string out    ="./";
    int bufferSize = 512;

    //..

    for (size_t i=1; i<argc; i++) {
        std::string paramToSearch = argv[i];
        std::smatch matches;
        if (std::regex_match(paramToSearch, matches, pattern)) {
            auto it = matches.begin();
            ++it;

            if ((*it) == "out") {
                out = *(++it);
                continue;
            }

            }
        
    }
    
    cout << "out: " << out << "\n";
    
    cout << "\n\n TCP \n\n";
    Server server(target);
    server._connect();
    
    // get buffer size
    bufferSize = stoi(server.receiveData());
    
    // get file name
    string fileName = (string) server.receiveData();
    cout << "Buffer size: " << bufferSize <<  "\n";

    // get file size
    __int64 fileSize = stoll(server.receiveData());
    __int64 remain = fileSize;

    server.setBufferSize(bufferSize);

    ofstream file ((out+fileName).c_str(), ios::out | ios::binary);

    cout << "Recv " << fileName << ":  000%";

    while (true){
        char buffer[bufferSize];
        strcpy(buffer, server.receiveData());
        if (strcmp(buffer,"~END") == 0){
            break;
        }
        file.write(buffer, min(remain, 1ll*bufferSize));
        
        remain -= bufferSize;
        if (remain <= 0ll) break;
        long double per = (long double)(fileSize - remain)/fileSize * 100.0;
        int intPer = (int) per;

        cout << "\b\b\b\b" << intPer/100 << (intPer%100)/10 << intPer%10 << "%";
        
    }

    cout << "\b\b\b\b100%";
    cout << "\nRecv " << fileName << " success\n";
  
    file.close();
	system("PAUSE");
    return 0;
}