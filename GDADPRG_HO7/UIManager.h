#pragma once
#include <unordered_map>
#include "UIText.h"
#include "UIButton.h"
#include "UIData.h"

typedef std::unordered_map<std::string, UIData*> DataTable;

class UIManager
{
	public: 
		static const string SCORE_UI_KEY;

		static UIManager* getInstance();

		UIData* getUIData(string name);
		UIData* storeData(string name);
		void removeData(string name);

	private:
		UIManager() {};
		UIManager(UIManager const&) {};             // copy constructor is private
		UIManager& operator=(UIManager const&) {};  // assignment operator is private
		static UIManager* sharedInstance;

		DataTable dataTable;


};

