#include <iostream>

using namespace std;

#include <automataexecution.h>
#include <automatainstance.h>
#include <pushdownautomatasamples.h>

int main()
{
    //Example 1
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_1());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("01");
    //automataExecution.process_word("0011");
    //automataExecution.process_word("000111");
    //automataExecution.process_word("0");
    //automataExecution.process_word("1");
    //automataExecution.process_word("001");
    //automataExecution.process_word("011");

    //Example 2
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_2());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("00");
    //automataExecution.process_word("0110");
    //automataExecution.process_word("010010");
    //automataExecution.process_word("01");
    //automataExecution.process_word("001");
    //automataExecution.process_word("010");
    //automataExecution.process_word("0101");

    //Example 3
    AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_3());
    automataExecution.draw_automata_0p();

    //automataExecution.process_word("012");
    //automataExecution.process_word("001122");
    //automataExecution.process_word("000111222");
    //automataExecution.process_word("01");
    //automataExecution.process_word("02");
    //automataExecution.process_word("0012");
    automataExecution.process_word("011222");

    //Example 4
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_4());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("");

    return 0;
}
