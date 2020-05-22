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
	cout << MENU_INPUT_TERM;

	string input;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, input);
	cout << MENU_WORD_SEARCH << endl;
	auto words = VectoriseString(input, " ");
	if (words.size() > 1)
	{
		WordSearch(words);
	}
	else
	{
		WordSearch(input);
	}
}

void IdeasBank::UserIndexSearch()
{
	string input;
	vector<int> resultByIndex;
	cout << "Search term : ";

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, input);

	vector<string> words = VectoriseString(input, " ");
	if (words.size() == 1)
	{
		resultByIndex = IndexSearch(input);
	}
	else
	{
		resultByIndex = IndexSearch(words);
	}
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
			if (key == "cats")
			{
				cout << "test" << endl;
			}
			if (!indices.AVL_Retrieve(key, index))
			{
				index.key = key;

				for (int j = 0; j < ideas.size(); j++)
				{
					if (ideas[j].WordSearch(index.key) && !IdInSet(index.idList, ideas[j].GetId()))
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

void IdeasBank::WordSearch(string input)
{
	for (int i = 0; i < ideas.size(); i++)
	{
		if (ideas[i].WordSearch(input))
		{
			IdeaPrint(ideas[i].GetId());
		}
	}
}

void IdeasBank::WordSearch(vector<string> words)
{
	//words.erase(words.begin() + 1);
	for (int i = 0; i < ideas.size(); i++)
	{
		if (LogicalOp(words, ideas[i]))
		{
			IdeaPrint(ideas[i].GetId());
		}
	}
}

bool IdeasBank::LogicalOp(vector<string> words, Idea idea)
{
	if (words[1] == "OR")
	{
		if (idea.WordSearch(words[0]) || idea.WordSearch(words[2]))
		{
			return true;
		}
	}
	else if (words[1] == "AND")
	{
		if (idea.WordSearch(words[0]) && idea.WordSearch(words[2]))
		{
			return true;
		}
	}
	return false;
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

vector<int> IdeasBank::IndexSearch(vector<string> words)
{
	vector<int> result;
	vector<int> setA;
	vector<int> setB;
	Index index1;
	if (words[1] == "OR")
	{
		if (indices.AVL_Retrieve(words[0], index1))
		{
			setA = index1.idList;
		}
		if (indices.AVL_Retrieve(words[2], index1))
		{
			setB = index1.idList;
		}
		for (int i = 0; i < setA.size(); i++)
		{
			if (!IsInSet(result, setA[i]))
			{
				result.push_back(setA[i]);
			}
		}
		for (int i = 0; i < setB.size(); i++)
		{
			if (!IsInSet(result, setB[i]))
			{
				result.push_back(setB[i]);
			}
		}
	}
	else if (words[1] == "AND")
	{
		if (indices.AVL_Retrieve(words[0], index1))
		{
			setA = index1.idList;
		}
		if (indices.AVL_Retrieve(words[2], index1))
		{
			setB = index1.idList;
		}
		for (int i = 0; i < setA.size(); i++)
		{
			if (IsInSet(setB, setA[i]))
			{
				result.push_back(setA[i]);
			}
		}
	}
	return result;
}

