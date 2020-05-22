#include "IdeasBank.h"
#include <fstream>
#include "Constants.h"
#include "Helper.h"

bool IdeasBank::IdeaInsertion(Idea idea)
{
	if (idea.Validate())
	{
		ideas.push_back(idea);

		UpdateIndex();
		return true;
	}
	else
	{
		return false; // idea is not valid, let caller know that it wasn't inserted
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
	bool result = false;
	auto iterator = ideas.begin();
	while (iterator != ideas.end())
	{
		if (iterator->GetId() == id)
		{
			ideas.erase(iterator);
			result = true; // Item was found and deleted successfully.
		}
		iterator++;
	}

	if (result)
	{
		UpdateIndex(); // We erased something, update the index.
	}
	return result;
}

void IdeasBank::IdeaPrintAll()
{
	auto iterator = ideas.begin();
	while (iterator != ideas.end())
	{
		iterator->Print();
		iterator++;
	}
	cout << endl;
}

void IdeasBank::UserWordSearch()
{
	string input;
	cout << MENU_INPUT_TERM;
	cin >> input;
	cout << MENU_WORD_SEARCH << endl;
	for (int i = 0; i < ideas.size(); i++)
	{
		if (ideas[i].WordSearch(input))
		{
			IdeaPrint(ideas[i].GetId());
		}
	}
}

void IdeasBank::UserIndexSearch()
{
	string input;
	cout << "Search term : ";
	cin >> input;
	auto resultByIndex = IndexSearch(input);
	auto searchIndex = resultByIndex.begin();
	cout << MENU_INDEX_SEARCH << endl;
	while (searchIndex != resultByIndex.end())
	{
		IdeaPrint(*searchIndex++);
	}
}

void IdeasBank::TestTreeUpdating()
{
	Index index;
	string tested = "weather";
	indices.AVL_Retrieve(tested, index);
	cout << "\n" << tested << " is in idea ID ";
	for (int i = 0; i < index.idList.size(); i++)
	{
		cout << index.idList[i] << ", ";
	}
	cout << endl;
}

void IdeasBank::PrintIndex()
{
	indices.AVL_Print();
}

bool IdeasBank::ReadFile()
{
	ifstream infile{ "ideasbank.txt" };
	int id;
	string line, proposer, content;
	vector<string> keywords;

	while (infile >> line)
	{
		if (line == TAG_ID)
		{
			getline(infile, line);
			id = stoi(line);
		}
		else if (line == TAG_PROPOSER)
		{
			getline(infile, line);
			TrimWhiteSpace(&line);
			proposer = line;
		}
		else if (line == TAG_KEYWORDS)
		{
			getline(infile, line);
			keywords = VectoriseString(line, " ");
		}
		else if (line == TAG_CONTENTS)
		{
			getline(infile, line);
			TrimWhiteSpace(&line);
			content = line;
		}
		else if (line == TAG_END)
		{
			Idea idea = Idea(id, proposer, content, keywords);
			ideas.push_back(idea);
		}
	}

	infile.close();

	return true;
}

void IdeasBank::UpdateIndex()
{
	auto ideaIterator = ideas.begin();
	while (ideaIterator != ideas.end())
	{
		string contents = ideaIterator++->GetContent();
		while (contents != "")
		{
			Index index;
			string key = GetWord(&contents);
			if (!indices.AVL_Retrieve(key, index))
			{
				index.key = key;

				for (int j = 0; j < ideas.size(); j++)
				{
					if (ideas[j].ContentSearch(index.key) && !IdInSet(index.idList, ideas[j].GetId()))
					{
						index.idList.push_back(ideas[j].GetId());
					}
				}

				//remove any idea ids from idLists that don't exist in the bank anymore.
				auto idIt = index.idList.begin();
				while (idIt != index.idList.end())
				{
					if (!IdeaFind(*idIt))
					{
						index.idList.erase(idIt);
					}
					idIt++;
				}

				// try updating record first, if no record, insert it.
				if (!indices.AVL_Update(index.key, index))
				{
					indices.AVL_Insert(index);
				}
			}
		}
	}

}

bool IdeasBank::IdeaFind(int id)
{
	for (int i = 0; i < ideas.size(); i++)
	{
		if (id == ideas[i].GetId())
		{
			return true;
		}
	}
	return false;
}

vector<int> IdeasBank::KeywordSearch(string word)
{
	vector<int> result;
	for (int i = 0; i < ideas.size(); i++)
	{
		if (ideas[i].KeywordSearch(word))
		{
			result.push_back(ideas[i].GetId());
		}
	}
	return result;
}

vector<int> IdeasBank::IndexSearch(string word)
{
	vector<int> result;
	Index index;
	if (indices.AVL_Retrieve(word, index))
	{
		result = index.idList;
	}
	return result;
}

