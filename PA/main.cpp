#include <iostream>

using namespace std;

#include <automataexecution.h>
#include <automatainstance.h>
#include <pushdownautomatasamples.h>

int main()
{
    AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_1());
    automataExecution.draw_automata_0p();

    automataExecution.process_word("01");
    //automataExecution.process_word("000111");
    //automataExecution.test1_remove_later("00001111");

    return 0;
}
