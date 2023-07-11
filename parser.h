#include <bits/stdc++.h>
#include "grammar.h"
#include "lexer.h"

using std::string;
using std::vector;
using std::map;
using std::set;

map<string, char> typeToVt{
    {IDENT, 'd'},
    {INT, 'n'},
    {ASSIGN, '='},
    {PLUS, '+'},
    {MINUS, '-'},
    {ASTERISK, '*'},
    {SLASH, '/'},
    {SEMICOLON, ';'},
    {LPAREN, '('},
    {RPAREN, ')'},
    {LBRACE, '{'},
    {RBRACE, '}'},
    {END, '#'},
    {LET, 'l'},
    {VOID, 'v'},
};

bool doParserAnalyze(vector<token> l, parserTableType p, grammarType g)
{
    std::cout << "Parser stack: \n";
    std::cout << "Number  Stack                              StringRemain\n";
    vector<char> parserStack1;
    vector<char> parserStack2;
    parserStack1.push_back('#');
    parserStack1.push_back('B');
    for (int i = (int)l.size() - 1; i >= 0; i--)
    {
        parserStack2.push_back(typeToVt[l[i].Type]);
    }
    int num = 0;
    while (1)
    {
        if (parserStack1.empty() && parserStack2.empty())
        {
            return true;
        }
        else if (parserStack1.empty() && !parserStack2.empty())
        {
            return false;
        }
        else if (!parserStack1.empty() && parserStack2.empty())
        {
            return false;
        }
        std::cout << ++num << "  ";
        for (auto c: parserStack1)
        {
            std::cout << c;
        }
        for (int i = 0; i <= 35 - parserStack1.size(); i++)
        {
            std::cout << " ";
        }
        for (int i = (int)parserStack2.size() - 1; i >= 0; i--)
        {
            std::cout << parserStack2[i];
        }
        std::cout << '\n';
        char ch1 = parserStack1.back();
        char ch2 = parserStack2.back();
        if (ch1 == ch2)
        {
            parserStack1.pop_back();
            parserStack2.pop_back();
        }
        else
        {
            if (!p[{ch1, ch2}])
            {
                return false;
            }
            int id = p[{ch1, ch2}] - 1;
            parserStack1.pop_back();
            string s = g[ch1][id];
            if (s != "$")
            {
                for (int j = (int)s.length() - 1; j >= 0; j--)
                {
                    parserStack1.push_back(s[j]);
                }
            }
            
        }
    }
    
    
}
