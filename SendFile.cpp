// g++ SendFile.cpp -o SendFile -lws2_32      SendFile.exe 127.0.0.1 --path=c:/demo/demo.txt
#include<iostream>
#include<regex>
#include <sys/stat.h>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)
#include <sys\types.h> 
#include <sys\stat.h> 
#include<fstream>
#include <algorithm>

#include "client.h"

using namespace std;

__int64 getFileSize(const char *path );

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
    
    cout << "target: " << target << "\n";
    cout << "path: " << path << "\n";
    cout << "buffer size: " << bufferSize << "\n";


    cout << "\n\n TCP \n\n";
    string  fileName = getFileName(path);
    __int64 fileSize = getFileSize(path.c_str());
    __int64 remain = fileSize;

    Client client(target);
    client._connect();    

    //.. send  bufferSize
    char strBufferSize[bufferSize.length()+1];
    strcpy(strBufferSize, bufferSize.c_str());
    client.sendData(strBufferSize);

    // send fileName
    char strFileName[fileName.length()+1];
    strcpy(strFileName, fileName.c_str());
    client.sendData(strFileName);

    //send file size
    string stringFileSize = to_string(fileSize);
    char strFileSize[stringFileSize.length()+1];
    strcpy(strFileSize, stringFileSize.c_str());
    client.sendData(strFileSize);

    int intBufferSize = stoi(bufferSize);
    client.setBufferSize(intBufferSize);
    // open file 
    ifstream file (path.c_str(), ios::in | ios::binary);
    cout << "Send " << fileName << ":  000%";

    while (true){
        char buffer[intBufferSize];
        
        file.read(buffer, min(remain,1ll*intBufferSize));
        
        client.sendData(buffer);
        // cout << buffer;
        if (file.eof()) {
            char endFile[] = "~END";
            client.sendData(endFile);
            break;

        }
        remain -= 1ll*intBufferSize;
        long double per = (long double)(fileSize - remain)/fileSize * 100.0;
        int intPer = (int) per;

        cout << "\b\b\b\b" << intPer/100 << (intPer%100)/10 << intPer%10 << "%";
      

        if (remain <= 0ll) break;
    }

    cout << "\b\b\b\b100%";
    cout << "\nSend " << fileName << " success\n";
    file.close();
    system("PAUSE");
    return 0;

}

string getFileName(string const & path){
    return path.substr(path.find_last_of("/\\") + 1);
}

__int64 getFileSize(const char * path) { 
  struct __stat64 fileStat; 
  int err = _stat64(path, &fileStat); 
  if (0 != err) return 0; 
  return fileStat.st_size; 
}