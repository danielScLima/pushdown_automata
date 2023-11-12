#include "automataexecution.h"

#include <algorithm>    // std::find
#include <fstream>

#include <iostream>

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

char AutomataExecution::getTopCharInStack()
{
    if (this->char_stack.length() == 0)
        return 'e';
    else
    {
        char b = this->char_stack.back();
        return b;
    }
}

char AutomataExecution::getCharInWord(int index)
{
    if (index < this->word.length() == 0)
        return this->word[index];
    else
        return 'e';
}

bool AutomataExecution::existCharInWordPosition(int index)
{
    return index < this->word.length();
}

bool AutomataExecution::process_word(const std::string &word)
{
    reset_indexes();
    this->word = word;
    this->current_state = this->automataInstance.start_state;

    draw_automata_considering_input_1p("Before to read any input");

    int wordLen =  word.length();
    std::cout << "wordLen: " << wordLen << std::endl;
    std::cout << "this->id_of_processed_char_input: " << this->id_of_processed_char_input << std::endl;

    //for (
         //this->id_of_processed_char_input = 0
    //     ;
    //     this->id_of_processed_char_input < wordLen;
         //this->id_of_processed_char_input++
    //)
    while (true)
    {
        std::cout << "? "<< std::endl;

        std::cout << "Stack '" << this->char_stack << "'" << std::endl;

        //Get all of the possible transitions
        std::vector<TransitionPossibility> possibleTransitions = getAvailableTransitions
        (
            this->current_state,
            //this->char_stack.back(),
            getTopCharInStack(),
            //word[this->id_of_processed_char_input+1]
            getCharInWord(this->id_of_processed_char_input+1),
            existCharInWordPosition(this->id_of_processed_char_input+1)
        );

        std::cout << "Quant de transitions: " << possibleTransitions.size() << std::endl;

        if (possibleTransitions.size() == 0)
        {
            //Se for estado final, com pilha vazia e palavra toda processada, aceita
            //Searches for index in acceptance state vector
            auto it = std::find(
                this->automataInstance.vectorOfAcceptanceStateIds.begin(),
                this->automataInstance.vectorOfAcceptanceStateIds.end(),
                this->current_state
            );
            if (it != this->automataInstance.vectorOfAcceptanceStateIds.end() &&
                    this->char_stack.length() == 0 &&
                    (this->id_of_processed_char_input+1 > this->word.length()))
                return true; //word foi aceita
            else
                return false; //word NÃO foi aceita
        }
        else
        {
            TransitionPossibility chosen;

            std::cout << "PA " << std::endl;

            if (possibleTransitions.size() == 1)
            {
                std::cout << "PB " << std::endl;
                //só tem uma transição a fazer
                chosen = possibleTransitions[0];
            }
            else
            {
                std::cout << "PC " << std::endl;
                //Existe mais do que uma transição
                //Perguntar ao usuario qual usar
                int escolha = 0;
                chosen = possibleTransitions[escolha];
            }

            this->current_state = chosen.destiny_state;


            if (chosen.transition.inputSymbol == 'e')
            {
                //Não consome entrada
            }
            else
            {
                //Consome entrada
                this->id_of_processed_char_input++;
            }

            if (chosen.transition.topOfStackSymbolToBeReplaced == 'e' &&
                    chosen.transition.topOfStackSymbolToReplace == 'e')
            {
                //Não precisa fazer nada
            }
            else if (chosen.transition.topOfStackSymbolToBeReplaced != 'e' &&
                     chosen.transition.topOfStackSymbolToReplace != 'e')
            {
                this->char_stack[this->char_stack.size()-1] =
                   chosen.transition.topOfStackSymbolToReplace;
            }
            else if (chosen.transition.topOfStackSymbolToBeReplaced == 'e' &&
                     chosen.transition.topOfStackSymbolToReplace != 'e')
            {
                this->char_stack.push_back(chosen.transition.topOfStackSymbolToReplace);
            }
            else if (chosen.transition.topOfStackSymbolToBeReplaced != 'e' &&
                     chosen.transition.topOfStackSymbolToReplace == 'e')
            {
                this->char_stack.pop_back();
            }


            /*if (chosen.transition.inputSymbol == 'e' &&
                chosen.transition.topOfStackSymbolToBeReplaced == 'e')
            {
                if (chosen.transition.topOfStackSymbolToReplace != 'e')
                {
                    //this->id_of_processed_char_input++;
                    this->char_stack.push_back(chosen.transition.topOfStackSymbolToReplace);
                }
            }
            else if (chosen.transition.topOfStackSymbolToBeReplaced == 'e' &&
                chosen.transition.topOfStackSymbolToReplace == 'e')
            {} //nada a fazer
            else if (chosen.transition.topOfStackSymbolToReplace == 'e')
            {
                this->id_of_processed_char_input++;
                this->char_stack.pop_back();
            }
            else if (chosen.transition.topOfStackSymbolToBeReplaced == 'e')
            {
                this->id_of_processed_char_input++;
                this->char_stack.push_back(chosen.transition.topOfStackSymbolToReplace);
            }
            else
            {
                this->id_of_processed_char_input++;
                this->char_stack[this->char_stack.size()-1] =
                   chosen.transition.topOfStackSymbolToReplace;
            }*/

            std::string msg = "After read '"+std::string(1, chosen.transition.inputSymbol)+"'";

            std::cout << "PD " << std::endl;

            draw_automata_considering_input_1p(msg);
        }
    }

    draw_automata_considering_input_1p("End of processing");

    return true;
}

