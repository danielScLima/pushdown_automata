#include "pushdownautomatasamples.h"

PushdownAutomataSamples::PushdownAutomataSamples()
{

}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_1()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vetor partindo 0
        {
            {}, //vetor chegando no 0
            {Transition('e','e','$')}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {}, //vetor chegando no 3
        },

        //vetor partindo do 1
        {
            {}, //vetor chegando no 0
            {Transition('0','e','0')}, //vetor chegando no 1
            {Transition('1','0','e')},  //vetor chegando no 2
            {} //vetor chegando no 3
        },

        //vetor partindo do 2
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {Transition('1','0','e')},  //vetor chegando no 2
            {Transition('e','$','e')}, //vetor chegando no 3
        },

        //vetor partindo do 3
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {} //vetor chegando no 3
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {3};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_A"                     //nameOfAutomata
    );
}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_2()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vetor partindo 0
        {
            {}, //vetor chegando no 0
            {Transition('e','e','$')}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {}, //vetor chegando no 3
        },

        //vetor partindo do 1
        {
            {}, //vetor chegando no 0
            {Transition('0','e','0'), Transition('1','e','1')}, //vetor chegando no 1
            {Transition('e','e','e')},  //vetor chegando no 2
            {} //vetor chegando no 3
        },

        //vetor partindo do 2
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {Transition('0','0','e'),Transition('1','1','e')},  //vetor chegando no 2
            {Transition('e','$','e')}, //vetor chegando no 3
        },

        //vetor partindo do 3
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {} //vetor chegando no 3
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {3};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_B"                     //nameOfAutomata
    );
}
