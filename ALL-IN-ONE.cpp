#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <ctime>
#include <stdlib.h>


typedef std::vector<int> Row;
typedef std::vector<Row> Field;
typedef std::pair<int, int> Coord;
typedef std::vector<int> IntVect;
typedef int (*CheckFunc)(const Field &, const Coord &);

#define FIELD_SIZE 10

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

std::string encode_string(const Coord &c)
{
    std::string res;
    if (c.second+65 == 74)
    {
        res.push_back((char)c.second+65+1);
    }
    else
        res.push_back((char)c.second+65);
    if (c.first == 9)
    {
        res.push_back((char)49);
        res.push_back((char)48);
    }
    else
        res.push_back((char)c.first+49);
    return res;
}

void print_field(const Field &f)
{
    std::cout << "    A   B   C   D   E   F   G   H   I   K  " << std::endl;
    std::cout << "  +---+---+---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        if (i != 9)
            std::cout << i+1 << " ";
        else
            std::cout << i+1;
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            switch(f[i][j])
            {
                case 0:
                    std::cout << "|   ";
                    break;
                case 1:
                    std::cout << "| O ";
                    break;
                case 2:
                    std::cout << "| X ";
                    break;
                case 3:
                    std::cout << "| . ";
                    break;
                case 4:
                    std::cout << "| * ";
                    break;
                case 5:
                    std::cout << "| K ";
            }
             
        }
        std::cout << '|';
        std::cout << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+---+---+\n";      
    }
}

bool check_borders(int i, int j) {
	return (i >= 0 && i < FIELD_SIZE && j >= 0 && j < FIELD_SIZE);
}

const Coord next_move(const Field &user_field, const Coord &last_move) {
	int curr_i = last_move.first, curr_j = last_move.second;
	while(true) {
		curr_j += 2;
		if (curr_j >= FIELD_SIZE) {
			curr_j = curr_j % FIELD_SIZE;
			curr_i += 1;
			if (curr_i >= FIELD_SIZE)
				curr_i = 0;
		}

		int result = user_field[curr_i][curr_j];
		if (result == 0)
			break;
	}	
	return std::make_pair(curr_i, curr_j);
}

const Coord tricky_move(const Field &user_field, const Coord &last_move) {
	int curr_i = last_move.first, curr_j = last_move.second;
	//try to find near enemy cell
	std::cout << "SO TRICKY MOVE" << std::endl;
	return std::make_pair(curr_i, curr_j);
}

std::string ask_user(const Coord move) {
	std::string result;
	std::cout << "Fire on " << encode_string(move) << std::endl;
	std::cin >> result;
	return result;
}

bool comp_move(Field &user_field, Coord &last_move) {
	int last_result;
	Coord move;
	std::string resp;
	
	if (last_move.first < 0 or last_move.second < 0) {
		last_move.first = 0;
		last_move.second = 0;
	}
	
	while(true) {
		print_field(user_field);
		last_result = user_field[last_move.first][last_move.second];
		if (last_result == 2) 
			move = tricky_move(user_field, last_move);
		else if (last_result == 0)
			move = last_move;
		else 
			move = next_move(user_field, last_move);
		resp = ask_user(move);
		last_move = move;

		if (resp == "MISS")
		 	user_field[last_move.first][last_move.second] = 3;
			return false;
		if (resp == "HIT")
		 	user_field[last_move.first][last_move.second] = 2;
		if (resp == "KILL")
		 	user_field[last_move.first][last_move.second] = 5;
		
	}
}


int main() {
    srand(time(0));
    Row row (FIELD_SIZE);
    Field user(FIELD_SIZE, row);
    Field enemy(FIELD_SIZE, Row(FIELD_SIZE));
    place_ships(user);
    print_field(user);
    Coord init = std::make_pair(-1,-1);
    while(true)
	    comp_move(enemy, init);	 
   
    return 0;
}
