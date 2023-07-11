#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

typedef map<char, vector<string>> grammarType;
typedef map<char, set<pair<char, int>>> setType;
typedef map<pair<char, char>, int> parserTableType;

grammarType grammar{
    {'B', {"Td(){S}"}},
    {'S', {"ld=E;S", "d=E;S", "$"}},
    {'E', {"E+U", "E-U", "U"}},
    {'U', {"U*F", "U/F", "F"}},
    {'F', {"(E)", "n", "d"}},
    {'T', {"v", "i"}},
};

set<char> newVt;
set<char> newVn;

grammarType eliminateLeftRecursion(grammarType g)
{
    grammarType newGrammar;
    for (auto V : g)
    {
        char Vn = V.first;
        set<int> num;
        for (int i = 0; i < V.second.size(); i++)
        {
            if (Vn == V.second[i][0])
            {
                num.insert(i);
            }
        }
        if (!num.empty())
        {
            vector<string> newVec;
            string s;
            string ch = V.second[2];
            s += ch;
            s += Vn - 4;
            newVec.push_back(s);
            newGrammar.insert({V.first, newVec});
            vector<string> scndVec;
            for (auto i: num)
            {
                string t = V.second[i];
                string res;
                for (int j = 1; j < t.length(); j++)
                {
                    res += t[j];
                }
                res += Vn - 4;
                scndVec.push_back(res);
            }
            scndVec.push_back("$");
            newGrammar.insert({Vn - 4, scndVec});
        }
        else
        {
            newGrammar.insert(V);
        }
    }
    return newGrammar;
}

void printGrammar(grammarType g)
{
    std::cout << "Grammar: \n";
    for (auto i: g)
    {
        std::cout << i.first << " -> ";
        for (auto j: i.second)
        {
            std::cout << j << " | ";
        }
        std::cout << '\n';
    }
}

setType getFirstSet(grammarType g)
{
    setType firstSet;
    while (1)
    {
        bool changed = false;
        for (auto V: g)
        {
            int x = firstSet[V.first].size();
            for (int i = 0; i < V.second.size(); i++)
            {
                string s = V.second[i];
                if (s[0] >= 'A' && s[0] <= 'Z')
                {
                    for (auto y: firstSet[s[0]])
                    {
                        firstSet[V.first].insert(y);
                    }
                }
                else
                {
                    firstSet[V.first].insert({s[0], i});
                }   
            }
            if (x < firstSet[V.first].size())
            {
                changed = true;
            }
        }
        if (!changed)
        {
            break;
        }
    }
    return firstSet;
}

void printFirstSet(setType s)
{
    std::cout << "FirstSet: \n";
    for (auto i: s)
    {
        std::cout << i.first << ": ";
        for (auto j: i.second)
        {
            std::cout << j.first << ", ";
        }
        std::cout << '\n';
    }
    
}

setType getFollowSet(grammarType g, setType firstSet)
{
    setType followSet;
    map<char, bool> canVoid;
    for (auto V: g)
    {
        canVoid[V.first] = false;
        for (auto x: V.second)
        {
            if (x == "$")
            {
                canVoid[V.first] = true;
            }
        }
    }
    while (1)
    {
        bool changed = false;
        for (auto V: g)
        {
            for (auto x: V.second)
            {
                for (int i = 0; i < (int)x.size(); i++)
                {
                    if (x[i] >= 'A' && x[i] <= 'Z')
                    {
                        int num = followSet[x[i]].size();
                        if (i == (int)x.size() - 1)
                        {
                            for (auto y: followSet[V.first])
                            {
                                if (y.first != '$')
                                {
                                    followSet[x[i]].insert(y);
                                }
                            }
                        }
                        else
                        {
                            if (x[i + 1] >= 'A' && x[i + 1] <= 'Z')
                            {
                                for (auto y: firstSet[x[i + 1]])
                                {
                                    if (y.first != '$')
                                    {
                                        followSet[x[i]].insert({y.first, 0});
                                    }
                                }
                                if (i == (int)x.size() - 2 && canVoid[x[i + 1]])
                                {
                                    for (auto y: followSet[V.first])
                                    {
                                        if (y.first != '$')
                                        {
                                            followSet[x[i]].insert(y);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (x[i + 1] != '$')
                                {
                                    followSet[x[i]].insert({x[i + 1], 0});
                                }
                                
                            }   
                        }
                        if (num < followSet[x[i]].size())
                        {
                            changed = true;
                        }
                        
                    }
                    
                }
                
            }
               
        }
        if (!changed)
        {
            break;
        }
    }
    return followSet;
}

void printFollowSet(setType s)
{
    std::cout << "FollowSet: \n";
    for (auto i: s)
    {
        std::cout << i.first << ": ";
        for (auto j: i.second)
        {
            std::cout << j.first << ", ";
        }
        std::cout << '\n';
    }
    
}

pair<parserTableType, parserTableType> getParserTable(grammarType g, setType firstSet, setType followSet)
{
    std::cout << "Parser table: \n";
    parserTableType parserTableShow;
    parserTableType parserTable;
    int num = 0;
    for (auto V: g)
    {
        int i = 0;
        for (auto x: V.second)
        {
            ++i;
            ++num;
            if (x == "$")
            {
                for (auto y: followSet[V.first])
                {
                    parserTableShow[{V.first, y.first}] = num;
                    parserTable[{V.first, y.first}] = i;
                }
            }
            else
            {
                if (x[0] >= 'A' && x[0] <= 'Z')
                {
                    for (auto y: firstSet[x[0]])
                    {
                        parserTableShow[{V.first, y.first}] = num;
                        parserTable[{V.first, y.first}] = i;
                    }
                }
                else
                {
                    parserTableShow[{V.first, x[0]}] = num;
                    parserTable[{V.first, x[0]}] = i;
                }
                
            }
        }
    }
    return {parserTableShow, parserTable};
}

void printParserTable(grammarType g, parserTableType p)
{
    for (auto V: g)
    {
        newVn.insert(V.first);
        for (auto x: V.second)
        {
            for (auto c: x)
            {
                if (!(c >= 'A' && c <= 'Z'))
                {
                    newVt.insert(c);
                }
            }
        }
    }
    std::cout << ' ';
    for (auto Vt: newVt)
    {
        std::cout << Vt << ' ';
    }
    std::cout << '\n';
    for (auto Vn: newVn)
    {
        std::cout << Vn << ' ';
        for (auto Vt: newVt)
        {
            std::cout << p[{Vn, Vt}] << ' ';
        }
        std::cout << '\n';
    }
    
}


/* 
B = begin
T = type
L = ident
S = sentence
E = Expression
l = let
i = int
v = void
d = ident
n = integer

Vn = {B, T, I, S, E, U, F}
Vt = {$, +, -, *, /, =, n, v, i, l, d, (, ), {, }, #}

B -> T I () {S} 
S -> l I = E; S
S -> $
E -> E + U
E -> E - U
E -> U
F -> (E)
U -> U * F
U -> U / F
U -> F
F -> n
I -> d
T -> v | i

*/