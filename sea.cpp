#include <stdio.h>
#include <vector>
#include <iostream>
#include <utility>

typedef std::vector<int> Row;
typedef std::vector<Row> Field;
typedef std::pair<int, int> Coord;

typedef std::pair<Coord, int> Result;
typedef std::vector<Result> ResultVect;
typedef int (*CheckFunc)(const Field &, const Coord &);

bool all_kill(Field &f)
{
    int count = 0;
    for(int i = 0; i < f.size(); ++i)
    {
        for(int j = 0; f[i].size(); ++j)
        {
            if(f[i][j] == 2)
                ++count;
        }
    }
    if(count == 20)
        return true;
}

void around_ship(Field &f, Coord &c, int orient)
{
    if(orient == -1)
    {
        if(c.second > 0 && c.second < f.size() - 1)
        {
            f[c.first][c.second + 1] = 3;
            f[c.first][c.second - 1] = 3;
        }
    }
    
}

void look_around(const Field &f, const Coord &c, CheckFunc cf, ResultVect &res)
{
    int sz = f.size();
    ResultVect r;
    r.reserve(8);
    if (c.first - 1 >= 0 && c.second + 1 >= 0) {
        Coord c(c.first - 1, c.second + 1);
        r.push_back(Result(c, cf(f, c)));
    }
    if (c.second + 1 <= sz - 1) {
        Coord c(c.first, c.second + 1);
        r.push_back(Result(c, cf(f, c)));
    }
    if (c.first + 1 <= sz - 1 && c.second + 1 <= sz - 1) {
        Coord c(c.first + 1, c.second + 1)
        r.push_back(Result(c, cf(f, c)));
    }
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
    return c;
}

bool check_killed(Field &f, const Coord &c)
{
    if(f[c.first][c.second] == 5)
        return true;
    if(f[c.first][c.second] != 2)
        return false;
    IntVect res;
    look_around(f, c, get_cell, res);
    for(int i = 0; i < res.size(); ++i)
    {
        if(res[i] == 1)
            return false;
        
    }
}

int main()
{
    
    return 0;
}
