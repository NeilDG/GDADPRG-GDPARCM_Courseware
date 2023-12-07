#include "NetworkManager.h"
#include "imgui_impl_opengl3_loader.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include "Debug.h"

NetworkManager* NetworkManager::sharedInstance = nullptr;

#define DEFAULT_PORT "8088"
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
	if (iResult == 0)
	{
		Debug::Log("Successfully initialized application as SERVER. \n");
	}
	else if (iResult != 0) {
		Debug::Log("Failed to start as SERVER. Please try again. \n");
		WSACleanup();
	}
}

void NetworkManager::clientStart()
{
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


