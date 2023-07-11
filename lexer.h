#include "token.h"

using std::string;
using std::vector;
using std::map;
using std::set;


class lexer
{
public:
    string input;
    int position;
    int readPosition;
    char ch;
    lexer(string in);
    void readChar();
    token nextToken();
    string readIndentifier();
    string readNumber();
    void skipWhitespace();
};

bool isLetter(char ch)
{
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool isDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}

lexer::lexer(string in)
{
    input = in;
    position = readPosition = 0;
    ch = 0;
    readChar();
}

void lexer::readChar()
{
    if (readPosition >= input.length())
    {
        ch = 0;
    }
    else
    {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition += 1;
}

token lexer::nextToken()
{
    token tok = token("", "");
    skipWhitespace();
    string c;
    c += ch;
    switch (ch)
    {
    case '=':
        tok = token(ASSIGN, c);
        break;
    case '-':
        tok = token(MINUS, c);
        break;
    case '+':
        tok = token(PLUS, c);
        break;
    case '/':
        tok = token(SLASH, c);
        break;
    case '*':
        tok = token(ASTERISK, c);
        break;
    case ';':
        tok = token(SEMICOLON, c);
        break;
    case '(':
        tok = token(LPAREN, c);
        break;
    case ')':
        tok = token(RPAREN, c);
        break;
    case '{':
        tok = token(LBRACE, c);
        break;
    case '}':
        tok = token(RBRACE, c);
        break;
    case 0:
        tok = token(END, "");
        break;
    default:
        if (isLetter(ch))
        {
            tok.Literal = readIndentifier();
            tok.Type = lookupIdent(tok.Literal);
            return tok;
        }
        else if (isDigit(ch))
        {
            tok.Type = INT;
            tok.Literal = readNumber();
            return tok;
        }
        else
        {
            tok = token(ILLEGAL, c);
        }
        break;
    }
    readChar();
    return tok;
}

string lexer::readIndentifier()
{
    int lastPosition = position;
    while (isLetter(ch))
    {
        readChar();
    }
    string ret;
    for (int i = lastPosition; i < position; i++)
    {
        ret += input[i];
    }
    return ret;
}

string lexer::readNumber()
{
    int lastPosition = position;
    while (isDigit(ch))
    {
        readChar();
    }
    string ret;
    for (int i = lastPosition; i < position; i++)
    {
        ret += input[i];
    }
    return ret;
}

void lexer::skipWhitespace()
{
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        readChar();
    }
}

vector<token> getLexerAns(string in)
{
    lexer l = lexer(in);
    token x = token("", "");
    vector<token> ret;
    do
    {
        x = l.nextToken();
        ret.push_back(x);
    } while (x.Type != END);
    return ret;
}

void printLexerAns(vector<token> ret)
{
    std::cout << "Lexer result: " << '\n';
    for (auto x: ret)
    {
        std::cout << "(Type: " << x.Type << ", " << "Literal: " << x.Literal << "}" << '\n';
    }
    std::cout << '\n';
}