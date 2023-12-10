#include "NetworkManager.h"
#include "imgui_impl_opengl3_loader.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include <format>
#include <iostream>

#include "Debug.h"

NetworkManager* NetworkManager::sharedInstance = nullptr;

#define DEFAULT_IP_ADDRESS "192.168.1.134"
#define DEFAULT_PORT "8088"
#define DEFAULT_BUFFER_LEN 512

NetworkManager* NetworkManager::getInstance()
{
	return sharedInstance;
}

void NetworkManager::initialize()
{
	sharedInstance = new NetworkManager();
}

void NetworkManager::destroy()
{
	WSACleanup();
	delete sharedInstance;
}

NetworkManager::NetworkManager()
{
	WSADATA wsaData;

	int result;

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result == 0)
	{
		Debug::Log("Successfully initialized winsock \n");
		this->serverAcceptingThread = std::make_shared<ServerAcceptingThread>();
	}
	else
	{
		Debug::Log("Winsock failed. \n");
	}
}

void NetworkManager::serverStart()
{
	if(this->threadingEnabled)
	{
		this->serverAcceptingThread->start();
	}
	else
	{
		this->serverAcceptingThread->serverStart();
	}
}

void NetworkManager::clientStart()
{
	this->clientState == ClientState::ATTEMPTING_SERVER_CONNECT;
	SOCKET connectSocket = INVALID_SOCKET;
	struct addrinfo* result = nullptr, * ptr = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int iResult = getaddrinfo(DEFAULT_IP_ADDRESS, DEFAULT_PORT, &hints, &result);

	for(ptr = result; ptr != nullptr; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (connectSocket == INVALID_SOCKET) {
			wchar_t* s = nullptr;
			std::string errorMsg = std::format("Socket failed with error: {} \n", FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)s, sizeof(s), nullptr));
			printf("socket failed with error: %ld\n", WSAGetLastError());

			Debug::Log(errorMsg);
			WSACleanup();
		}

		// Connect to server.
		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if(connectSocket == INVALID_SOCKET)
	{
		Debug::Log("Unable to connect to server \n");
		WSACleanup();
	}

	//first initial send
	const char* sendMsg = "Client has successfully connected.";
	iResult = send(connectSocket, sendMsg, (int)strlen(sendMsg), 0);
	if (iResult == SOCKET_ERROR) {
		std::string errorMsg = std::format("Send failed with error: {} \n", WSAGetLastError());
		printf("send failed: %d\n", WSAGetLastError());

		Debug::Log(errorMsg);
		closesocket(connectSocket);
		WSACleanup();
	}

	printf("Bytes Sent: %ld\n", iResult);
	this->clientState = ClientState::CONNECTED_TO_SERVER;
}

NetworkManager::ServerState NetworkManager::getServerState() const
{
	return this->serverState;
}

NetworkManager::ClientState NetworkManager::getClientState() const
{
	return this->clientState;
}

void NetworkManager::setThreadingEnabled(bool flag)
{
	this->threadingEnabled = flag;
}


