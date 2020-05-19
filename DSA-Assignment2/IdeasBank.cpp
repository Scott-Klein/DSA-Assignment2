#include "IdeasBank.h"
#include <fstream>
#include "Constants.h"
#include "Helper.h"

bool IdeasBank::IdeaInsertion(Idea idea)
{
	if (idea.Validate())
	{
		ideas.push_back(idea);
		Index index;
		auto keywords = idea.GetKeywords();
		for (int i = 0; i < keywords.size(); i++)
		{

		}
		//indices.AVL_Insert()
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
	ifstream infile{ "ideasbank.txt" };
	int id;
	string line, proposer, content;
	vector<string> keywords;

	while (infile >> line)
	{
		if (line == "#id#")
		{
			getline(infile, line);
			id = stoi(line);
		}
		else if (line == PROPOSER_TAG)
		{
			getline(infile, line);
			TrimWhiteSpace(&line);
			proposer = line;
		}
		else if (line == "#keywords#")
		{
			getline(infile, line);
			keywords = VectoriseString(line, " ");
		}
		else if (line == "#content#")
		{
			getline(infile, line);
			TrimWhiteSpace(&line);
			content = line;
		}
		else if (line == "#end#")
		{
			Idea idea = Idea(id, proposer, content, keywords);
			ideas.push_back(idea);
		}
	}

	infile.close();

	return true;
}

