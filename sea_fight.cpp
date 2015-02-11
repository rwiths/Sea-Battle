#include <stdio.h>
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "mor.cpp"
#include "encode.cpp"
#include "1.cpp"

typedef std::vector<int> Row;
typedef std::vector<Row> Field;
typedef std::pair<int, int> Coord;


bool check_killed(Field &my, Coord p)
{
    /*GLOB++;
    if(GLOB==1)
    {
        GLOB=0;
        return true;
    }*/
    return false;
}
//спросить коорд, пометить, ответ, ходить или нет?,

Coord player_turn()
{
    int x,y;
    std::string str;
    std::cout<<"Make your turn"<<std::endl;
    std::cin>>str;
    Coord p=decode_coord(str);
    //std::cin>>y>>x;
    //Coord p(x,y);
    return p;
}

void mark_killed(Field &my,Coord p)
{
    int i,j;
    i=p.first;j=p.second;
    my[p.first][p.second]=5;
    for(int k=0;k<4;k++)
    {
        int it=i,jt=j;
        while(my[it][jt]==2 || my[it][jt]==5)
        {
            
            switch (k)
            {
                case 0:it++;if(it<10)if(my[it][j]==2 || my[it][jt]==5)my[it][j]=5;break;
                case 1:it--;if(it>=0)if(my[it][j]==2 || my[it][jt]==5)my[it][j]=5;break;
                case 2:jt++;if(jt<10)if(my[i][jt]==2 || my[it][jt]==5)my[i][jt]=5;break;
                case 3:jt--;if(jt>=0)if(my[i][jt]==2 || my[it][jt]==5)my[i][jt]=5;break;
            }
        }
    }
}

bool user_move(Field &my)
{
    Coord p=player_turn();
    if (my[p.first][p.second]==0)
    {
        my[p.first][p.second]=3;
        std::cout<<"Miss"<<std::endl;
        return false;
    }
    if (my[p.first][p.second]==1)
    {
        my[p.first][p.second]=2;
        if(check_killed(my,p))
        {
            std::cout<<"Killed"<<std::endl;
            mark_killed(my,p);
        }
        else std::cout<<"Hit"<<std::endl;
        return true;
    }
    std::cout<<"Miss"<<std::endl;
    return false;
}


int main()
{
    Row row (10);
    Field my(10,row);
    Field your(10,row);
    place_ships(my);
    //Coord p(4,5);
    //my[4][4]=1;
    //my[4][5]=1;
    //mark_killed(my,p);
    while(1)
    {
        user_move(my);
        //if(!user_move(my)) break;
        /*while(my_move(your));
        */
        print_field(my);
    }
    return 0;
}
