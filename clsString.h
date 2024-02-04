#pragma once
#include <iostream>
#include <vector>
#include "clsChar.h"
using namespace std;

class clsString
{
private:
    string _Value;

public:
    clsString()
    {
        _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void setValue(string Value)
    {
        _Value = Value;
    }

    string getValue()
    {
        return _Value;
    }

    __declspec(property(get = getValue, put = setValue)) string Value;

    // string methods:

    static void PrintFirstLetterOfWord(string Sentence)
    {
        bool FirstLetter = true;

        for (short i = 0; i < Sentence.length(); i++)
        {
            if (Sentence[i] != ' ' && FirstLetter)
            {
                cout << Sentence[i] << endl;
            }

            FirstLetter = Sentence[i] == ' ';
        }
    }

    void PrintFirstLetterOfWord()
    {
        PrintFirstLetterOfWord(Value);
    }

    

    static void CapatilizeSentence(string Sentence)
    {
        bool IsFirstLetter = true;

        for (short i = 0; i < Sentence.length(); i++)
        {
            if (Sentence[i] != ' ' && IsFirstLetter)
            {
                Sentence[i] = clsChar::CapitilizeLetter(Sentence[i]);
            }

            IsFirstLetter = Sentence[i] == ' ';
        }

        cout << Sentence << endl;
    }

    void CapatilizeSentence()
    {
        CapatilizeSentence(Value);
    }


    static void LowercaseSentece(string Sentence)
    {
        bool IsFirstLetter = true;

        for (short i = 0; i < Sentence.length(); i++)
        {
            if (Sentence[i] != ' ' && IsFirstLetter)
            {
                Sentence[i] = clsChar::LowercaseLetter(Sentence[i]);
            }

            IsFirstLetter = Sentence[i] == ' ';
        }

        cout << Sentence << endl;
    }

    void LowercaseSentece()
    {
        LowercaseSentece(Value);
    }


    static string InvertString(string Str)
    {
        for (short i = 0; i < Str.length(); i++)
        {
            Str[i] = clsChar::InvertChar(Str[i]);
        }

        return Str;
    }

    string InvertString()
    {
        return InvertString(Value);
    }

    static int UpperCaseCount(string Str)
    {
        int UpperCounter = 0;
        for (short i = 0; i < Str.length(); i++)
        {
            isupper(Str[i]) && UpperCounter++;
        }

        return UpperCounter;
    }

    int UpperCaseCount()
    {
        return UpperCaseCount(Value);
    }

    static int LowerCaseCount(string Str)
    {
        int LowerCounter = 0;
        for (short i = 0; i < Str.length(); i++)
        {
            islower(Str[i]) && LowerCounter++;
        }

        return LowerCounter;
    }

    int LowerCaseCount()
    {
        return LowerCaseCount(Value);
    }

    static void LetterInStringCounter(string Sentence, char Charachter, bool MatchCase = true)
    {
        int Counter = 0;

        for (short i = 0; i < Sentence.length(); i++)
        {
            if (MatchCase)
            {
                (Sentence[i] == Charachter) && Counter++;
            }
            else
            {
                (tolower(Sentence[i]) == tolower(Charachter)) && Counter++;
            }
        }

        cout << "You letter " << Charachter << ", " << char(toupper(Charachter)) << " has " << Counter << " occurences in the string.";
    }

    void LetterInStringCounter(char Char, bool MatchCase)
    {
        LetterInStringCounter(Value, Char, MatchCase);
    }

    bool IsVowel(char Ch)
    {
        Ch = tolower(Ch);
        return Ch == 'a' || Ch == 'e' || Ch == 'i' || Ch == 'o' || Ch == 'u';
    }

    void CountVowels(string String)
    {
        int Counter = 0;

        for (short i = 0; i < String.length(); i++)
        {
            IsVowel(String[i]) && Counter++;
        }

        cout << Counter << " Vowels" << endl;
    }

    void CountVowels()
    {
        CountVowels(Value);
    }

    static short CountWords(string S1)
    {
        string delim = " "; // delimiter
        cout << "\nYour string wrords are: \n\n";
        short pos = 0;
        string sWord; // define a string variable  // use find() function to get the position of the delimiters

        short Counter = 0;
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
            {
                cout << sWord << endl;
                Counter++;
            }
            S1.erase(0, pos + delim.length()); /* erase() until positon and move to next word. */
        }
        if (S1 != "")
        {
            cout << S1 << endl; // it print last word of the string.
            Counter++;
        }

        return Counter;
    }

    short CountWords()
    {
        CountWords(Value);
    }

    static vector<string> Split(string S1, string Delim)
    {

        vector<string> vString;

        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            // if (sWord != "")
            // {
            vString.push_back(sWord);
            //}

            S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }

        return vString;

    }

    vector<string> Split(string Delim)
    {
        return Split(_Value, Delim);
    }

    static string join(vector<string> vWords, string Delim)
    {
        string Str;
        for (short i = 0; i < vWords.size(); i++)
        {
            Str = Str + vWords[i] + Delim;
        }

        return Str.substr(0, Str.length() - Delim.length());
    }

    static bool isPunc(char Ch) {
        return Ch == ',' || Ch == '.' || Ch == '\'' || Ch == '\"' || Ch == '\\';
    }

    static string RemovePunctuation(string Str)
    {
        string Punc = ",'./\"";
        string StrWithoutPunc = "";
        for (short i = 0; i < Str.length(); i++)
        {
            if (!isPunc(Str[i]))
            {
                StrWithoutPunc += Str[i];
            }
        }

        return StrWithoutPunc;
    }

    string RemovePunctuation() {
        return RemovePunctuation(Value);
    }

};

