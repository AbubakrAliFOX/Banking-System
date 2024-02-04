#pragma once
#include <string>

class clsChar
{
private: 
    char _Char;

public:

    static char CapitilizeLetter(char Letter)
    {
        return char(toupper(Letter));
    }


    static char LowercaseLetter(char Letter)
    {
        return char(tolower(Letter));
    }


    static char InvertChar(char charachter)
    {
        return isupper(charachter) ? tolower(charachter) : toupper(charachter);
    }
};

