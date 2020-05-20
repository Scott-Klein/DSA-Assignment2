#pragma once

#include <vector>
#include "Idea.h"
#include "AVL_ADT.h"
#include "Index.h"

using namespace std;
class IdeasBank
{
public:
	IdeasBank()
	{
		if (ReadFile())
		{
			UpdateIndex();
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
	void UserWordSearch();
	void TestTreeUpdating();
private:
	vector<Idea> ideas;
	AvlTree<Index, string> indices;
	bool ReadFile();
	void UpdateIndex();
	bool IdeaFind(int id);

	vector<int> KeywordSearch(string word);
	vector<int> IndexSearch(string word);
};

