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
    int len_of_word = this->word.length();
    if (index < len_of_word)
        return this->word[index];
    else
        return 'e';
}

bool AutomataExecution::existCharInWordPosition(int index)
{
    return index < this->word.length();
}

bool AutomataExecution::singleTransitionMustMove
(
    TransitionPossibility possibility
)
{
    if (possibility.transition.inputSymbol != 'e')
        return true;

    //possibility.transition.inputSymbol == 'e'

    if (theEntireWordHasBeenProcessed() == false)
        return true;

    //theEntireWordHasBeenProcessed() == true
    if (theStackIsEmpty() == false)
        return true;

    return false; //Pode aceitar a palavra
}

bool AutomataExecution::theCurrentStateIsAFinalState()
{
    auto it = std::find(
        this->automataInstance.vectorOfAcceptanceStateIds.begin(),
        this->automataInstance.vectorOfAcceptanceStateIds.end(),
        this->current_state
    );
    return it != this->automataInstance.vectorOfAcceptanceStateIds.end();
}

bool AutomataExecution::theEntireWordHasBeenProcessed()
{
    return this->id_of_processed_char_input == this->word.length()-1;
}

bool AutomataExecution::theStackIsEmpty()
{
    return this->char_stack.length() == 0;
}

bool AutomataExecution::process_word(const std::string &word)
{
    reset_indexes();
    this->word = word;
    this->current_state = this->automataInstance.start_state;

    draw_automata_considering_input_1p("Before to read any input", 0);

    while (true)
    {
        char topCharInStack = getTopCharInStack();
        char charInWord = getCharInWord(this->id_of_processed_char_input+1);

        //Get all of the possible transitions
        std::vector<TransitionPossibility> possibleTransitions = getAvailableTransitions
        (
            this->current_state,
            topCharInStack,
            charInWord,
            existCharInWordPosition(this->id_of_processed_char_input+1)
        );

        if (possibleTransitions.size() == 0)
        {
            //If it is a final state, with an empty stack and the entire word has been processed, accept
            //Searches for index in acceptance state vector
            auto it = std::find(
                this->automataInstance.vectorOfAcceptanceStateIds.begin(),
                this->automataInstance.vectorOfAcceptanceStateIds.end(),
                this->current_state
            );
            if (
                it != this->automataInstance.vectorOfAcceptanceStateIds.end() &&
                this->char_stack.length() == 0 &&
                (this->id_of_processed_char_input == this->word.length()-1)
            )
            {
                draw_automata_considering_input_1p("The word was accepted", 1);
                return true; //The word was accepted
            }
            else
            {
                draw_automata_considering_input_1p("The word was rejected", 2);
                return false; //The word was rejected
            }
        }
        else
        {
            TransitionPossibility chosen;

            if (possibleTransitions.size() == 1)
            {
                chosen = possibleTransitions[0];

                std::cout << "### A single one transition is possible. " << std::endl;
                std::cout << "Going from state "+std::to_string(chosen.origin_state)+
                             " to "+std::to_string(chosen.destiny_state) << std::endl;
                std::cout << "The transition is: ";
                std::cout << std::string(1, chosen.transition.inputSymbol)+
                             " , "+std::string(1, chosen.transition.topOfStackSymbolToBeReplaced)+
                             " -> "+std::string(1, chosen.transition.topOfStackSymbolToReplace)
                          << std::endl << std::endl;

                std::cout.flush();

                //Verify if must follow the single transition
                bool ret = singleTransitionMustMove(possibleTransitions[0]);
                if (ret == false)
                {
                    //The word can already be accepted
                    std::cout << "The word can already be accepted. " << std::endl;
                    draw_automata_considering_input_1p("The word was accepted", 1);
                    return true;
                }
                else
                {
                    std::cout << "Following the transition. " << std::endl;
                }
            }
            else
            {
                std::cout << "### More than one transition is possible. Possibilities: " << std::endl;
                for (int index = 0; index < possibleTransitions.size(); ++index)
                {
                    TransitionPossibility possible = possibleTransitions[index];
                    std::cout << "Type "+std::to_string(index) << " to choose: ";
                    std::cout << "Origin: state "+std::to_string(possible.origin_state) <<
                                 " Destiny: state "+std::to_string(possible.destiny_state);
                    std::cout << " -- Transition: " << std::string(1, possible.transition.inputSymbol)+
                                 " , "+std::string(1, possible.transition.topOfStackSymbolToBeReplaced)+
                                 " -> "+std::string(1, possible.transition.topOfStackSymbolToReplace) <<
                                 std::endl;
                }
                std::cout << "Which one must be chosen? " << std::endl;
                std::cout.flush();

                int escolha = read_number_betwen_0_and_max(possibleTransitions.size()-1);

                chosen = possibleTransitions[escolha];

                std::cout << "Going from state "+std::to_string(chosen.origin_state)+
                             " to "+std::to_string(chosen.destiny_state) << std::endl;
                std::cout << "The selected transition is: ";
                std::cout << std::string(1, chosen.transition.inputSymbol)+
                             " , "+std::string(1, chosen.transition.topOfStackSymbolToBeReplaced)+
                             " -> "+std::string(1, chosen.transition.topOfStackSymbolToReplace)
                          << std::endl << std::endl;

                std::cout.flush();
            }

            this->current_state = chosen.destiny_state;


            if (chosen.transition.inputSymbol == 'e')
            {
                //Does not consume input
            }
            else
            {
                //consume input
                this->id_of_processed_char_input++;
            }

            if (chosen.transition.topOfStackSymbolToBeReplaced == 'e' &&
                    chosen.transition.topOfStackSymbolToReplace == 'e')
            {
                //You don't need to do anything
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

            std::string msg = "After read '"+std::string(1, chosen.transition.inputSymbol)+"'";

            draw_automata_considering_input_1p(msg, 0);
        }
    }
}

int AutomataExecution::read_number_betwen_0_and_max(int numeroMaximo)
{
    int numero;
    std::cout << "Enter an integer between 0 and " << numeroMaximo << std::endl;
    std::cin >> numero;

    while(std::cin.fail() || numero < 0 || numero > numeroMaximo)
    {
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Enter an integer between 0 and " << numeroMaximo << std::endl;
        std::cin >> numero;
    }
    std::cout << "The number entered was: " << numero << std::endl;
    return numero;
}

void AutomataExecution::draw_automata_0p()
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image = this->automataInstance.nameOfAutomata+".png";
    draw_automata_2p(local_url, name_of_image);
}


