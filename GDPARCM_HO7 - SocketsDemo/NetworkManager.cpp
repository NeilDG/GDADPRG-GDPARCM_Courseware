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

void NetworkManager::serverStart()
{
	struct addrinfo* result = nullptr, * ptr = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	int iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		Debug::Log("Failed to initialize network config. Please try again. \n");
		WSACleanup();
		return;
	}
	SOCKET listenSocket = NULL;
	SOCKET clientSocket = INVALID_SOCKET;
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if(listenSocket == INVALID_SOCKET)
	{
		Debug::Log("Failed to initialize a socket. \n");
		WSACleanup();
	}

	this->serverState = ServerState::WAITING_CONNECTION;
	//bind socket
	iResult = bind(listenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));
	freeaddrinfo(result);

	if(iResult == SOCKET_ERROR)
	{
		Debug::Log("Failed to initialize a socket. \n");
		closesocket(listenSocket);
		WSACleanup();
	}
	else
	{
		Debug::Log("Successfully bound socket! \n");
	}

	if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		Debug::Log("Listening to a socket failed. \n");
		closesocket(listenSocket);
		WSACleanup();
	}

	//attempt to accept any incoming client connection. Note that accept is a blocking call!
	Debug::Log("Looking for incoming connections. \n");
	
	clientSocket = accept(listenSocket, nullptr, nullptr);
	if(clientSocket == INVALID_SOCKET)
	{
		Debug::Log("No incoming sockets accepted. \n");
		closesocket(listenSocket);
		WSACleanup();
	}

	//no longer needs a listening socket since only one client is allowed
	closesocket(listenSocket);

	//Receive messages from client until it either both of them shuts down.
	this->serverState = ServerState::CLIENTS_CONNECTED;
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

NetworkManager::NetworkManager()
{
	WSADATA wsaData;

	int result;

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result == 0)
	{
		Debug::Log("Successfully initialized winsock \n");
	}
	else
	{
		Debug::Log("Winsock failed. \n");
	}
}


