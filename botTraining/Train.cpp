#include <iostream>
#include <conio.h>
#include "tree.cpp"
using namespace std;

class Map
{
  public:
    int **map;
    bool **mapactiv;
    Map()
    {
        mapactiv = new bool *[10];
        map = new int *[10];
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
            mapactiv[0][0] = 1; // игра начинается для Х с вехнего левого угла
            return;
        }
        else if (igrok == 2 && map[9][9] == 0)
        {
            mapactiv[9][9] = 1; // игра начинается для О с нижнего правого угла
            return;
        }
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (map[i][j] == igrok)
                {
                    if (j - 1 >= 0)
                        mapactiv[i][j - 1] = 1;
                    if (j + 1 < 10)
                        mapactiv[i][j + 1] = 1;
                    if (i + 1 < 10)
                        mapactiv[i + 1][j] = 1;
                    if (i - 1 >= 0)
                        mapactiv[i - 1][j] = 1;
                    if (i + 1 < 10 && j - 1 >= 0)
                        mapactiv[i + 1][j - 1] = 1;
                    if (i + 1 < 10 && j + 1 < 10)
                        mapactiv[i + 1][j + 1] = 1;
                    if (i - 1 >= 0 && j - 1 >= 0)
                        mapactiv[i - 1][j - 1] = 1;
                    if (i - 1 >= 0 && j + 1 < 10)
                        mapactiv[i - 1][j + 1] = 1;
                }

        for (int k = 0; k < 10; k++)
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (map[i][j] == igrok + 2 && mapactiv[i][j] == 1)
                    {

                        if (j - 1 >= 0)
                            mapactiv[i][j - 1] = 1;
                        if (j + 1 < 10)
                            mapactiv[i][j + 1] = 1;
                        if (i + 1 < 10)
                            mapactiv[i + 1][j] = 1;
                        if (i - 1 >= 0)
                            mapactiv[i - 1][j] = 1;
                        if (i + 1 < 10 && j - 1 >= 0)
                            mapactiv[i + 1][j - 1] = 1;
                        if (i + 1 < 10 && j + 1 < 10)
                            mapactiv[i + 1][j + 1] = 1;
                        if (i - 1 >= 0 && j - 1 >= 0)
                            mapactiv[i - 1][j - 1] = 1;
                        if (i - 1 >= 0 && j + 1 < 10)
                            mapactiv[i - 1][j + 1] = 1;
                    }

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (map[i][j] == igrok || map[i][j] == 3 || map[i][j] == 4)
                    mapactiv[i][j] = 0;
    }
    bool Hod(int i, int j, int igrok)
    {
        Activation(igrok);
        if (!mapactiv[i][j])
            return 0;
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
        return 1;
    }
};
class Train
{

