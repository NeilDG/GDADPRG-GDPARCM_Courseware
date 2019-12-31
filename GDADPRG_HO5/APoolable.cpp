#include "APoolable.h"

APoolable::APoolable(string name): AGameObject(name)
{

}

APoolable::~APoolable()
{
	AGameObject::~AGameObject();
}
