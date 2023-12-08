#pragma once
class NetworkManager
{
public:
	static NetworkManager* getInstance();
	static void initialize();
	static void destroy();

	void serverStart();
	void clientStart();

	enum ServerState
	{
		SERVER_INACTIVE,
		WAITING_CONNECTION,
		CLIENTS_CONNECTED,
		CLOSED_CONNECTION
	};

	enum ClientState
	{
		CLIENT_INACTIVE,
		ATTEMPTING_SERVER_CONNECT,
		CONNECTED_TO_SERVER,
		CLOSED
	};

	ServerState getServerState() const;
	ClientState getClientState() const;

private:
	NetworkManager();
	~NetworkManager() = default;

	NetworkManager(NetworkManager const&) {};             // copy constructor is private
	NetworkManager& operator=(NetworkManager const&) {};  // assignment operator is private*/
	static NetworkManager* sharedInstance;

	ServerState serverState = ServerState::SERVER_INACTIVE;
	ClientState clientState = ClientState::CLIENT_INACTIVE;
};

