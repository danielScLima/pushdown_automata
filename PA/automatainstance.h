#ifndef AUTOMATAINSTANCE_H
#define AUTOMATAINSTANCE_H

#include <vector>
#include <transition.h>
#include <string>

struct AutomataInstance
{
    AutomataInstance
    (
        std::vector<std::vector<std::vector<Transition>>> structure,
        int start_state,
        std::vector<int> vectorOfAcceptanceStateIds,
        std::string nameOfAutomata
    )
    {
        this->structure = structure;
        this->start_state = start_state;
        this->vectorOfAcceptanceStateIds = vectorOfAcceptanceStateIds;
        this->nameOfAutomata = nameOfAutomata;
    }

    std::vector<std::vector<std::vector<Transition>>> structure;
    int start_state;
    std::vector<int> vectorOfAcceptanceStateIds;
    std::string nameOfAutomata;
};

#endif // AUTOMATAINSTANCE_H
