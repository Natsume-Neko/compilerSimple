#include <bits/stdc++.h>

using std::string;
using std::map;
using std::make_pair;

//标识符+字面量
const string IDENT = "IDENT";
const string INT   = "INT";

//运算符
const string ASSIGN   = "=";
const string PLUS     = "+";
const string MINUS    = "-";
const string ASTERISK = "*";
const string SLASH    = "/";

//分隔符
const string SEMICOLON = ";";
const string LPAREN = "(";
const string RPAREN = ")";
const string LBRACE = "{";
const string RBRACE = "}";

//关键字
const string ILLEGAL = "ILLEGAL";
const string END	 = "END";
const string LET     = "LET";
const string VOID    = "VOID";


map<string, string> keywords{make_pair("let", LET), make_pair("void", VOID)};

class token
{
public:
    string Type;
    string Literal;    
    token(string tp, string lt);

};

token::token(string tp, string lt)
{
    Type = tp;
    Literal = lt;
}

string lookupIdent(string ident)
{
    if (keywords[ident] != "")
    {
        return keywords[ident];
    }
    return IDENT;
}