#include "automataexecution.h"

#include <algorithm>    // std::find
#include <fstream>

AutomataExecution::AutomataExecution(const AutomataInstance& automataInstance):
    automataInstance(automataInstance)
{

}

void AutomataExecution::reset_indexes()
{
    this->current_state = -1; //Must be initialized with the initial state of the machine
    this->id_of_processed_char_input = -1; //in the state none of the input char was processed
}

bool AutomataExecution::process_word(const std::string &word)
{
    reset_indexes();

    for (
         this->id_of_processed_char_input = 0;
         this->id_of_processed_char_input < word.size();
         this->id_of_processed_char_input++
    )
    {
        //Get all of the possible transitions
    }
}

void AutomataExecution::draw_automata()
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image = this->automataInstance.nameOfAutomata+".png";
    draw_automata(local_url, name_of_image);
}

void AutomataExecution::write_to_file(const std::string &url, const std::string &content)
{
    std::ofstream myfile;
    myfile.open (url);
    myfile << content;
    myfile.close();
}

void AutomataExecution::draw_automata(const std::string& local_url, const std::string &url)
{
    std::string content = produce_content_of_draw();
    write_to_file(local_url+"/file.dot", content);
    std::string command = "dot "+local_url+"/file.dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());
}

std::string AutomataExecution::produce_content_of_draw()
{
    std::string content = "digraph G {\n";
    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Turing Machine: "+this->automataInstance.nameOfAutomata+"\"\n"
        "\t\tcolor=blue;\n"
        "\n";

    for (int index = 0; index < this->automataInstance.structure.size(); ++index)
    {
        //Searches for index in acceptance state vector
        auto it = std::find(
            this->automataInstance.vectorOfAcceptanceStateIds.begin(),
            this->automataInstance.vectorOfAcceptanceStateIds.end(),
            index
        );
        if (it != this->automataInstance.vectorOfAcceptanceStateIds.end())
            content += "\t\tq"+std::to_string(index)+" [shape=\"doublecircle\"];\n";
        else
            content += "\t\tq"+std::to_string(index)+";\n";
    }

    for (int index = 0; index < this->automataInstance.structure.size(); ++index)
    {
        for (int index2 = 0; index2 < this->automataInstance.structure.size(); ++index2)
        {
            std::string s;
            std::vector<Transition> transitions = getTransitionsOfXStateToYState(index, index2);

            if (transitions.size() == 0)
                continue;

            for (int entryindex = 0;entryindex<transitions.size();entryindex++)
            {
                auto entry = transitions[entryindex];

                std::string tmp = std::string(1, entry.inputSymbol)+
                        ","+std::string(1, entry.topOfStackSymbolToBeReplaced)+
                        " -> "+std::string(1, entry.topOfStackSymbolToReplace);
                if (entryindex == 0)
                    s = tmp;
                else
                    s = s + "\n" + tmp;

            }

            content += "\t\tq"+std::to_string(index)+"->q"+std::to_string(index2)+
                    "[label=\""+s+"\"];\n";
        }
    }

    content += "x [color=white, label=\"\"];";
    content += "\t\tx->q"+std::to_string(this->automataInstance.start_state);

    content += "\t}\n"
        "\n"
        "}";

    return content;
}

std::vector<Transition> AutomataExecution::getTransitionsOfXStateToYState(int x, int y)
{
    return this->automataInstance.structure[x][y];
}
