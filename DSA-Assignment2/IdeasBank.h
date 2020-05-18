#pragma once

#include <vector>
#include "Idea.h"
using namespace std;
class IdeasBank
{
public:
	IdeasBank()
	{

	}

	bool IdeaInsertion(Idea idea);
	void IdeaPrint(int id);
	bool IdeaErase(int id);
	void IdeaPrintAll();

private:
	vector<Idea> ideas;
};

