#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	BaseRunner();
	void run();


private:
	static const sf::Time	TIME_PER_FRAME;
	sf::Time ticks;

	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};