  public:
    Map *map;
    bool GOver;
    int hod;
    int igrok;
    unsigned long long int count;
    TreeBase *Tr;
    Train()
    {
        map = new Map;
        Tr = new TreeBase;
    }
    ~Train()
    {
        delete map;
        delete Tr;
    }
    bool GameOver()
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
                                    Tr->someWin(hod, 0);
                                    igrok = 0;
                                    GOver = true;
                                    return true;
                                }
                        Tr->someWin(hod, 1);
                        igrok = 0;
                        GOver = true;
                        return true;
                    }
            Tr->someWin(hod, 1);
            igrok = 0;
            GOver = true;
            return true;
        }
    }
    void endhod()
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
        GameOver();
    }
    void botchoseX(Map *map)
    {
        int maxWinrate = 0;
        int numMaxSun = -1;
        for (int i = 0; i < Tr->tree->numSun; i++)
            if (Tr->tree->Sun[i]->win / Tr->tree->Sun[i]->num >= maxWinrate)
            {
                maxWinrate = Tr->tree->Sun[i]->win / Tr->tree->Sun[i]->num;
                numMaxSun = i;
            }
        if (maxWinrate <= 0)
        {
            if (botchoseX2(map))
                return;
        }
        if (numMaxSun != -1)
        {
            map->Hod(Tr->tree->Sun[numMaxSun]->x, Tr->tree->Sun[numMaxSun]->y, 1);
            Tr->tree->Sun[numMaxSun]->num++;
            Tr->tree = Tr->tree->Sun[numMaxSun];
            return;
        }
        for (int i = 9; i >= 0; i--)
            for (int j = 9; j >= 0; j--)
                if (map->mapactiv[i][j])
                {
                    map->Hod(i, j, 1);
                    Tr->add(i, j);
                }
    }
    void botchoseO(Map *map)
    {
        int maxWinrate = 0;
        int numMaxSun = -1;
        for (int i = 0; i < Tr->tree->numSun; i++)
            if (Tr->tree->Sun[i]->win / Tr->tree->Sun[i]->num > maxWinrate)
            {
                maxWinrate = Tr->tree->Sun[i]->win / Tr->tree->Sun[i]->num;
                numMaxSun = i;
            }
        if (maxWinrate < 0.01)
        {
            if (botchoseO2(map))
                return;
        }
        if (numMaxSun != -1)
        {
            map->Hod(Tr->tree->Sun[numMaxSun]->x, Tr->tree->Sun[numMaxSun]->y, 2);
            Tr->tree->Sun[numMaxSun]->num++;
            Tr->tree = Tr->tree->Sun[numMaxSun];
            return;
        }
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (map->mapactiv[i][j])
                {
                    map->Hod(i, j, 2);
                    Tr->add(i, j);
                }
    }
    bool botchoseO2(Map *map)
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
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 2);
                                                            Tr->add(i, j);
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
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 2);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 2);
                            Tr->add(i, j);
                            return true;
                        }
                    }
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && map->map[i][j] == 1)
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 2);
                            Tr->add(i, j);
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
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 2);
                            Tr->add(i, j);
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
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 2);
                                                            Tr->add(i, j);
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
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 2);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 2);
                            Tr->add(i, j);
                            return true;
                        }
                    }
        }
        return false;
    }
    bool botchoseX2(Map *map)
    {
        int numX = 0;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (map->map[i][j] == 1)
                    numX++;
        if (numX <= 3)
        {
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                        if (j - 1 < 0 || (map->map[i][j - 1] != 2 && map->map[i][j - 1] != 4))
                            if (j + 1 >= 10 || (map->map[i][j + 1] != 2 && map->map[i][j + 1] != 4))
                                if (i + 1 >= 10 || (map->map[i + 1][j] != 2 && map->map[i + 1][j] != 4))
                                    if (i - 1 < 0 || (map->map[i - 1][j] != 2 && map->map[i - 1][j] != 4))
                                        if (i + 1 >= 10 || j - 1 < 0 || (map->map[i + 1][j - 1] != 2 && map->map[i + 1][j - 1] != 4))
                                            if (i + 1 >= 10 || j + 1 >= 10 || (map->map[i + 1][j + 1] != 2 && map->map[i + 1][j + 1] != 4))
                                                if (i - 1 < 0 || j - 1 < 0 || (map->map[i - 1][j - 1] != 2 && map->map[i - 1][j - 1] != 4))
                                                    if (i - 1 < 0 || j + 1 >= 10 || (map->map[i - 1][j + 1] != 2 && map->map[i - 1][j + 1] != 4))
                                                    {
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 1);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }

            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                        if (j - 1 < 0 || map->map[i][j - 1] != 4)
                            if (j + 1 >= 10 || map->map[i][j + 1] != 4)
                                if (i + 1 >= 10 || map->map[i + 1][j] != 4)
                                    if (i - 1 < 0 || map->map[i - 1][j] != 4)
                                        if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] != 4)
                                            if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] != 4)
                                                if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] != 4)
                                                    if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] != 4)
                                                    {
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 1);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 1);
                            Tr->add(i, j);
                            return true;
                        }
                    }
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (map->mapactiv[i][j] && map->map[i][j] == 2)
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 1);
                            Tr->add(i, j);
                            return true;
                        }
                    }
        }
        else
        {
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                    if (map->mapactiv[i][j] && map->map[i][j] == 2)
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 1);
                            Tr->add(i, j);
                            return true;
                        }
                    }
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                        if (j - 1 < 0 || map->map[i][j - 1] == 2)
                            if (j + 1 >= 10 || map->map[i][j + 1] == 2)
                                if (i + 1 >= 10 || map->map[i + 1][j] == 2)
                                    if (i - 1 < 0 || map->map[i - 1][j] == 2)
                                        if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] == 2)
                                            if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] == 2)
                                                if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] == 2)
                                                    if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] == 2)
                                                    {
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 1);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                        if (j - 1 < 0 || map->map[i][j - 1] != 4)
                            if (j + 1 >= 10 || map->map[i][j + 1] != 4)
                                if (i + 1 >= 10 || map->map[i + 1][j] != 4)
                                    if (i - 1 < 0 || map->map[i - 1][j] != 4)
                                        if (i + 1 >= 10 || j - 1 < 0 || map->map[i + 1][j - 1] != 4)
                                            if (i + 1 >= 10 || j + 1 >= 10 || map->map[i + 1][j + 1] != 4)
                                                if (i - 1 < 0 || j - 1 < 0 || map->map[i - 1][j - 1] != 4)
                                                    if (i - 1 < 0 || j + 1 >= 10 || map->map[i - 1][j + 1] != 4)
                                                    {
                                                        if (!Tr->here(i, j))
                                                        {
                                                            map->Hod(i, j, 1);
                                                            Tr->add(i, j);
                                                            return true;
                                                        }
                                                    }
            for (int i = 9; i >= 0; i--)
                for (int j = 9; j >= 0; j--)
                    if (map->mapactiv[i][j] && !map->map[i][j])
                    {
                        if (!Tr->here(i, j))
                        {
                            map->Hod(i, j, 1);
                            Tr->add(i, j);
                            return true;
                        }
                    }
        }
        return false;
    }
    void trenirovka()
    {
        GOver = false;
        hod = 0;
        igrok = 1;
        count = 0;
        map->Hod(0, 0, 1);
        endhod();
        while (true)
        {
            while (igrok == 1 && !GOver)
            {
                botchoseX(map);
                endhod();
            }
            while (igrok == 2 && !GOver)
            {
                botchoseO(map);
                endhod();
            }
            if (GOver)
            {
                GOver = false;
                hod = 0;
                igrok = 1;
                delete map;
                map = new Map;
                map->Hod(0, 0, 1);
                endhod();
                cout << count << endl;
                count++;
            }
            if (_kbhit())
            {
                Tr->saveall();
                return;
            }
        }
    }
};
int main()
{
    Train temp;
    temp.trenirovka();
    return 0;
}