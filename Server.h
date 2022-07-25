#include<WinSock2.h>
#include<iostream>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)

using namespace std;

#define BUFFER_SIZE 512
#define PORT 8000
class Server{

	WSADATA winSocketData;

	SOCKET tcpRecvFileSocket;

	struct sockaddr_in tcpRecvFileAdd;
	struct sockaddr_in tcpSendFileAdd;
	int sizeOFtcpSendFileAdd = sizeof(tcpSendFileAdd);

	SOCKET acceptSocket;

	// char senderBuffer[BUFFER_SIZE];

	char recvBuffer[BUFFER_SIZE];

	int bufferSize = BUFFER_SIZE;


    public:
		Server();
		Server(string target);
		void sendData(char *data);
		void _connect();
		char* receiveData();
		int getBufferSize();
		void setBufferSize(int newBufferSize);
		~Server();
};


Server::Server() {
}
Server::Server(string target) {
	
	//wsaStartup

	int wsaStartup = WSAStartup(MAKEWORD(2, 2), &winSocketData);
	if (wsaStartup != 0)
	{
		cout << "wsaStartup fail" << "\n";
        exit(0);
	}
	// cout << "wsaStartup success" << "\n";
    
	//Fill tcpRecvFileAdd

	tcpRecvFileAdd.sin_family = AF_INET;
	tcpRecvFileAdd.sin_addr.s_addr = inet_addr(target.c_str());
	tcpRecvFileAdd.sin_port = htons(PORT);
    
}

void Server::_connect(){
	//Create socket

	tcpRecvFileSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcpRecvFileSocket == INVALID_SOCKET)
	{
		cout << "TCP Server Socket Creation failed" << WSAGetLastError() << "\n";
        exit(0);
	}

	//Blind

	int flagBlind = bind(tcpRecvFileSocket, (SOCKADDR*)&tcpRecvFileAdd, sizeof(tcpRecvFileAdd));
	if (flagBlind == SOCKET_ERROR)
	{
		cout << "blind fail";

	}
	// cout << "Bindsuccess" << "\n";

	// Listen 

	int flagListen = listen(tcpRecvFileSocket, 2);
	if (flagListen == SOCKET_ERROR)
	{
		cout << "Listen fail ";
	}
	// cout << "Listen success" << "\n";

	// Accept

	acceptSocket = accept(tcpRecvFileSocket, (SOCKADDR*)&tcpSendFileAdd,&sizeOFtcpSendFileAdd);
	if (acceptSocket == INVALID_SOCKET)
	{
		cout << "Accept fail";
	}
	cout << "Accept success" << "\n";
}

void Server::setBufferSize(int newBufferSize){
	bufferSize = newBufferSize;
}

int Server::getBufferSize(){
	return bufferSize;
}

void Server::sendData(char *data){
	int flagSend = send(acceptSocket, data, bufferSize, 0);
	if (flagSend == SOCKET_ERROR)
	{
		cout << "Send fail";
	}
	// cout << "Send success" << "\n";

}

char* Server::receiveData(){
	

	int flagRecv = recv(acceptSocket, recvBuffer, bufferSize, 0);
	if (flagRecv == SOCKET_ERROR)
	{
		cout << "Recv fail";
	}
	// cout << "Recv success" << "\n";
	
	return recvBuffer;
}

Server::~Server(){
	// Close Socket
		
	int flagCloseSocket = closesocket(tcpRecvFileSocket);

	if (flagCloseSocket == SOCKET_ERROR)
	{
		cout << "Close fail"; 
		exit(0);
	}
	cout << "Clean success" << "\n";
}