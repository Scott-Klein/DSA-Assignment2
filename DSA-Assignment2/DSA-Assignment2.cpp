// DSA-Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Idea.h"
#include <fstream>
#include <string>
#include "IdeasBank.h"
#include "Constants.h"

int Menu();

int main()
{
    IdeasBank bank = IdeasBank();
    
	while (true)
	{
		int operation = Menu();
		switch (operation)
		{
		case 1:
			bank.IdeaPrintAll();
			break;
		case 2:
			bank.PrintIndex();
			break;
		case 3:
			bank.UserWordSearch();
			break;
		case 4:
			bank.UserIndexSearch();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << MENU_DEFAULT << endl;
			break;
		}
	}
}

int Menu()
{
	cout << endl;
	cout << MENU_1 << endl;
	cout << MENU_2 << endl;
	cout << MENU_3 << endl;
	cout << MENU_4 << endl;
	cout << MENU_5 << endl;
	cout << MENU_6 << endl;
	int input;
	cin >> input;
	return input;
}