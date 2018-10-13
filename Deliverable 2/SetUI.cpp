#include "SetUI.h"

SetUI::SetUI() { TopicScreen(); }

// Greet the user and shows the developer name.
void SetUI::TopicScreen() {
    system("clear");
    cout << "------------------------------------------------------------------"
            "----"
         << endl; // Replace the name with yours
    cout << "\033[1;31mSet Calculator\033[0m\nDeveloper Name: "
         << "\033[1;34mNelson Cook (ncoo162, 181796651)\033[0m\n";
    cout << "To know available commands, please type 'help'" << endl;
    cout << "------------------------------------------------------------------"
            "---"
         << endl;
}

bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr,
                         bool verbose) {
    /* Todo:
     *     This function is NOT completed.
     *     Reading the data from the input file is done.
     *     Use it to implement your logic.
     */

    string line;
    ifstream infile(filename.c_str());

    // return false if the file does not exist
    if (!infile.good())
        return false;

    getline(infile, line); // Get the first line to extract set members
    line.erase(0, 2);      // Remove '//' in the line

    cout << "Extracting set members from the first line: ";
    vector<string> element;
    int i = 0;
    size_t found;
    while ((found = line.find(",", i)) != std::string::npos) {
        element.push_back(line.substr(i, found - i));
        cout << element.at(element.size() - 1) << " ";
        i = found + 1;
    }
    element.push_back(line.substr(i));
    cout << element.at(element.size() - 1);
    cout << endl;

    getline(infile, line); // To bypass the second line

    // read the rest of the file.
    while (getline(infile, line)) {
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        // find } as the finisher for file reading
        if (line.find("}") != string::npos)
            break;
        // fetch set and relation in the line
        cout << "Extracting the relation per line: \n";
        if (!getFromLine(ss, sr, line))
            return false;
        cout << endl;
    }
    infile.close();
    sr->setInput(ss);

    return true;
}

bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line) {
    vector<string> element;
    int i = 0;
    size_t found;
    while ((found = line.find("->", i)) != std::string::npos) {
        element.push_back(line.substr(i, found - i));
        i = found + 2;
    }
    element.push_back(line.substr(i, line.find("[", i) - i));

    for (int j = 0; j < (int)element.size() - 1; j++) {
        cout << element.at(j) << ", ";
    }
    cout << element.at(element.size() - 1) << endl;

    string temp = line.substr(i, line.find(";", i) - i);
    cout << "weight info: " << temp;

    /*Todo:
     *	Add relation to *sr if and only if
     *  thie relation is a valid relation.
     *  Otherwise, return false.
     *  Also, extract the weight information from the string [label="x"]
     *  The weight number is found in between the quotation mark " "
     */

    return true;
}

void SetUI::printError(string reason) {
    // error message if the command cannot be understood
    if (reason.compare("command") == 0) {
        cout << "Command cannot be understood. Please enter help to see the "
                "available commands\n";
    }
    // error message if the command argument is incorrect
    else if (reason.compare("argument") == 0) {
        cout << "Incorrect command arguments!\n";
        cout << "Please type help to know about the command arguments\n";
    }

    /* Todo:
     * You must think about different error scenarios.
     * Prepare error messages.
     * Some examples are given below:
            1. emit an error message if the input file does not exist or
     contains wrong data.
            2. emit an error message if the user trying to find the equivalence
     class for a string that does not have equivalence relation
    */
}

string SetUI::GetCommand() {
    string commandInput;
    cout << ">> ";

    getline(cin, commandInput);
    return commandInput;
}

// clang-format off
// prints the help message (Completed)
void SetUI::Help() {
    cout << "Currently available commands:\n";
    cout << "Anything inside <> bracket is an optional argument, while [] "
            "bracket contains a must argument.\n\n";
    cout << left << setw(45) << ColorText("	help", RED) << left << setw(50)
         << "Show help." << endl
         << endl;
    cout << left << setw(45) << ColorText("	ls <path> ", RED) << left
         << setw(50)
         << "Identical to the ls shell command. If a path is given, then"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "the program returns all the files in that path." << endl
         << endl;
    cout << left << setw(45) << ColorText("	clear ", RED) << left
         << setw(50)
         << "Identical to the clear shell command. Clear the screen." << endl
         << endl;
    cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED)
         << left << setw(50)
         << "Open a file. If the file does not exist, then program returns"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "an error message. If -v (verbose) option is enabled (e.g., open "
            "a.txt -v),"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "then each line in the file is printed on console while reading."
         << endl
         << endl;
    cout << left << setw(45) << ColorText("	list", RED) << left << setw(50)
         << "List all the members of set and relation." << endl
         << endl;
    cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left
         << setw(50)
         << "Check the relation. The option has to be provided. Options are:"
         << endl;
    cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)"
         << endl;
    cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)"
         << endl;
    cout << left << setw(41) << "" << left << setw(50) << "-t (transtivie)"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "-e (equivalence relation)" << endl
         << endl;
    cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left
         << setw(50)
         << "Show equivalence class of the given [VALUE = Set member]." << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "If VALUE is not a member of set, then the program returns" << endl;
    cout << left << setw(41) << "" << left << setw(50) << "an error message."
         << endl
         << endl;
    cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED)
         << left << setw(50)
         << "This command checks if two given members are connected to each "
            "other"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "If any of VALUE1 and VALUE2 is not a member of the set, then it"
         << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "returns an error message." << endl
         << endl;
    cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED)
         << left << setw(50)
         << "Apply Dijkstra algorithm to find the shortest path." << endl;
    cout << left << setw(41) << "" << left << setw(50)
         << "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting "
            "node, and VALUE2 is the destination."
         << endl
         << endl;
    cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50)
         << "Terminate the program." << endl;
    cout << "\n\n";
}
// clang-format on

void SetUI::printShortestPath(int distance, string path) {
    cout << "  The shortest path distance: "
         << ColorText(to_string(distance), GREEN) << endl;
    cout << "  The path is: " << ColorText(path, BLUE) << endl;
}

string SetUI::ColorText(string s, COLOR color) {
    string temp;
    switch (color) {
    case RED:
        temp = "\033[1;31m" + s + "\033[0m";
        break;
    case BLUE:
        temp = "\033[1;34m" + s + "\033[0m";
        break;
    case YELLOW:
        temp = "\033[1;33m" + s + "\033[0m";
        break;
    case GREEN:
        temp = "\033[1;32m" + s + "\033[0m";
        break;
    case WHITE:
        temp = "\033[1;37m" + s + "\033[0m";
        break;
    default:
        temp = "\033[0m" + s;
        break;
    }
    return temp;
}
