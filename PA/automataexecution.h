#ifndef AUTOMATAEXECUTION_H
#define AUTOMATAEXECUTION_H

#include "automatainstance.h"

class AutomataExecution
{
public:
    AutomataExecution(const AutomataInstance& automataInstance);

    void draw_automata();

    void draw_automata_considering_input(const std::string& msg);

    bool process_word(const std::string& word);

private:
    int current_state = -1; //Must be initialized with the initial state of the machine
    int id_of_processed_char_input = -1; //in the state none of the input char was processed
    std::string char_stack; //Inserts and removes in the end

    AutomataInstance automataInstance;

    std::string word;

    void reset_indexes();

    void draw_automata(
        const std::string& local_url,
        const std::string &url
    );

    void draw_automata(
        const std::string& local_url,
        const std::string &url,
        const std::string& content
    );

    void draw_automata_considering_input(
        const std::string& local_url,
        const std::string &url,
        const std::string& content
    );

    void write_to_file(const std::string &url, const std::string &content);

    std::string produce_content_of_draw();

    std::vector<Transition> getTransitionsOfXStateToYState(int x, int y);

    std::string produce_content_of_draw_considering_input
    (
        const std::string &message,
        int write_acceptance_status = 0
    );

    std::string getCharTransformedAsString(char c);
};

#endif // AUTOMATAEXECUTION_H
