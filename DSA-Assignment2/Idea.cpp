#include "Idea.h"

bool Idea::WordSearch(string word)
{
	for (int i = 0; i < keywords.size(); i++)
	{
		if (keywords[i] == word)
		{
			return true;
		}
	}

	if (content.find(word)!= string::npos)
	{
		return true;
	}

	return false;
}

bool Idea::Validate()
{
	if (this->id > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Idea::Test()
{
	this->keywords.push_back("smartphone");
	this->keywords.push_back("tablet");
	this->content = "Every smartphone or tablet is equipped with a detachable styles, which has built in earphone and microphone (possibley even a camera), wirelessly connected to its body.";
	this->proposer = "Dongmo Zhang";
}

void Idea::Print()
{
	cout << "idea id: " << id << endl;
	cout << "proposer: " << proposer << endl;
	cout << "keywords: ";
	for (int i = 0; i < keywords.size(); i++)
	{
		cout << keywords[i];
		if (i != keywords.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl << content << endl;
}

bool Idea::KeywordSearch(string word)
{
	bool result = false;
	for (int i = 0; i < keywords.size(); i++)
	{
		if (keywords[i] == word)
		{
			result = true;
		}
	}
	return result;
}

bool Idea::ContentSeaerch(string word)
{
	bool result = false;
	if (content.find(word) != string::npos)
	{
		result = true;
	}
	return result;
}
