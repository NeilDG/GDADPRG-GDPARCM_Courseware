#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;

	BaseRunner();
	void run();

private:
	enum StreamingType {BATCH_LOAD = 0, SINGLE_STREAM = 1};
	const float STREAMING_LOAD_DELAY = 500.0f;

	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;
	
	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};


