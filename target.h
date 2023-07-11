#include "semantic.h"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

void printTarget(vector<semType> smtc)
{
    std::cout << "Target code: \n";
    std::cout << "CODE: \n";
    std::cout << "START: \n";
    std::cout << "  MOV AX, DATA \n";
    std::cout << "  MOV DS, AX \n";
    for (auto x: smtc)
    {
        if (x.op == ASSIGN)
        {
            std::cout << "  MOV AX, " << x.arg1 << "\n";
            std::cout << "  MOV " << x.res << ", AX\n";
        }
        else if (x.op == PLUS)
        {
            std::cout << "  MOV AX, " << x.arg1 << "\n";
            std::cout << "  ADD AX, " << x.arg2 << "\n";
            std::cout << "  MOV " << x.res << ", AX\n";
        }
        else if (x.op == MINUS)
        {
            std::cout << "  MOV AX, " << x.arg1 << "\n";
            std::cout << "  SUB AX, " << x.arg2 << "\n";
            std::cout << "  MOV " << x.res << ", AX\n";
        }
        else if (x.op == ASTERISK)
        {
            std::cout << "  MOV AX, " << x.arg1 << "\n";
            std::cout << "  MOV BX, " << x.arg2 << "\n";
            std::cout << "  MUL BX\n";
            std::cout << "  MOV " << x.res << ", AX\n"; 
        }
        else if (x.op == SLASH)
        {
            std::cout << "  MOV AX, " << x.arg1 << "\n";
            std::cout << "  MOV BX, " << x.arg2 << "\n";
            std::cout << "  DIV BX\n";
            std::cout << "  MOV " << x.res << ", AX\n"; 
        }
    }
    std::cout << "CODE ENDS\n";
    std::cout << "END START\n";
}