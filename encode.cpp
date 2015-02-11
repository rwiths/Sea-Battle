#include <iostream>
#include <utility>
#include <stdlib.h>
#include <string>
//std::string encode_coord(const Coord &c);
typedef std::pair<int,int> Coord;


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
Coord decode_coord(const std::string &s)
{
    Coord c;
    if (s.length()>2)
    {
        c.first = 9;
    }
    else
    {
        c.first = s[1]-49;
    }
    
    if (s[0]-65 == 10)
    {
        c.second = s[0]-66; 
    }
    else
    {
        c.second = s[0]-65; 
    }
     
    return c;  
}

/*int main()
{
    std::cout << "\n";
    Coord c;
    std::cout << "Encode test:\n";
    for (int i = 0; i < 10; i++)
    {
        c.first = c.second = i;
        std::cout << c.first << " " << c.second << " "<< "  =  " << encode_string(c) << std::endl;
    }
    std::cout << "\n";
    std::cout << "Decode test:\n";
    std::cout << "A1" << " " << " = " << decode_coord("A1").first << " "<< decode_coord("A1").second << std::endl;
    std::cout << "B2" << " " << " = " << decode_coord("B2").first << " "<< decode_coord("B2").second << std::endl;
    std::cout << "C3" << " " << " = " << decode_coord("C3").first << " "<< decode_coord("C3").second << std::endl;
    std::cout << "D4" << " " << " = " << decode_coord("D4").first << " "<< decode_coord("D4").second << std::endl;
    std::cout << "E5" << " " << " = " << decode_coord("E5").first << " "<< decode_coord("E5").second << std::endl;
    std::cout << "F6" << " " << " = " << decode_coord("F6").first << " "<< decode_coord("F6").second << std::endl;
    std::cout << "G7" << " " << " = " << decode_coord("G7").first << " "<< decode_coord("G7").second << std::endl;
    std::cout << "H8" << " " << " = " << decode_coord("H8").first << " "<< decode_coord("H8").second << std::endl;
    std::cout << "I9" << " " << " = " << decode_coord("I9").first << " "<< decode_coord("I9").second << std::endl;
    std::cout << "K10" << " " << " = " << decode_coord("K10").first << " "<< decode_coord("K10").second << std::endl;
    std::cout << std::endl;

    

    return 0;
}
*/
