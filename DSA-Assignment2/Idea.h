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

	Idea(int id)
	{
		this->id = id;
	}

	Idea(int id, string proposer, string content, vector<string> keywords)
	{
		this->id = id;
		this->proposer = proposer;
		this->content = content;
		this->keywords = keywords;
	}

	int GetId()
	{
		return this->id;
	}
	
	string GetContent()
	{
		return this->content;
	}

	

	void SetProposer(string inProposer)
	{
		this->proposer = inProposer;
	}

	void SetKeywords(vector<string> inVector)
	{
		this->keywords = inVector;
	}
	vector<string> GetKeywords()
	{
		return this->keywords;
	}
	void SetContent(string inContent)
	{
		this->content = inContent;
	}

	bool Validate();
	bool WordSearch(string word);
	bool ContentSearch(string word);
	bool KeywordSearch(string word);
	void Print();
private:
	int id;
	string proposer;
	vector<string> keywords;
	string content;

	
	
};

