#include<WinSock2.h>
#include<iostream>
#pragma comment(lib,"ibwsock32.a")
# pragma warning(disable:4996)

using namespace std;

#define BUFFER_SIZE 512
#define PORT 8000
class Client{

	WSADATA winSocketData;

	SOCKET tcpSendFileSocket;

	struct sockaddr_in tcpRecvFileAdd;

	char recvBuffer[BUFFER_SIZE];

	int bufferSize = BUFFER_SIZE;


    public:
		Client();
		Client(string target);
		void sendData(char *data);
		void _connect();
		char* receiveData();
		int getBufferSize();
		void setBufferSize(int newBufferSize);
		~Client();
};

Client::Client(string target){
	//wsaStartup

	int wsaStartup = WSAStartup(MAKEWORD(2, 2), &winSocketData);
	if (wsaStartup != 0)
	{
		cout << "wsaStartup fail" << "\n";
        exit(0);
	}
	// cout << "WSAStartup success" << "\n";

	//Create socket

	tcpSendFileSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcpSendFileSocket == INVALID_SOCKET)
	{
		cout << "create socket fail" << WSAGetLastError() << "\n";
        exit(0);
	}
	// cout << "socket success";
	
    // Fill tcpRecvFileAdd

	tcpRecvFileAdd.sin_family = AF_INET;
	tcpRecvFileAdd.sin_addr.s_addr = inet_addr(target.c_str());
	tcpRecvFileAdd.sin_port = htons(PORT);

}

void Client::_connect(){
	// Connect 
	int flagConnect  = connect(tcpSendFileSocket, (SOCKADDR*)&tcpRecvFileAdd, sizeof(tcpRecvFileAdd));
	if (flagConnect == SOCKET_ERROR)
	{
		cout << "Connect fail " ;
        exit(0);
	}
	cout << "Connect success" << "\n";
}

char* Client::receiveData(){
	// Recv data

	int flagRecv = recv(tcpSendFileSocket, recvBuffer, bufferSize, 0);
	if (flagRecv == SOCKET_ERROR)
	{
		cout << "Recv fail";
	}
	return recvBuffer;
}

void Client::sendData(char *data){

	// Send data

	int flagSend = send(tcpSendFileSocket, data, bufferSize, 0);
	if (flagSend == SOCKET_ERROR)
	{
		cout << "send fail";
	}
	// cout << "send success" << "\n";
}

void Client::setBufferSize(int newBufferSize){
	bufferSize = newBufferSize;
}

int Client::getBufferSize(){
	return bufferSize;
}

Client::~Client(){
	// Close socket

	int flagCloseSocket = closesocket(tcpSendFileSocket);
	if (flagCloseSocket == SOCKET_ERROR)
	{
		cout << "close socket fail";
		exit(0);
	}
	cout << "close socket success" << "\n";

}