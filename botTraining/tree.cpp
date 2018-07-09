#include <fstream>
#include <vector>
using namespace std;

struct Tree
{
	int x;
	int y;
	int win;			// кол-во побед после прохождения по узлу
	int num;			// кол-во прохождения по узлу
	int numSun;			// кол-во дочерних узлов
	vector<Tree *> Sun; // массив сыновей
	Tree *rod;			// ссылка на родителя
};

class TreeBase
{
  public:
	int forclear;
	bool flagclear;
	Tree *tree;
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
	void writeBranch(ofstream &f, Tree *tree)
	{
		f << " " << tree->x << " ";
		f << tree->y << " ";
		f << tree->win << " ";
		f << tree->num << " ";
		f << tree->numSun;
	}
	void writeTree(ofstream &f, Tree *tree)
	{
		for (int i = 0; i < tree->numSun; i++)
			writeBranch(f, tree->Sun[i]);
			
		for (int i = 0; i < tree->numSun; i++)
			writeTree(f, tree->Sun[i]);
	}
	bool here(int x, int y)
	{
		for (int i = 0; i < tree->numSun; i++)
			if (tree->Sun[i]->x == x && tree->Sun[i]->y == y)
				return true;
		return false;
	}
	void add(int i, int j)
	{
		Tree *newtree = new Tree;
		newtree->x = i;
		newtree->y = j;
		newtree->win = 0;
		newtree->num = 1;
		newtree->numSun = 0;
		newtree->rod = tree;
		tree->Sun.push_back(newtree);
		tree->numSun++;
		tree = newtree;
	}
	TreeBase()
	{
		ifstream f("Tree.txt");
		tree = nullptr;

		tree = new Tree;
		f >> tree->x;
		f >> tree->y;
		f >> tree->win;
		f >> tree->num;
		f >> tree->numSun;
		tree->rod = nullptr;
		readTree(f, tree);

		f.close();
	}
	void saveall()
	{
		while (tree->rod != nullptr)
		{
			tree = tree->rod;
		}
		if (tree != nullptr)
		{
			ofstream f("Tree.txt");

			f << tree->x << " ";
			f << tree->y << " ";
			f << tree->win << " ";
			f << tree->num << " ";
			f << tree->numSun;
			writeTree(f, tree);

			f.close();
		}
		while (tree->rod != nullptr)
		{
			tree = tree->rod;
		}
	}
	void clearBranch(Tree *tree)
	{
		if (tree->numSun)
		{
			for (int i = 0; i < tree->numSun; i++)
				clearBranch(tree->Sun[i]);
		}
		tree->Sun.erase(tree->Sun.begin(), tree->Sun.end());
		delete tree;
		return;
	}
	void someWin(int hod, bool flag) // кто то выиграл и меняем кол-во побед
	{
		if (flag)
		{
			if (!(hod % 3))
				flag = !flag;
			while (tree->rod != nullptr)
			{
				if (!(hod % 3))
					flag = !flag;
				if (flag)
					tree->win++;

				tree = tree->rod;
				hod--;
			}
			if (flag)
				tree->win++;
		}
		else
		{
			while (tree->rod != nullptr)
			{
				if (!(hod % 3))
					flag = !flag;
				if (flag)
					tree->win++;

				tree = tree->rod;
				hod--;
			}
			if (flag)
				tree->win++;
		}
	}
};