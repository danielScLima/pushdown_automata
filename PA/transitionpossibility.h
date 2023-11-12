#ifndef TRANSITIONPOSSIBILITY_H
#define TRANSITIONPOSSIBILITY_H

#include <transition.h>

struct TransitionPossibility
{
    TransitionPossibility():
        transition(Transition(' ',' ',' '))
    {}

    TransitionPossibility
    (
        int origin_state,
        int destiny_state,
        Transition transition
    ): transition(transition)
    {
        this->origin_state = origin_state;
        this->destiny_state = destiny_state;
    }

    int origin_state;
    int destiny_state;
    Transition transition;
};

#endif // TRANSITIONPOSSIBILITY_H
