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
