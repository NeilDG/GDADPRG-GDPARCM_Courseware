#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(string name) : AComponent(name, Renderer)
{
	this->type = Renderer;
	this->renderStates = sf::RenderStates::Default;
}

SpriteRenderer::~SpriteRenderer()
{
	delete this->sprite;
	delete this->targetWindow;
	AComponent::~AComponent();
}

void SpriteRenderer::assignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}

void SpriteRenderer::assignSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::setRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}

void SpriteRenderer::perform() {
	this->targetWindow->draw(*this->sprite, this->renderStates);
}
