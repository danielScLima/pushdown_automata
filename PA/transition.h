#ifndef TRANSITION_H
#define TRANSITION_H

struct Transition
{
    char inputSymbol;
    char topOfStackSymbolToBeReplaced;
    char topOfStackSymbolToReplace;

    Transition
    (
        char inputSymbol,
        char topOfStackSymbolToBeReplaced,
        char topOfStackSymbolToReplace
    )
    {
        this->inputSymbol = inputSymbol;
        this->topOfStackSymbolToBeReplaced = topOfStackSymbolToBeReplaced;
        this->topOfStackSymbolToReplace = topOfStackSymbolToReplace;
    }
};

#endif // TRANSITION_H
