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
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_3());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("012");
    //automataExecution.process_word("001122");
    //automataExecution.process_word("000111222");
    //automataExecution.process_word("01");
    //automataExecution.process_word("02");
    //automataExecution.process_word("0012");
    //automataExecution.process_word("011222");

    //Example 4
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_4());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("01");
    //automataExecution.process_word("0011");
    //automataExecution.process_word("000111");
    //automataExecution.process_word("0");
    //automataExecution.process_word("1");
    //automataExecution.process_word("001");
    //automataExecution.process_word("");

    //Example 5
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_5());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("");
    //automataExecution.process_word("ab");
    //automataExecution.process_word("ba");
    //automataExecution.process_word("aabb");
    //automataExecution.process_word("bbaa");
    //automataExecution.process_word("aab");
    //automataExecution.process_word("abaa");

    //Example 6
    //AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_6());
    //automataExecution.draw_automata_0p();

    //automataExecution.process_word("");
    //automataExecution.process_word("ab");
    //automataExecution.process_word("ba");
    //automataExecution.process_word("aabb");
    //automataExecution.process_word("bbaa");
    //automataExecution.process_word("aab");
    //automataExecution.process_word("abaa");

    //Example 7
    AutomataExecution automataExecution(PushdownAutomataSamples::get_structure_of_sample_7());
    automataExecution.draw_automata_0p();

    //automataExecution.process_word("");
    //automataExecution.process_word("abaa");
    //automataExecution.process_word("aabbaaaa");
    //automataExecution.process_word("ab");
    //automataExecution.process_word("aba");
    //automataExecution.process_word("ba");
    automataExecution.process_word("baa");

    return 0;
}
