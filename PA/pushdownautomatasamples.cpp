#include "pushdownautomatasamples.h"

PushdownAutomataSamples::PushdownAutomataSamples()
{

}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_1()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','$')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {Transition('0','e','0')}, //vector arriving at 1
            {Transition('1','0','e')},  //vector arriving at 2
            {} //vector arriving at 3
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('1','0','e')},  //vector arriving at 2
            {Transition('e','$','e')}, //vector arriving at 3
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {} //vector arriving at 3
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
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','$')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {Transition('0','e','0'), Transition('1','e','1')}, //vector arriving at 1
            {Transition('e','e','e')},  //vector arriving at 2
            {} //vector arriving at 3
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('0','0','e'),Transition('1','1','e')},  //vector arriving at 2
            {Transition('e','$','e')}, //vector arriving at 3
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {} //vector arriving at 3
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
