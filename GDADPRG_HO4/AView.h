#pragma once
#include "AGameObject.h"

//has a background (sprite) and holds N UI elements.
class AView :	public AGameObject
{
	public:
		AView(string name);
		~AView();

	protected:
		AGameObject::ObjectList uiElementList;
};

