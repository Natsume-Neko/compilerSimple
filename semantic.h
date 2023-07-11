#include "parser.h"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

struct semType
{
    string op;
    string arg1;
    string arg2;
    string res;
};

string intToString(int x)
{
    string t = "t";
    string s;
    while (x != 0)
    {
        s += (char)(x % 10 + '0');
        x /= 10;
    }
    s.reserve();
    return t + s;
}
void printSemanticAns(vector<semType> smtc);
vector<semType> getSemanticAns(vector<token> l, parserTableType p, grammarType g);

class semantic
{
public:
    vector<token> lex;
    parserTableType parserTable;
    grammarType newGrammar;
    map<string, bool> identTable;
    map<string, string> identNum;
    vector<semType> sems;
    int tmpCount;
    int tokenPTR;
    semantic(vector<token> l, parserTableType p, grammarType g);
    void error();
    bool check(char);
    token getToken();
    void nextToken();
    void B();
    void T();
    void S();
    string E();
    string A(string);
    string U();
    string Q(string);
    string F();
};

semantic::semantic(vector<token> l, parserTableType p, grammarType g)
{
    lex = l;
    parserTable = p;
    newGrammar = g;
    tokenPTR = 0;
    tmpCount = 0;
}

void semantic::error()
{
    std::cout << "Parser Error\n";
    exit(0);
}

bool semantic::check(char ch)
{
    auto tok = getToken();
    char Vt = typeToVt[tok.Type];
    return Vt == ch;
}

void semantic::nextToken()
{
    if (tokenPTR >= lex.size())
    {
        error();
    }
    tokenPTR++;
}

token semantic::getToken()
{
    if (tokenPTR >= lex.size())
    {
        error();
    }
    return lex[tokenPTR];
}

void semantic::B()
{
    if (check('v') || check('i'))
    {
        T();
    }
    else
    {
        error();
    }
    if (check('d'))
    {
        nextToken();
    }
    else
    {
        error();
    }
    if (check('('))
    {
        nextToken();
    }
    else
    {
        error();
    }
    if (check(')'))
    {
        nextToken();
    }
    else
    {
        error();
    }
    if (check('{'))
    {
        nextToken();
    }
    else
    {
        error();
    }
    if (check('}') || check('l') || check('d'))
    {
        S();
    }
    else
    {
        error();
    }
    if (check('}'))
    {
        nextToken();
    }
    else
    {
        error();
    }
    
}

void semantic::T()
{
    if (check('v') || check('i'))
    {
        nextToken();
    }
    else
    {
        error();
    }
}

void semantic::S()
{
    if (check('}'))
    {
        return;
    }
    else if (check('l'))
    {
        nextToken();
        string name = getToken().Literal;
        if (check('d'))
        {
            nextToken();
        }
        else
        {
            error();
        }
        if (check('='))
        {
            nextToken();
        }
        else
        {
            error();
        }
        if (check('(') || check('d') || check('n'))
        {
            string num = E();
            identTable[name] = true;
            identNum[name] = num;
            sems.push_back({ASSIGN, num, "", name});
        }
        else
        {
            error();
        }
        if (check(';'))
        {
            nextToken();
        }
        else
        {
            error();
        }
        if (check('}') || check('l') || check('d'))
        {
            S();
        }
        else
        {
            error();
        }
    }
    else if (check('d'))
    {
        string name = getToken().Literal;
        nextToken();
        if (check('='))
        {
            nextToken();
        }
        else
        {
            error();
        }
        if (check('(') || check('d') || check('n'))
        {
            string num = E();
            identTable[name] = true;
            identNum[name] = num;
            sems.push_back({ASSIGN, num, "", name});
        }
        else
        {
            error();
        }
        if (check(';'))
        {
            nextToken();
        }
        else
        {
            error();
        }
        if (check('}') || check('l') || check('d'))
        {
            S();
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
    
}

string semantic::E()
{
    if (check('(') || check('d') || check('n'))
    {
        string num = U();
        if (check(';') || check('+') || check('-') || check(')'))
        {
            return A(num);
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

string semantic::A(string t)
{
    if (check('+'))
    {
        nextToken();
        if (check('(') || check('d') || check('n'))
        {
            string num = U();
            if (check(')') || check('+') || check('-') || check(';'))
            {
                int tmp = ++tmpCount;
                string stmp = intToString(tmp);
                sems.push_back({PLUS, t, num, stmp});
                return A(stmp);
            }
        }
    }
    else if (check('-'))
    {
        nextToken();
        if (check('(') || check('d') || check('n'))
        {
            string num = U();
            if (check(')') || check('+') || check('-') || check(';'))
            {
                int tmp = ++tmpCount;
                string stmp = intToString(tmp);
                sems.push_back({MINUS, t, num, stmp});
                return A(stmp);
            }
        }
    }
    else if (check(';') || check(')'))
    {
        return t;
    }
    else
    {
        error();
    }   
}

string semantic::U()
{
    if (check('(') || check('d') || check('n'))
    {
        string num = F();
        if (check('*') || check('/') || check('+') || check('-') || check(')') || check(';'))
        {
            return Q(num);
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

string semantic::Q(string t)
{
    if (check('*'))
    {
        nextToken();
        if (check('(') || check('d') || check('n'))
        {
            string num = F();
            if (check('*') || check('/') || check('+') || check('-') || check(')') || check(';'))
            {
                int tmp = ++tmpCount;
                string stmp = intToString(tmp);
                sems.push_back({ASTERISK, t, num, stmp});
                return Q(stmp);
            }
            else
            {
                error();
            }
        }
    }
    else if (check('/'))
    {
        nextToken();
        if (check('(') || check('d') || check('n'))
        {
            string num = F();
            if (check('*') || check('/') || check('+') || check('-') || check(')') || check(';'))
            {
                int tmp = ++tmpCount;
                string stmp = intToString(tmp);
                sems.push_back({SLASH, t, num, stmp});
                return Q(stmp);
            }
            else
            {
                error();
            }
        }
    }
    else if (check('+') || check('-') || check(';') || check(')'))
    {
        return t;
    }
    else
    {
        error();
    }
}

string semantic::F()
{
    if (check('('))
    {
        nextToken();
        if (check('(') || check('d') || check('n'))
        {
            string num = E();
            if (check(')'))
            {
                nextToken();
            }
            else
            {
                error();
            }
            return num;
        }
        else
        {
            error();
        }
    }
    else if (check('n'))
    {
        string num = getToken().Literal;
        nextToken();
        return num;
    }
    else if (check('d'))
    {
        string num = getToken().Literal;
        nextToken();
        return num;
    }
    else
    {
        error();
    }
}

vector<semType> getSemanticAns(vector<token> l, parserTableType p, grammarType g)
{
    semantic smtc = semantic(l, p, g);
    smtc.B();
    return smtc.sems;
}

void printSemanticAns(vector<semType> smtc)
{
    std::cout << "Semantic result: \n";
    int n = 0;
    for (auto x: smtc)
    {
        std::cout << n++ << "(" << x.op << ", " << x.arg1 << ", " << x.arg2 << ", " << x.res << ")\n";
    }
}