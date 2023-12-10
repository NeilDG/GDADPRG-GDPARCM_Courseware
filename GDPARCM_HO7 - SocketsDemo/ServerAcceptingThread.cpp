#include "ServerAcceptingThread.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Debug.h"
#include "NetworkManager.h"
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_IP_ADDRESS "192.168.1.134"
#define DEFAULT_PORT "8088"
#define DEFAULT_BUFFER_LEN 512

ServerAcceptingThread::ServerAcceptingThread()
{
}

void ServerAcceptingThread::serverStart()
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

	if (listenSocket == INVALID_SOCKET)
	{
		Debug::Log("Failed to initialize a socket. \n");
		WSACleanup();
	}

	NetworkManager::getInstance()->serverState = NetworkManager::ServerState::WAITING_CONNECTION;
	//bind socket
	iResult = bind(listenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));
	freeaddrinfo(result);

	if (iResult == SOCKET_ERROR)
	{
		Debug::Log("Failed to initialize a socket. \n");
		closesocket(listenSocket);
		WSACleanup();
	}
	else
	{
		Debug::Log("Successfully bound socket! \n");
	}

	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		Debug::Log("Listening to a socket failed. \n");
		closesocket(listenSocket);
		WSACleanup();
	}

	//attempt to accept any incoming client connection. Note that accept is a blocking call!
	Debug::Log("Looking for incoming connections. \n");

	clientSocket = accept(listenSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET)
	{
		Debug::Log("No incoming sockets accepted. \n");
		closesocket(listenSocket);
		WSACleanup();
	}

	//no longer needs a listening socket since only one client is allowed
	closesocket(listenSocket);

	//Receive messages from client until it either both of them shuts down.
	NetworkManager::getInstance()->serverState = NetworkManager::ServerState::CLIENTS_CONNECTED;
}

void ServerAcceptingThread::run()
{
	this->serverStart();
}
