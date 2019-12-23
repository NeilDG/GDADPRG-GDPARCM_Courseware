#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>

using namespace std;
namespace HO2 {
	class BaseRunner : private sf::NonCopyable
	{
	public:
		BaseRunner();
		void run();


	private:
		static const sf::Time	TimePerFrame;
		sf::RenderWindow		window;
		vector <Entity> entityList;
		void render();
		void processEvents();
		void update(sf::Time elapsedTime);
	};
}

