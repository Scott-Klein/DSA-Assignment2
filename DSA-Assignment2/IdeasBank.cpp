#include "IdeasBank.h"

bool IdeasBank::IdeaInsertion(Idea idea)
{
	if (idea.Validate())
	{
		ideas.push_back(idea);
		return true;
	}
	else
	{
		return false;
	}
}

void IdeasBank::IdeaPrint(int id)
{
	for (int i = 0; i < ideas.size(); i++)
	{
		if (ideas[i].GetId() == id)
		{
			ideas[i].Print();
		}
	}
	cout << "idea id: " << this-
}

bool IdeasBank::IdeaErase(int id)
{
	return false;
}

void IdeasBank::IdeaPrintAll()
{
}
