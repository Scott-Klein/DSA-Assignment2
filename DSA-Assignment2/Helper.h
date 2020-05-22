#pragma once
#include <string>
#include <iostream>

using namespace std;

void TrimWhiteSpace(string* toTrim)
{
	if (toTrim->size() > 2)
	{
		*toTrim = toTrim->substr(toTrim->find_first_not_of(" \t"));
		while (toTrim->at(toTrim->length() - 1) == ' ' || toTrim->at(toTrim->length() - 1) == '.') // Trim any number of trailing whitespace
		{
			*toTrim = toTrim->substr(0, toTrim->length() - 1);
		}
	}
}

bool IdInSet(vector<int> vec, int id)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == id)
		{
			return true;
		}
	}
	return false;
}

vector<string> VectoriseString(string source, string delimiter)
{
	vector<string> result;
	TrimWhiteSpace(&source);
	string keyword;
	while (source.find_first_of(" ") != string::npos)
	{
		keyword = source.substr(0, source.find_first_of(" "));
		result.push_back(keyword);
		source = source.substr(source.find_first_of(" ")+1);
	}
	result.push_back(source); // insert the last keyword.
	return result;
}

string GetWord(string* content)
{
	string result;
	TrimWhiteSpace(content);
	auto split = content->find_first_of(" ");
	result = content->substr(0, split);
	if (split == string::npos)
	{
		*content = "";
	}
	else
	{
		*content = content->substr(split);
	}
	return result;
}

bool IsInSet(vector<int> vec, int n)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == n)
		{
			return true;
		}
	}
	return false;
}