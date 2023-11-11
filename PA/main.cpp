#include <iostream>

using namespace std;

#include <automataexecution.h>
#include <automatainstance.h>
#include <pushdownautomatasamples.h>

int main()
{
    AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_1());
    automataExecution.draw_automata();

    return 0;
}
