// g++ RecvFile.cpp -o RecvFile -lws2_32
#include<WinSock2.h>
#include<iostream>
#include<regex>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)

#define PORT 8000

int main(int argc, char* argv[]) {
    //.. 
    std::regex pattern("--(.*)=(.*)");
    
    //set default command line arguments
    std::string target = "127.0.0.1"; 
    std::string out    ="./";
    int bufferSize = 512;

    //..
    if (argc > 1) {
        target = (std::string) argv[1];
    }    

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
    
    std::cout << "Program name:" << argv[0] <<"\n";
    std::cout << "out: " << out << "\n";

    return 0;
}