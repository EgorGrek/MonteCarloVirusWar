#pragma once
#include <fstream>
#include <vector>
using namespace std;

struct Tree
{
	unsigned short int x;
	unsigned short int y;
	long double win;    // кол-во побед после прохождения по узлу
	long double num;    // кол-во прохождения по узлу
	int numSun; // кол-во дочерних узлов
	vector<Tree*> Sun; // массив сыновей
	Tree *rod; // ссылка на родителя 
};

ref class TreeBase
{
public:
	Tree * tree;
	void readBranch(ifstream &f, Tree *tree)
	{
		Tree *newtree = new Tree;
		f >> newtree->x;
		f >> newtree->y;
		f >> newtree->win;
		f >> newtree->num;
		f >> newtree->numSun;
		newtree->rod = tree;
		tree->Sun.push_back(newtree);
	}
	void readTree(ifstream &f, Tree *tree)
	{
		if (tree->numSun && f)
		{
			int i = 0;
			while (i != tree->numSun)
			{
				readBranch(f, tree);
				i++;
			}
			i = 0;
			while (i != tree->numSun)
			{
				readTree(f, tree->Sun[i]);
				i++;
			}
		}
	}
	bool here(int x, int y)
	{
		for (int i = 0; i < tree->numSun; i++)
			if (tree->Sun[i]->x == x && tree->Sun[i]->y == y)
				return true;
		return false;
	}
	TreeBase()
	{
		ifstream f("Tree.txt");
		tree = nullptr;
		
		if (f)
		{
			tree = new Tree;
			f >> tree->x;
			f >> tree->y;
			f >> tree->win;
			f >> tree->num;
			f >> tree->numSun;
			tree->rod = nullptr;
			readTree(f, tree);
		}

		f.close();
	}
};