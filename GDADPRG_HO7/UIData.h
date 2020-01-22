#pragma once
#include <unordered_map>
#include <string>

using namespace std;

typedef std::unordered_map<string, int> IntTable;
typedef std::unordered_map<string, int> FloatTable;

class UIData
{
	public:
		void putInt(string key, int value);
		void putFloat(string key, float value);
		int getInt(string key, int defaultVal);
		float getFloat(string key, float defaultVal);
	private:
		IntTable intTable;
		FloatTable floatTable;
};

