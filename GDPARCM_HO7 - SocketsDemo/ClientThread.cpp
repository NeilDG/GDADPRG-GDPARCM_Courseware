#include "ClientThread.h"
#include <format>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "ChatScreen.h"
#include "Debug.h"
#include "EventBroadcaster.h"
#include "NetworkManager.h"
#pragma comment(lib, "Ws2_32.lib")

ClientThread::ClientThread()
{
}

void ClientThread::clientStart()
{
	NetworkManager::getInstance()->clientState == NetworkManager::ClientState::ATTEMPTING_SERVER_CONNECT;
	SOCKET connectSocket = INVALID_SOCKET;
	struct addrinfo* result = nullptr, * ptr = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int iResult = getaddrinfo(DEFAULT_IP_ADDRESS, DEFAULT_PORT, &hints, &result);

	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
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

	if (connectSocket == INVALID_SOCKET)
	{
		Debug::Log("Unable to connect to server \n");
		WSACleanup();
		NetworkManager::getInstance()->clientState == NetworkManager::ClientState::CLIENT_INACTIVE;
		return;
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
		NetworkManager::getInstance()->clientState = NetworkManager::ClientState::CLIENT_INACTIVE;
		return;
	}

	printf("[Client] Bytes Sent: %ld\n", iResult);
	NetworkManager::getInstance()->clientState = NetworkManager::ClientState::CONNECTED_TO_SERVER;

	// // shutdown the connection since no more data will be sent
	// iResult = shutdown(connectSocket, SD_SEND);
	// if (iResult == SOCKET_ERROR) {
	// 	printf("shutdown failed with error: %d\n", WSAGetLastError());
	// 	closesocket(connectSocket);
	// 	WSACleanup();
	// 	return;
	// }

	char recvbuf[DEFAULT_BUFFER_LEN];
	int recvbuflen = DEFAULT_BUFFER_LEN;
	// Receive until the peer closes the connection
	do {

		iResult = recv(connectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			std::shared_ptr<Parameters> params = std::make_shared<Parameters>(EventNames::ON_RECEIVED_MSG);
			params->encodeString(ParameterKeys::MSG_KEY, recvbuf);
			params->encodeInt(ParameterKeys::SOURCE_KEY, 0);

			EventBroadcaster::getInstance()->broadcastEventWithParams(EventNames::ON_RECEIVED_MSG, params);
			printf("[Client] Bytes received: %d\n", iResult);
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	// cleanup
	closesocket(connectSocket);
	WSACleanup();
	NetworkManager::getInstance()->clientState = NetworkManager::ClientState::CLIENT_INACTIVE;
}

void ClientThread::run()
{
	this->clientStart();
}
