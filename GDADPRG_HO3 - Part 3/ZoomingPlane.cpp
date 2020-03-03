#include "ZoomingPlane.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "BaseRunner.h"
#include "ZoomingComponent.h"

ZoomingPlane::ZoomingPlane(string name) : AGameObject(name) {

}

ZoomingPlane::~ZoomingPlane() {
	AGameObject::~AGameObject();
}

void ZoomingPlane::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTextureAt(TextureManager::AssetType::Raptor, 0));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(BaseRunner::WINDOW_WIDTH - 400, BaseRunner::WINDOW_HEIGHT + 100);
	this->sprite->move(rand() % 500 - rand() % 500, 0);

	ZoomingComponent* zoomingComponent = new ZoomingComponent("ZoomComponent");
	this->attachComponent(zoomingComponent);
}

void ZoomingPlane::setDelay(float seconds)
{
	ZoomingComponent* zoomingComponent = (ZoomingComponent*) this->findComponentByName("ZoomComponent");
	zoomingComponent->setDelay(seconds);
}
