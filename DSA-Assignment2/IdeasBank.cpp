#include "IdeasBank.h"
#include <fstream>

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
	bool fail = true;
	for (int i = 0; i < ideas.size(); i++)
	{
		if (ideas[i].GetId() == id)
		{
			ideas[i].Print();
			fail = false;
		}
	}
	if (fail)
	{
		cout << "Could not find the specified idea ID in database." << endl;
	}
}

bool IdeasBank::IdeaErase(int id)
{
	auto iterator = ideas.begin();
	while (iterator != ideas.end())
	{
		if (iterator->GetId() == id)
		{
			ideas.erase(iterator);
			return true; // Item was found and deleted successfully.
		}
		iterator++;
	}
	// Item not found, nothing was erased.
	return false;
}

void IdeasBank::IdeaPrintAll()
{
	auto iterator = ideas.begin();
	while (iterator != ideas.end())
	{
		iterator->Print();
		iterator++;
	}
}

bool IdeasBank::ReadFile()
{
	ifstream infile{ "ideas.txt" };

	if (infile)
	{
		
	}

	return false;
}
