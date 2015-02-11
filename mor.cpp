#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#define N 10

typedef std::vector<int> Row;
typedef std::vector<Row> Field;


void print_field(const Field &f)
{
    std::cout << "    A   B   C   D   E   F   G   H   I   K  " << std::endl;
    std::cout << "  +---+---+---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < N; i++)
    {
        if (i != 9)
            std::cout << i+1 << " ";
        else
            std::cout << i+1;
        for (int j = 0; j < N; j++)
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
/*
int main()
{
    srand(time(0));
    Row row (N);
    Field f(N,row);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f[i][j] = rand() % 6;
        }
    }
    print_field(f);
    
   
    return 0;
}
*/
