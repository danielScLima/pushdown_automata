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
    this->word = "";
}

bool AutomataExecution::process_word(const std::string &word)
{
    reset_indexes();
    this->word = word;
    this->current_state = this->automataInstance.start_state;

    draw_automata_considering_input("Before to read any input");

    for (
         this->id_of_processed_char_input = 0;
         this->id_of_processed_char_input < word.size();
         this->id_of_processed_char_input++
    )
    {
        //Get all of the possible transitions
    }

    return true;
}

void AutomataExecution::draw_automata()
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image = this->automataInstance.nameOfAutomata+".png";
    draw_automata(local_url, name_of_image);
}

void AutomataExecution::draw_automata_considering_input(const std::string& msg)
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image =
            this->automataInstance.nameOfAutomata+"_"+std::to_string(this->id_of_processed_char_input+1)+".png";

    int write_acceptance_status = 0;

    if (this->id_of_processed_char_input == this->word.size())
    {
        if (this->char_stack.length() == 0)
            write_acceptance_status = 1;
        else
            write_acceptance_status = 2;
    }
    else {
        write_acceptance_status = 0;
    }

    std::string content = AutomataExecution::produce_content_of_draw_considering_input
    (
        msg,
        write_acceptance_status
    );

    draw_automata_considering_input(
        local_url,
        name_of_image,
        content
    );
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

    draw_automata(
        local_url,
        url,
        content
    );
}

void AutomataExecution::draw_automata(
    const std::string& local_url,
    const std::string &url,
    const std::string& content
)
{
    write_to_file(local_url+"/file.dot", content);
    std::string command = "dot "+local_url+"/file.dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());
}

void AutomataExecution::draw_automata_considering_input(
    const std::string& local_url,
    const std::string &url,
    const std::string& content
)
{
    write_to_file(local_url+"/file"+std::to_string(this->id_of_processed_char_input+1)+
                  ".dot", content);
    std::string command = "dot "+local_url+"/file"+std::to_string(this->id_of_processed_char_input+1)+
            ".dot -Tpng > "+local_url+"/"+url;
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

std::string AutomataExecution::produce_content_of_draw_considering_input
(
    const std::string &message,
    int write_acceptance_status
)
{
    std::string content = "digraph G {\n";

    content += "\tsubgraph cluster_0 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";
    content += "struct1 [label=<<TABLE>\n";
    content += "<TR>\n";

    for(int index = 0; index < this->word.size();++index)
    {
        //if (index == previous_input_symbol_index)
        if (index == this->id_of_processed_char_input)
        {
            content += "<TD BGCOLOR=\"gray\"><FONT>"+
                    getCharTransformedAsString(this->word[index])+"</FONT></TD>\n";
        }
        else
        {
            content += "<TD><FONT>"+getCharTransformedAsString(this->word[index])+"</FONT></TD>\n";
        }
    }

    content += "</TR>\n";
    content += "</TABLE>>];\n";
    content += "label = \"Word\";\n";
    content += "color=red;\n";
    content += "}\n";


    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Pushdown automata: "+message+"\"\n"
        "\t\tcolor=blue;\n"
        "\n";

    for (int index = 0; index < this->automataInstance.structure.size(); ++index)
    {
        if (index == this->current_state)
        {
            //Searches for index in acceptance state vector
            auto it = std::find(
                this->automataInstance.vectorOfAcceptanceStateIds.begin(),
                this->automataInstance.vectorOfAcceptanceStateIds.end(),
                index
            );
            if (it != this->automataInstance.vectorOfAcceptanceStateIds.end())
                content += "\t\tq"+std::to_string(index)+" [shape=\"doublecircle\",color=\"lightblue\"];\n";
            else
                content += "\t\tq"+std::to_string(index)+" [color=\"lightblue\"];\n";
        }
        else
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
        "\n";

    //inserir aceito ou rejeitado
    if (write_acceptance_status == 1)
    {
        content += "subgraph cluster_1s {\n"
                   "node [style=filled, shape=rect];\n"
                "cluster_1_n [label=\"Accepted word\", color=\"green\"];\n"
                "label = \"Status\";\n"
                "color=green;\n"
                "}\n"
                ;
    }
    else if(write_acceptance_status == 2)
    {
        content += "subgraph cluster_0s {\n"
                   "node [style=filled, shape=rect];\n"
                "cluster_0_n [label=\"Rejected word\", color=\"red\"];\n"
                "label = \"Status\";\n"
                "color=red;\n"
                "}\n"
                ;
    }

    content += "}";

    return content;
}

std::string AutomataExecution::getCharTransformedAsString(char c)
{
    //    if (c == '<')
    //        return std::string("&lt;");
    //    else if (c == '>')
    //        return std::string("&gt;");
    //    else
    //        return std::string(1, c);

    return std::string(1, c);
}
