#include "UIData.h"

UIData::~UIData()
{
	this->textTable.clear();
}

void UIData::putInt(string key, int value)
{
	this->intTable[key] = value;
}

void UIData::putFloat(string key, float value)
{
	this->floatTable[key] = value;
}

int UIData::getInt(string key, int defaultVal)
{
	//NOTE: Don't check against null since primitive datatype is used as value
	if (this->intTable.count(key) != 0) {
		return this->intTable[key];
	}
	else {
		return defaultVal;
	}
	
}

float UIData::getFloat(string key, float defaultVal)
{
	if (this->intTable.count(key) != 0) {
		return this->floatTable[key];
	}
	else {
		return defaultVal;
	}
}

void UIData::bindUIText(UIText* uiText)
{
	this->textTable[uiText->getName()] = uiText;
}

void UIData::refreshTextFromData(string objectName, string key, string prefix)
{
	string newText = prefix + to_string(this->getInt(key, -1));
	this->textTable[objectName]->setText(newText);
}