//0: still processing
//1: accepted
//2: rejected
void AutomataExecution::draw_automata_considering_input_1p(const std::string& msg, int write_acceptance_status)
{
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/pushdown_automata/PA/images";
    std::string name_of_image =
            this->automataInstance.nameOfAutomata+"_"+
            std::to_string(this->internal_increment+1)+".png";

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

    content += "\tsubgraph cluster_0 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";
    content += "struct1 [label=<<TABLE>\n";
    content += "<TR>\n";

    for(int index = 0; index < this->word.size();++index)
    {
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

    if (this->word.length() == 0)
    {
        content += "<TD width=\"50\" height=\"10\"> </TD>";
    }

    content += "</TR>\n";
    content += "</TABLE>>];\n";
    content += "label = \"Word\";\n";
    content += "color=red;\n";
    content += "}\n";

    //inicio de desenhando stack
    content += "\tsubgraph cluster_2 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";

    int stack_len = this->char_stack.length();
    if (stack_len > 0)
    {
        content += "struct2 [label=<<TABLE>\n";
        for (int index = stack_len - 1; index > -1; index--)
        {
            content += "<TR>\n";
            content += "<TD>\n";
            content += this->char_stack[index];
            content += "</TD>\n";
            content += "</TR>\n";
        }
        content += "</TABLE>>];\n";
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
    return std::string(1, c);
}
