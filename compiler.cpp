#include "target.h"

using std::string;
using std::vector;
using std::map;
using std::set;

int main()
{
    string in = "void main(){let a = 1; a = 10 + 11 * (12 + 13); let b = 2; b = a * 100;}";
    auto l = getLexerAns(in);
    printLexerAns(l);


    auto newGrammar = eliminateLeftRecursion(grammar);
    printGrammar(newGrammar);
    auto firstSet = getFirstSet(newGrammar);
    printFirstSet(firstSet);
    auto followSet = getFollowSet(newGrammar, firstSet);
    printFollowSet(followSet);


    auto doubletable = getParserTable(newGrammar, firstSet, followSet);
    auto showtable = doubletable.first;
    auto parsertable = doubletable.second;
    printParserTable(newGrammar, showtable);
    doParserAnalyze(l, parsertable, newGrammar);

    
    auto smtc = getSemanticAns(l, parsertable, newGrammar);
    printSemanticAns(smtc);
    printTarget(smtc);
    return 0;
}