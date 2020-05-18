#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Idea
{
public:
	Idea()
	{
		hash<time_t> idHash;
		id = idHash(time(NULL));
		id = abs(id);
	}

	int GetId()
	{
		return this->id;
	}

	bool WordSearch(string word);
	bool Validate();

	//Delete this function before submitting
	void Test();
	void Print();
private:
	int id;
	string proposer;
	vector<string> keywords;
	string content;

	bool KeywordSearch(string word);
	bool ContentSeaerch(string word);
};

