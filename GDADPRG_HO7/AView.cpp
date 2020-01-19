#include "AView.h"

AView::AView(string name) : AGameObject(name)
{

}

AView::~AView()
{
	AGameObject::~AGameObject();
}
