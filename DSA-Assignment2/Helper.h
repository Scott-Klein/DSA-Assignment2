#pragma once
#include <string>
#include <iostream>

using namespace std;

void TrimWhiteSpace(string* toTrim)
{
	if (toTrim->size() > 2)
	{
		*toTrim = toTrim->substr(toTrim->find_first_not_of(" \t"));
		while (toTrim->at(toTrim->length() - 1) == ' ') // Trim any number of trailing whitespace
		{
			*toTrim = toTrim->substr(0, toTrim->length() - 1);
		}
	}

}

vector<string> VectoriseString(string source, string delimiter)
{
	vector<string> result;
	TrimWhiteSpace(&source);
	int count = 0;
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