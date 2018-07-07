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
		if (tree->numSun)
		{
			int i = 0;
			while (i != tree->numSun)
			{
				writeBranch(f, tree->Sun[i]);
				i++;
			}
			i = 0;
			while (i != tree->numSun)
			{
				writeTree(f, tree->Sun[i]);
				i++;
			}
			/* for (int j = 0; j < tree->numSun; j++)
				delete tree->Sun[j]; */
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
		forclear = 0;
		flagclear = true;
		/* nullx(tree); */
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
	~TreeBase()
	{
		saveall();
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
	void clearTree(Tree *tree) // чистим тупые ходы O потому что ЕГО тренируем и ему неудачные ходы не нужны, он их никогда не выберет
	{						   // а вот X мы неудачные ходы не убираем, потому что они могут быть в дальнейшем выбраны человеком во время игры с ним
		forclear++;
		if (!(forclear % 3))
		{
			if (!((forclear / 3) % 2))
				flagclear = false;
			else
				flagclear = true;
		}
		if (flagclear)
		{
			int max = 0;
			int index = -1;
			for (int i = 0; i < tree->numSun; i++)
				if (tree->Sun[i]->win / tree->Sun[i]->num >= max)
				{
					max = tree->Sun[i]->win / tree->Sun[i]->num;
					index = i;
				}
			if (index != -1)
			{
				for (int j = 0; j < tree->numSun; j++)
					if (j != index)
					{
						for (int i = 0; i < tree->Sun[j]->numSun; i++)
							clearBranch(tree->Sun[j]->Sun[i]);
						tree->Sun[j]->numSun = 0;
						tree->Sun[j]->Sun.erase(tree->Sun.begin(), tree->Sun.end());
					}
				clearTree(tree->Sun[index]);
			}
			forclear--;
		}
		else
			for (int i = 0; i < tree->numSun; i++)
			{
				clearTree(tree->Sun[i]);
				forclear--;
			}
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
	void nullx(Tree *tree) //стираем Х память
	{
		forclear++;
		if (!(forclear % 3))
		{
			if (!(forclear % 6))
				flagclear = false;
			else
				flagclear = true;
		}
		if (flagclear)
		{
			tree->num = 1;
			tree->win = 0;
		}
		for (int i = 0; i < tree->numSun; i++)
		{
			nullx(tree->Sun[i]);
			forclear--;
		}
	}
};