bool AutomataExecution::test1_remove_later(const std::string &word)
{
    reset_indexes();
    this->word = word;
    this->current_state = 1;
    this->char_stack = "000";

    draw_automata_considering_input_1p("After read 0");

    return true;
}

void AutomataExecution::draw_automata_0p()
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image = this->automataInstance.nameOfAutomata+".png";
    draw_automata_2p(local_url, name_of_image);
}

void AutomataExecution::draw_automata_considering_input_1p(const std::string& msg)
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image =
            this->automataInstance.nameOfAutomata+"_"+
            std::to_string(this->internal_increment+1)+".png";

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

    draw_automata_considering_input_3p(
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

void AutomataExecution::draw_automata_2p(const std::string& local_url, const std::string &url)
{
    std::string content = produce_content_of_draw();

    draw_automata_3p(
        local_url,
        url,
        content
    );
}

void AutomataExecution::draw_automata_3p(
    const std::string& local_url,
    const std::string &url,
    const std::string& content
)
{
    write_to_file(local_url+"/file.dot", content);
    std::string command = "dot "+local_url+"/file.dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());
}

void AutomataExecution::draw_automata_considering_input_3p(
    const std::string& local_url,
    const std::string &url,
    const std::string& content
)
{
    write_to_file(local_url+"/file"+std::to_string(this->internal_increment+1)+
                  ".dot", content);
    std::string command = "dot "+local_url+"/file"+std::to_string(this->internal_increment+1)+
            ".dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());

    this->internal_increment++;
}

std::string AutomataExecution::produce_content_of_draw()
{
    std::string content = "digraph G {\n";
    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Pushdown automata: "+this->automataInstance.nameOfAutomata+"\"\n"
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

std::vector<TransitionPossibility> AutomataExecution::getAvailableTransitions
(
    int currentStateParameter,
    char topOfStack,
    char inputToBeProcessed,
    bool wordBeeingProcessed
)
{
    std::vector<std::vector<Transition>> transitionsLeavingCurentState =
            this->automataInstance.structure[currentStateParameter];

    std::vector<TransitionPossibility> selectedTransitions;

    for(int destIndex = 0; destIndex < transitionsLeavingCurentState.size(); destIndex++)
    {
        auto entry = transitionsLeavingCurentState[destIndex];
        for(int index = 0; index < entry.size(); ++index)
        {
            Transition transition = entry[index];

            if (inputToBeProcessed == transition.inputSymbol &&
                topOfStack == transition.topOfStackSymbolToBeReplaced)
            {
                selectedTransitions.push_back(
                    TransitionPossibility(
                        currentStateParameter,      //origin_state
                        destIndex,                  //destiny_state,
                        transition                  //transition
                    )
                );
            }
            else if(transition.inputSymbol == 'e' &&
                    topOfStack == transition.topOfStackSymbolToBeReplaced)
            {
                selectedTransitions.push_back(
                    TransitionPossibility(
                        currentStateParameter,      //origin_state
                        destIndex,                  //destiny_state,
                        transition                  //transition
                    )
                );
            }
            else if (inputToBeProcessed == transition.inputSymbol &&
                     transition.topOfStackSymbolToBeReplaced == 'e')
            {
                selectedTransitions.push_back(
                    TransitionPossibility(
                        currentStateParameter,      //origin_state
                        destIndex,                  //destiny_state,
                        transition                  //transition
                    )
                );
            }
            else if (transition.inputSymbol == 'e' &&
                     transition.topOfStackSymbolToBeReplaced == 'e')
            {
                selectedTransitions.push_back(
                    TransitionPossibility(
                        currentStateParameter,      //origin_state
                        destIndex,                  //destiny_state,
                        transition                  //transition
                    )
                );
            }
        }
    }

    return selectedTransitions;
}

std::string AutomataExecution::produce_content_of_draw_considering_input
(
    const std::string &message,
    int write_acceptance_status
)
{
    std::string content = "digraph G {\n";

    std::cout << "x1 " << std::endl;

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

    std::cout << "x2 " << std::endl;

    content += "</TR>\n";
    content += "</TABLE>>];\n";
    content += "label = \"Word\";\n";
    content += "color=red;\n";
    content += "}\n";

    //inicio de desenhando stack
    content += "\tsubgraph cluster_2 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";

    std::cout << "x3 " << std::endl;

    int stack_len = this->char_stack.length();
    if (stack_len > 0)
    {
        std::cout << " aqui" << std::endl;
        std::cout << " tamanho: " << stack_len << std::endl;
        content += "struct2 [label=<<TABLE>\n";
        for (int index = stack_len - 1; index > -1; index--)
        {
            std::cout << " teste " << std::endl;

            content += "<TR>\n";
            content += "<TD>\n";
            content += this->char_stack[index];
            content += "</TD>\n";
            content += "</TR>\n";
        }
        content += "</TABLE>>];\n";

        std::cout << " aqui2" << std::endl;
    }
    else
    {
        content += "struct2 [label=<<TABLE>\n";

        content += "<TR>\n";
        content += "<TD width=\"10\" height=\"50\">\n";
        content += "";
        content += "</TD>\n";
        content += "</TR>\n";

        content += "</TABLE>>];\n";
    }


    content += "label = \"Stack top\";\n";
    content += "color=red;\n";
    content += "}\n";

    //fim de desenhando stack


    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Pushdown automata: "+this->automataInstance.nameOfAutomata+"\n"+message+"\"\n"
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
