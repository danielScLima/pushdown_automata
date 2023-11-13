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
        "Example_1"                     //nameOfAutomata
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
        "Example_2"                     //nameOfAutomata
    );
}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_3()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','$')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {Transition('0','e','0')}, //vector arriving at 1
            {Transition('e','e','e')},  //vector arriving at 2
            {}, //vector arriving at 3
            {Transition('e','e','e')}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('1','0','e')},  //vector arriving at 2
            {Transition('e','$','e')}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {Transition('2','e','e')}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
        },

        //vector starting from 4
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {Transition('1','e','e')}, //vector arriving at 4
            {Transition('e','e','e')}, //vector arriving at 5
            {}, //vector arriving at 6
        },

        //vector starting from 5
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {Transition('2','0','e')}, //vector arriving at 5
            {Transition('e','$','e')}, //vector arriving at 6
        },

        //vector starting from 6
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {3, 6};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_3"                     //nameOfAutomata
    );
}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_4()
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

    std::vector<int> vectorOfAcceptanceStateIds = {0, 3};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_4"                     //nameOfAutomata
    );
}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_5()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','e')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {Transition('e','e','e')}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('e','e','$')},  //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('a','e','a')},  //vector arriving at 2
            {Transition('b','a','e')}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {Transition('b','a','e')}, //vector arriving at 3
            {Transition('e','$','e')}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 4
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 5
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {Transition('e','e','$')}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 6
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {Transition('b','e','b')}, //vector arriving at 6
            {Transition('a','b','e')}, //vector arriving at 7
            {}, //vector arriving at 8
        },

        //vector starting from 7
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {Transition('a','b','e')}, //vector arriving at 7
            {Transition('e','$','e')}, //vector arriving at 8
        },

        //vector starting from 8
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
            {}, //vector arriving at 5
            {}, //vector arriving at 6
            {}, //vector arriving at 7
            {}, //vector arriving at 8
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {1, 4, 5, 8};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_5"                     //nameOfAutomata
    );
}

AutomataInstance PushdownAutomataSamples::get_structure_of_sample_6()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','$')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {Transition('b','a','e'), Transition('a','b','e')}, //vector arriving at 1
            {Transition('a','a','a'), Transition('a','$','$')},  //vector arriving at 2
            {Transition('e','$','e')}, //vector arriving at 3
            {Transition('b','$','$'), Transition('b','b','b')}, //vector arriving at 4
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {Transition('e','e','a')}, //vector arriving at 1
            {},  //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 4
        {
            {}, //vector arriving at 0
            {Transition('e','e','b')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {3};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_6"                     //nameOfAutomata
    );
}


AutomataInstance PushdownAutomataSamples::get_structure_of_sample_7()
{
    std::vector<std::vector<std::vector<Transition>>> st = {
        //vector starting from 0
        {
            {}, //vector arriving at 0
            {Transition('e','e','$')}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 1
        {
            {}, //vector arriving at 0
            {Transition('a','e','a')}, //vector arriving at 1
            {Transition('e','e','e')},  //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 2
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {Transition('b','e','a')},  //vector arriving at 2
            {Transition('e','e','e')}, //vector arriving at 3
            {}, //vector arriving at 4
        },

        //vector starting from 3
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {Transition('a','a','e')}, //vector arriving at 3
            {Transition('e','$','e')}, //vector arriving at 4
        },

        //vector starting from 4
        {
            {}, //vector arriving at 0
            {}, //vector arriving at 1
            {}, //vector arriving at 2
            {}, //vector arriving at 3
            {}, //vector arriving at 4
        },
    };

    std::vector<int> vectorOfAcceptanceStateIds = {4};

    return AutomataInstance(
        st,                             //structure
        0,                              //start_state
        vectorOfAcceptanceStateIds,     //vectorOfAcceptanceStateIds
        "Example_7"                     //nameOfAutomata
    );
}
