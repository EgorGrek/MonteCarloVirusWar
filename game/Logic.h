#pragma once
#include "Tree.h"
#include <conio.h>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Map
{
private:
	void DrawFiled(Graphics^  g, int i, int j)
	{
		System::Drawing::Pen ^p = gcnew System::Drawing::Pen(System::Drawing::Color::Black);

		if (map[i][j] == 1)
		{
			g->DrawString("X", gcnew System::Drawing::Font("Times New Roman", 14), System::Drawing::Brushes::Blue, 30 * j + 5, 30 * i + 5);
		}
		else if (map[i][j] == 2)
		{
			g->DrawString("O", gcnew System::Drawing::Font("Times New Roman", 14), System::Drawing::Brushes::Red, 30 * j + 5, 30 * i + 5);
		}
		else if (map[i][j] == 3)
		{
			g->FillRectangle(System::Drawing::Brushes::Blue, 30 * j, 30 * i, 30, 30);
			g->DrawString("O", gcnew System::Drawing::Font("Times New Roman", 14), System::Drawing::Brushes::Black, 30 * j + 5, 30 * i + 5);
		}
		else if (map[i][j] == 4)
		{
			g->FillRectangle(System::Drawing::Brushes::Red, 30 * j, 30 * i, 30, 30);
			g->DrawString("X", gcnew System::Drawing::Font("Times New Roman", 14), System::Drawing::Brushes::Black, 30 * j + 5, 30 * i + 5);
		}
	}
public:
	int **map;
	bool **mapactiv;
	Map()
	{
		mapactiv = new bool*[10];
		map = new int*[10];
		for (int i = 0; i < 10; i++)
		{
			map[i] = new int[10];
			mapactiv[i] = new bool[10];
			for (int j = 0; j < 10; j++)
			{
				map[i][j] = 0;
				mapactiv[i][j] = 0;
			}
		}
	}
	void Activation(int igrok)
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				mapactiv[i][j] = 0;

		if (igrok == 1 && map[0][0] == 0)
		{
			mapactiv[0][0] = 1;// игра начинается для Х с вехнего левого угла
			return;
		}
		else if (igrok == 2 && map[9][9] == 0)
		{
			mapactiv[9][9] = 1;// игра начинается для О с нижнего правого угла
			return;
		}
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (map[i][j] == igrok)
				{
					if (j - 1 >= 0)mapactiv[i][j - 1] = 1;
					if (j + 1 < 10)mapactiv[i][j + 1] = 1;
					if (i + 1 < 10)mapactiv[i + 1][j] = 1;
					if (i - 1 >= 0)mapactiv[i - 1][j] = 1;
					if (i + 1 < 10 && j - 1 >= 0)mapactiv[i + 1][j - 1] = 1;
					if (i + 1 < 10 && j + 1 < 10)mapactiv[i + 1][j + 1] = 1;
					if (i - 1 >= 0 && j - 1 >= 0)mapactiv[i - 1][j - 1] = 1;
					if (i - 1 >= 0 && j + 1 < 10)mapactiv[i - 1][j + 1] = 1;
				}


		for (int k = 0; k < 10; k++)
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map[i][j] == igrok + 2 && mapactiv[i][j] == 1)
					{

						if (j - 1 >= 0)mapactiv[i][j - 1] = 1;
						if (j + 1 < 10)mapactiv[i][j + 1] = 1;
						if (i + 1 < 10)mapactiv[i + 1][j] = 1;
						if (i - 1 >= 0)mapactiv[i - 1][j] = 1;
						if (i + 1 < 10 && j - 1 >= 0)mapactiv[i + 1][j - 1] = 1;
						if (i + 1 < 10 && j + 1 < 10)mapactiv[i + 1][j + 1] = 1;
						if (i - 1 >= 0 && j - 1 >= 0)mapactiv[i - 1][j - 1] = 1;
						if (i - 1 >= 0 && j + 1 < 10)mapactiv[i - 1][j + 1] = 1;
					}


		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (map[i][j] == igrok || map[i][j] == 3 || map[i][j] == 4)
					mapactiv[i][j] = 0;
	}
	bool Hod(int i, int j, int igrok, Graphics^  g)
	{
		Activation(igrok);
		if (!mapactiv[i][j]) return 0;
		if (map[i][j] == 0)
		{
			map[i][j] += igrok;
		}
		else
		{
			if (igrok == 1)
				map[i][j] = 3;
			else
				map[i][j] = 4;
		}
		DrawFiled(g, i, j);
		return 1;
	}
	void DrawMap(Graphics^  g)
	{
		System::Drawing::Pen ^p = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				g->DrawRectangle(p, 30 * j, 30 * i, 30, 30);
			}
	}
};
ref class Bot
{
public:
	TreeBase ^MonteBot;
	Bot()
	{
		MonteBot = gcnew TreeBase;
	}
	~Bot()
	{
		delete MonteBot;
	}
	void botchoseO(Map ^map, Graphics^  g)
	{
		int maxWinrate = 0;
		int numMaxSun = -1;
		for (int i = 0; i < MonteBot->tree->numSun; i++)
			if (MonteBot->tree->Sun[i]->win / MonteBot->tree->Sun[i]->num > maxWinrate)
			{
				maxWinrate = MonteBot->tree->Sun[i]->win / MonteBot->tree->Sun[i]->num;
				numMaxSun = i;
			}
		if (maxWinrate < 0.01)
		{
			if (botchoseO2(map, g))
				return;
		}
		if (numMaxSun != -1)
		{
			map->Hod(MonteBot->tree->Sun[numMaxSun]->x, MonteBot->tree->Sun[numMaxSun]->y, 2, g);
			MonteBot->tree->Sun[numMaxSun]->num++;
			MonteBot->tree = MonteBot->tree->Sun[numMaxSun];
			return;
		}
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (map->mapactiv[i][j])
				{
					map->Hod(i, j, 2, g);
					Tree *newtree = new Tree;
					newtree->x = i;
					newtree->y = j;
					newtree->win = 0;
					newtree->num = 1;
					newtree->numSun = 0;
					newtree->rod = MonteBot->tree;
					MonteBot->tree->Sun.push_back(newtree);
					MonteBot->tree->numSun++;
					MonteBot->tree = newtree;

				}
	}
	bool botchoseO2(Map ^map, Graphics^  g)
	{
		int numO = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (map->map[i][j] == 2)
					numO++;
		if (numO <= 3)
		{
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
						if (j - 1 < 0 || (map->map[i][j - 1] != 1 && map->map[i][j - 1] != 3))
							if (j + 1 >= 10 || (map->map[i][j + 1] != 1 && map->map[i][j + 1] != 3))
								if (i + 1 >= 10 || (map->map[i + 1][j] != 1 && map->map[i + 1][j] != 3))
									if (i - 1 < 0 || (map->map[i - 1][j] != 1 && map->map[i - 1][j] != 3))
										if (i + 1 >= 10 || j - 1 < 0 || (map->map[i + 1][j - 1] != 1 && map->map[i + 1][j - 1] != 3))
											if (i + 1 >= 10 || j + 1 >= 10 || (map->map[i + 1][j + 1] != 1 && map->map[i + 1][j + 1] != 3))
												if (i - 1 < 0 || j - 1 < 0 || (map->map[i - 1][j - 1] != 1 && map->map[i - 1][j - 1] != 3))
													if (i - 1 < 0 || j + 1 >= 10 || (map->map[i - 1][j + 1] != 1 && map->map[i - 1][j + 1] != 3))
													{
														if (!MonteBot->here(i, j))
														{
															map->Hod(i, j, 2, g);
															Tree *newtree = new Tree;
															newtree->x = i;
															newtree->y = j;
															newtree->win = 0;
															newtree->num = 1;
															newtree->numSun = 0;
															newtree->rod = MonteBot->tree;
															MonteBot->tree->Sun.push_back(newtree);
															MonteBot->tree->numSun++;
															MonteBot->tree = newtree;
															return true;
														}
													}

			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
						if (j - 1 < 0 || map->map[i][j - 1] != 3)
							if (j + 1 >= 10 || map->map[i][j + 1] != 3)
								if (i + 1 >= 10 || map->map[i + 1][j] != 3)
									if (i - 1 < 0 || map->map[i - 1][j] != 3)
										if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] != 3)
											if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] != 3)
												if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] != 3)
													if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] != 3)
													{
														if (!MonteBot->here(i, j))
														{
															map->Hod(i, j, 2, g);
															Tree *newtree = new Tree;
															newtree->x = i;
															newtree->y = j;
															newtree->win = 0;
															newtree->num = 1;
															newtree->numSun = 0;
															newtree->rod = MonteBot->tree;
															MonteBot->tree->Sun.push_back(newtree);
															MonteBot->tree->numSun++;
															MonteBot->tree = newtree;
															return true;
														}
													}
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
					{
						if (!MonteBot->here(i, j))
						{
							map->Hod(i, j, 2, g);
							Tree *newtree = new Tree;
							newtree->x = i;
							newtree->y = j;
							newtree->win = 0;
							newtree->num = 1;
							newtree->numSun = 0;
							newtree->rod = MonteBot->tree;
							MonteBot->tree->Sun.push_back(newtree);
							MonteBot->tree->numSun++;
							MonteBot->tree = newtree;
							return true;
						}
					}
			for (int i = 9; i >= 0; i--)
				for (int j = 9; j >= 0; j--)
					if (map->mapactiv[i][j] && map->map[i][j] == 1)
					{
						if (!MonteBot->here(i, j))
						{
							map->Hod(i, j, 2, g);
							Tree *newtree = new Tree;
							newtree->x = i;
							newtree->y = j;
							newtree->win = 0;
							newtree->num = 1;
							newtree->numSun = 0;
							newtree->rod = MonteBot->tree;
							MonteBot->tree->Sun.push_back(newtree);
							MonteBot->tree->numSun++;
							MonteBot->tree = newtree;
							return true;
						}
					}
		}
		else
		{
			for (int i = 9; i >= 0; i--)
				for (int j = 9; j >= 0; j--)
					if (map->mapactiv[i][j] && map->map[i][j] == 1)
					{
						if (!MonteBot->here(i, j))
						{
							map->Hod(i, j, 2, g);
							Tree *newtree = new Tree;
							newtree->x = i;
							newtree->y = j;
							newtree->win = 0;
							newtree->num = 1;
							newtree->numSun = 0;
							newtree->rod = MonteBot->tree;
							MonteBot->tree->Sun.push_back(newtree);
							MonteBot->tree->numSun++;
							MonteBot->tree = newtree;
							return true;
						}
					}
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
						if (j - 1 < 0 || map->map[i][j - 1] == 1)
							if (j + 1 >= 10 || map->map[i][j + 1] == 1)
								if (i + 1 >= 10 || map->map[i + 1][j] == 1)
									if (i - 1 < 0 || map->map[i - 1][j] == 1)
										if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] == 1)
											if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] == 1)
												if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] == 1)
													if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] == 1)
													{
														if (!MonteBot->here(i, j))
														{
															map->Hod(i, j, 2, g);
															Tree *newtree = new Tree;
															newtree->x = i;
															newtree->y = j;
															newtree->win = 0;
															newtree->num = 1;
															newtree->numSun = 0;
															newtree->rod = MonteBot->tree;
															MonteBot->tree->Sun.push_back(newtree);
															MonteBot->tree->numSun++;
															MonteBot->tree = newtree;
															return true;
														}
													}
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
						if (j - 1 < 0 || map->map[i][j - 1] != 3)
							if (j + 1 >= 10 || map->map[i][j + 1] != 3)
								if (i + 1 >= 10 || map->map[i + 1][j] != 3)
									if (i - 1 < 0 || map->map[i - 1][j] != 3)
										if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] != 3)
											if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] != 3)
												if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] != 3)
													if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] != 3)
													{
														if (!MonteBot->here(i, j))
														{
															map->Hod(i, j, 2, g);
															Tree *newtree = new Tree;
															newtree->x = i;
															newtree->y = j;
															newtree->win = 0;
															newtree->num = 1;
															newtree->numSun = 0;
															newtree->rod = MonteBot->tree;
															MonteBot->tree->Sun.push_back(newtree);
															MonteBot->tree->numSun++;
															MonteBot->tree = newtree;
															return true;
														}
													}
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->mapactiv[i][j] && !map->map[i][j])
					{
						if (!MonteBot->here(i, j))
						{
							map->Hod(i, j, 2, g);
							Tree *newtree = new Tree;
							newtree->x = i;
							newtree->y = j;
							newtree->win = 0;
							newtree->num = 1;
							newtree->numSun = 0;
							newtree->rod = MonteBot->tree;
							MonteBot->tree->Sun.push_back(newtree);
							MonteBot->tree->numSun++;
							MonteBot->tree = newtree;
							return true;
						}
					}
		}
		return false;
	}
	void someWin(int hod, bool flag) // кто то выиграл и меняем кол-во побед
	{
		if (flag)
		{
			if (!(hod % 3))
				flag = !flag;
			while (MonteBot->tree->rod != nullptr)
			{
				if (!(hod % 3))
					flag = !flag;
				if(flag)
					MonteBot->tree->win++;

				MonteBot->tree = MonteBot->tree->rod;
				hod--;
			}
			if (flag)
				MonteBot->tree->win++;
		}
		else
		{
			while (MonteBot->tree->rod != nullptr)
			{
				if (!(hod % 3))
					flag = !flag;
				if (flag)
					MonteBot->tree->win++;

				MonteBot->tree = MonteBot->tree->rod;
				hod--;
			}
			if (flag)
				MonteBot->tree->win++;
		}
	}
};
ref class GameLogic
{
public:
	Map ^map;
	Bot ^lesha;
	int hod;
	int igrok; // 1 - X, 2 - O
	bool botO;
	bool GOver;
	void botOvkl(Button ^button2, System::Windows::Forms::Label^ label2, Graphics^ e)
	{
		if (botO)
		{
			botO = false;
			button2->BackColor = Color::Honeydew;
			button2->Text = "Включить бота";
		}
		else
		{
			botO = true;
			button2->BackColor = Color::Gray;
			button2->Text = "Выключить бота";
			while (igrok == 2)
			{
				lesha->botchoseO(map, e);
				endhod(label2);
			}
		}
	}
	bool GameOver(System::Windows::Forms::Label^ label2)
	{
		if (hod <= 20)
			return false;
		else
		{
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (map->map[i][j] == 1)
					{
						for (int i = 0; i < 10; i++)
							for (int j = 0; j < 10; j++)
								if (map->map[i][j] == 2)
								{
									for (int i = 0; i < 10; i++)
										for (int j = 0; j < 10; j++)
											if (map->mapactiv[i][j])
												return false;

									if (igrok == 1)
										label2->Text = "X LOSE";
									else
										label2->Text = "O LOSE";
									lesha->someWin(hod, 0);
									igrok = 0;
									GOver = true;
									return true;
								}
						label2->Text = "O LOSE";
						lesha->someWin(hod, 1);
						igrok = 0;
						GOver = true;
						return true;
					}
			label2->Text = "X LOSE";
			lesha->someWin(hod, 1);
			igrok = 0;
			GOver = true;
			return true;
		}
	}
	void endhod(System::Windows::Forms::Label^ label2)
	{
		hod++;
		if (!(hod % 3))
		{
			if (igrok == 1)
			{
				igrok = 2;
			}
			else
			{
				igrok = 1;
			}
		}
		map->Activation(igrok);
		if (!GameOver(label2))
		{
			if (igrok == 1)
				label2->Text = "Ход X";
			else
				label2->Text = "Ход O";
		}
	}
	GameLogic()
	{
		map = gcnew Map;
		lesha = gcnew Bot;
		hod = 0;
		igrok = 1;
		botO = false;
		GOver = false;
	}
	~GameLogic()
	{
		delete map;
		delete lesha;
	}
	void StartGame(System::Windows::Forms::PaintEventArgs^ e, System::Windows::Forms::Label^ label2)
	{
		delete map;
		map = gcnew Map;
		map->DrawMap(e->Graphics);
		igrok = 1;
		GOver = false;
		hod = 0;
		label2->Text = "Ход X";
	}
	void Hod(Graphics^ e, System::Windows::Forms::Label^ label, int i, int j)
	{
		if (!GOver)
		{
			i /= 30;
			j /= 30;
			if (map->Hod(i, j, igrok, e))
			{
				if (i == 0 && j == 0)
				{
					endhod(label);
					return;
				}
				if (lesha->MonteBot->here(i, j))
				{
					for (int k = 0; k < lesha->MonteBot->tree->numSun; k++)
						if (lesha->MonteBot->tree->Sun[k]->x == i && lesha->MonteBot->tree->Sun[k]->y == j)
						{
							lesha->MonteBot->tree = lesha->MonteBot->tree->Sun[k];
							break;
						}
				}
				else
				{
					Tree *newtree = new Tree;
					newtree->x = i;
					newtree->y = j;
					newtree->win = 0;
					newtree->num = 1;
					newtree->numSun = 0;
					newtree->rod = lesha->MonteBot->tree;
					lesha->MonteBot->tree->Sun.push_back(newtree);
					lesha->MonteBot->tree->numSun++;
					lesha->MonteBot->tree = newtree;
				}
				endhod(label);
			}
			while (botO && igrok == 2 && !GOver)
			{
				lesha->botchoseO(map, e);
				endhod(label);
			}
		}
	}
};