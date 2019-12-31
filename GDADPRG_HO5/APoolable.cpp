#include "APoolable.h"

APoolable::APoolable(string name): AGameObject(name)
{

}

APoolable::~APoolable()
{
	AGameObject::~AGameObject();
}

void APoolable::initialize()
{

}

void APoolable::onRelease()
{
}

void APoolable::onActivate()
{
}
