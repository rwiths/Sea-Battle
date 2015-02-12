#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <utility>

#define N 10

typedef std::vector<int> Row;
typedef std::vector<Row> Field;
typedef std::pair<int,int> Coord;

typedef std::vector<int> IntVect;
typedef int (*CheckFunc)(const Field &, const Coord &);

void look_around(const Field &f, const Coord &c, CheckFunc cf, IntVect &res)
{
    int sz = f.size();
    IntVect r;
    r.reserve(8);
    if (c.first - 1 >= 0 && c.second + 1 >= 0)
        r.push_back(cf(f, Coord(c.first - 1, c.second + 1)));
    if (c.second + 1 <= sz - 1)
        r.push_back(cf(f, Coord(c.first, c.second + 1)));
    if (c.first + 1 <= sz - 1 && c.second + 1 <= sz - 1)
        r.push_back(cf(f, Coord(c.first + 1, c.second + 1)));
    if (c.first + 1 <= sz - 1)
        r.push_back(cf(f, Coord(c.first + 1, c.second)));
    if (c.first + 1 <= sz - 1 && c.second - 1 >= 0)
        r.push_back(cf(f, Coord(c.first + 1, c.second - 1)));
    if (c.second - 1 >= 0)
        r.push_back(cf(f, Coord(c.first, c.second - 1)));
    if (c.first - 1 >= 0 && c.second - 1 >= 0)
        r.push_back(cf(f, Coord(c.first - 1, c.second - 1)));
    if (c.first - 1 >= 0)
        r.push_back(cf(f, Coord(c.first - 1, c.second)));
    res.swap(r);
}

int sum(const IntVect &r)
{
    IntVect::const_iterator i = r.begin(), e = r.end();
    int x = 0;
    for (; i != e; ++i)
        x += *i;
    return x;
}

int get_cell(const Field &f, const Coord &c)
{
    std::cout<<"It`s get_cell"<<endl;
    return f[c.first][c.second];
}

bool block_check(const Field &f, const Coord &c)  // true if there are non-0 cell around
{
    IntVect res;
    look_around(f, c, get_cell, res);
    return sum(res) + f[c.first][c.second] > 0;
}

void place_ship(Field &field, int sz)
{
    srand(time(0));
    Coord c;
    Coord tmp;
    int flag = 0;
    int side;
    while(flag == 0)
    {
        side = rand() % 4;
        
        if(side == 0) //up
        {
            c.first = rand() % (10 - sz) + sz;
            c.second = rand() % 10;
            tmp = c;
            for(int i = 0; i < sz; i++, tmp.first--)
            {
                if(block_check(field, tmp) != false)
                    break;
                if(sz - i == 1)
                {
                    for(int j = 0; j < sz; j++)
                        field[c.first-j][c.second] = 1;
                    flag = 1;
                }
            }
        }
        if(side == 1) //down
        {
            c.first = rand() % (10 - sz);
            c.second = rand() % 10;            
            tmp = c;
            for(int i = 0; i < sz; i++, tmp.first++)
            {
                if(block_check(field, tmp) != false)
                    break;
                if(sz - i == 1)
                {
                    for(int j = 0; j < sz; j++)
                        field[c.first+j][c.second] = 1;
                    flag = 1;
                }
            }
        }
        if(side == 2) //left
        {
            c.first = rand() % 10;
            c.second = rand() % (10 - sz) + sz;
            tmp = c;
            for(int i = 0; i < sz; i++, tmp.second--)
            {
                if(block_check(field, tmp) != false)
                    break;
                if(sz - i == 1)
                {
                    for(int j = 0; j < sz; j++)
                        field[c.first][c.second-j] = 1;
                    flag = 1;
                }
            }
        }
        if(side == 3) //right
        {
            c.first = rand() % 10;
            c.second = rand() % (10 - sz);         
            tmp = c;
            for(int i = 0; i < sz; i++, tmp.second++)
            {
                if(block_check(field, tmp) != false)
                    break;
                if(sz - i == 1)
                {
                    for(int j = 0; j < sz; j++)
                        field[c.first][c.second+j] = 1;
                    flag = 1;
                }
            }
        }
    }
}

void place_ships(Field &field)
{
    place_ship(field, 4);
    place_ship(field, 3);
    place_ship(field, 3);
    place_ship(field, 2);
    place_ship(field, 2);
    place_ship(field, 2);
    place_ship(field, 1);
    place_ship(field, 1);
    place_ship(field, 1);
    place_ship(field, 1);
}

/*int main()
{
    Row row(10);
    Field field(10, row);
    place_ships(field);
    print_field(field);
    return 0;
}*/
