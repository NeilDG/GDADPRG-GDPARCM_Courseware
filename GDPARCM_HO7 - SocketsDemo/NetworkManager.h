#pragma once
class NetworkManager
{
public:
	static NetworkManager* getInstance();
	static void initialize();
	static void destroy();

	void serverStart();
	void clientStart();

private:
	NetworkManager();
	~NetworkManager() = default;

	NetworkManager(NetworkManager const&) {};             // copy constructor is private
	NetworkManager& operator=(NetworkManager const&) {};  // assignment operator is private*/
	static NetworkManager* sharedInstance;
};

