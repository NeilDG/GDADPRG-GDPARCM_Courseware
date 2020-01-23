#pragma once
#include <unordered_map>
#include <string>
#include "UIButton.h"
#include "UIText.h"

using namespace std;

typedef std::unordered_map<string, int> IntTable;
typedef std::unordered_map<string, int> FloatTable;

typedef std::unordered_map<std::string, UIText*> TextTable;
typedef std::unordered_map<std::string, UIButton*> ButtonTable;

class UIData
{
	public:
		~UIData();
		void putInt(string key, int value);
		void putFloat(string key, float value);
		int getInt(string key, int defaultVal);
		float getFloat(string key, float defaultVal);

		void bindUIText(UIText* uiText);
		void refreshTextFromData(string objectName, string key, string prefix = "");
	
private:
		IntTable intTable;
		FloatTable floatTable;

		TextTable textTable;
};

