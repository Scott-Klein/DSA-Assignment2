#pragma once

#include <vector>
#include "Idea.h"
using namespace std;
class IdeasBank
{
public:
	IdeasBank()
	{
		if (ReadFile())
		{
			cout << "Read files from .txt" << endl;
		}
		else
		{
			cout << "Failed to read files from .txt" << endl;
		}
	}

	bool IdeaInsertion(Idea idea);
	void IdeaPrint(int id);
	bool IdeaErase(int id);
	void IdeaPrintAll();

private:
	vector<Idea> ideas;

	bool ReadFile();
};

