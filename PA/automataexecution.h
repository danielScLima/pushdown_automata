#ifndef AUTOMATAEXECUTION_H
#define AUTOMATAEXECUTION_H

#include "automatainstance.h"
#include "transitionpossibility.h"

class AutomataExecution
{
public:
    AutomataExecution(const AutomataInstance& automataInstance);

    void draw_automata_0p();

    void draw_automata_considering_input_1p(const std::string& msg, int write_acceptance_status);

    bool process_word(const std::string& word);

    char getTopCharInStack();
    char getCharInWord(int index);
    bool existCharInWordPosition(int index);

    bool test1_remove_later(const std::string &word);

private:
    int current_state = -1; //Must be initialized with the initial state of the machine
    int id_of_processed_char_input = -1; //in the state none of the input char was processed
    std::string char_stack = ""; //Inserts and removes in the end

    AutomataInstance automataInstance;

    std::string word = "";

    int internal_increment = 0;

    void reset_indexes();

    void draw_automata_2p(
        const std::string& local_url,
        const std::string &url
    );

    void draw_automata_3p(
        const std::string& local_url,
        const std::string &url,
        const std::string& content
    );

    void draw_automata_considering_input_3p(
        const std::string& local_url,
        const std::string &url,
        const std::string& content
    );

    void write_to_file(const std::string &url, const std::string &content);

    std::string produce_content_of_draw();

    std::vector<Transition> getTransitionsOfXStateToYState(int x, int y);

    std::vector<TransitionPossibility> getAvailableTransitions
    (
        int currentStateParameter,
        char topOfStack,
        char inputToBeProcessed,
        bool wordBeeingProcessed
    );

    std::string produce_content_of_draw_considering_input
    (
        const std::string &message,
        int write_acceptance_status = 0
    );

    std::string getCharTransformedAsString(char c);

    int read_number_betwen_0_and_max(int numeroMaximo);
};

#endif // AUTOMATAEXECUTION_H
