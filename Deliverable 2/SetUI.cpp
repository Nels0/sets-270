#include "SetUI.h"

/* Function Header Template:
 * Description
 *
 * Arguments:   A:         String
 *              B:         SetOfStrings
 *              C:         StringRelation
 *              D:         Bool
 *
 * Returns:     E:         Bool
 */

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

bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose) {
    /* ReadFromFile:
     * Reads a set, and binary relations with weights.
     *
     * Arguments:   Filename:   String
     *              ss:         SetOfStrings to write to
     *              sr:         StringRelation to write to
     *              verbose:    Bool
     *
     * Returns:     Success:    Bool
     */

    string line;
    ifstream infile(filename.c_str());

    // return false if the file does not exist
    if (!infile.good()) {
        return false;
    }

    getline(infile, line); // Get the first line to extract set members

    if (verbose) {
        cout << ColorText(line, WHITE) << endl;
    }

    line.erase(0, 2); // Remove '//' in the line

    int i = 0;
    size_t found;
    // Remove all the spaces, and resize string
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    while ((found = line.find(",", i)) != std::string::npos) { // Find comma
        // Add from i to just before comma
        ss->insertElement(line.substr(i, found - i));

        i = found + 1; // Move i to after comma
    }
    // Add from after last comma to end of line
    ss->insertElement(line.substr(i));

    getline(infile, line); // To bypass the second line

    // read the rest of the file.
    while (getline(infile, line)) {
        if (verbose) {
            cout << ColorText(line, WHITE) << endl;
        }
        // Remove all the spaces, and erase() does nothing
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (line.compare("") != 0) {
            // find } as the finisher for file reading
            if (line.find("}") != string::npos)
                break;
            // fetch set and relation in the line
            if (!getFromLine(ss, sr, line))
                return false;
        }
    }
    infile.close();
    sr->setInput(ss);
    cout << ColorText("  File reading was successful\n  Please type 'list' to view "
                      "the members and relations defined in the graph",
                      GREEN)
         << "\n"
         << ColorText("  If a directory is opened instead of a file, program "
                      "will generate incorrect outputs",
                      BLUE)
         << endl;

    return true;
}

bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line) {
    /* GetFromLine:
     * Gets a binary relation from an opened file
     *
     * Arguments:   ss:         SetOfStrings to write to
     *              sr:         StringRelation to write to
     *              line:       String to read from
     *
     * Returns:     Sucess:     Bool
     */

    vector<string> element;
    int i = 0;
    size_t found;
    while ((found = line.find("->", i)) != std::string::npos) {
        element.push_back(line.substr(i, found - i));
        i = found + 2;
    }
    element.push_back(line.substr(i, line.find("[", i) - i));

    string temp = line.substr(line.find("\"") + 1, std::string::npos);

    int tempWeight = stoi(temp, nullptr);

    string relation;
    std::vector<string>::iterator p;

    for (p = element.begin(); p != element.end(); p++) {
        if (!ss->isMember(*p)) {
            printError("invalidRelation");
            return false;
        } else {
            relation.append(*p);
            relation.append(",");
        }
    }

    // Remove trailing "," and add relation from this line
    relation.erase(relation.end() - 1);
    sr->insertElement(relation);
    sr->appendWeight(tempWeight);

    return true;
}

int SetUI::ListMembers(SetOfStrings *model) {

    int i = 0;
    cout << "  The members of the " << ColorText("sets", BLUE) << " are:\n  => {";
    for (i = 0; i != model->size() - 1; i++) {
        cout << ColorText(model->returnElement(i), BLUE) << ", ";
    }
    cout << ColorText(model->returnElement(i), BLUE) << "}" << endl;
    return 0;
}

int SetUI::ListMembers(StringRelation *model) {

    int i = 0;

    cout << "  The members of the " << ColorText("relations", YELLOW) << " are:\n  => {";
    for (i = 0; i != model->size() - 1; i++) {
        cout << "(" << ColorText(model->returnElement(i), YELLOW) << "), ";
    }
    cout << "(" << ColorText(model->returnElement(i), YELLOW) << ")}" << endl;

    cout << "  The associated " << ColorText("weights", BLUE) << " are:\n  => {";
    for (i = 0; i != model->size() - 1; i++) {
        cout << ColorText(to_string(model->getWeight(i)), BLUE) << ", ";
    }
    cout << ColorText(to_string(model->getWeight(i)), BLUE) << "}" << endl;

    return 0;
}

void SetUI::printProperties(string property, bool isProperty) {

    string printString;

    if (property.compare("equivalence") == 0) {
        printString = "  => This is ";
        if (!isProperty) {
            printString.append("not ");
        }
        printString.append("an equivalence relation");
    } else {
        printString = "  => It is ";

        if (!isProperty) {
            printString.append("not ");
        }
        printString.append(property);
    }

    if (isProperty) {
        cout << ColorText(printString, GREEN) << endl;
    } else {
        cout << ColorText(printString, RED) << endl;
        ;
    }
    return;
}

void SetUI::printEquivalenceClass(string member, SetOfStrings *ss) {

    int i = 0;
    cout << "  => [" << ColorText(member, BLUE) << "] = {";
    for (i = 0; i < ss->size() - 1; ++i) {
        if (ss->returnElement(i).compare("\n") == 0) {
            printError("command");
            continue;
        } else {
            cout << ColorText(ss->returnElement(i), YELLOW) << ", ";
        }
    }
    cout << ColorText(ss->returnElement(i), YELLOW) << "}" << endl;
}

void SetUI::printReachable(bool reachable, bool self) {
    cout << left << setw(2) << " ";
    if (reachable) {
        cout << ColorText("Reachable", GREEN) << endl;
        if (self) {
            cout << ColorText("(Source == Destination)", BLUE) << endl;
        }
    } else {
        printError("unreachable");
    }
}

void SetUI::printError(string reason) {

    // error message if the command cannot be understood
    if (reason.compare("command") == 0) {
        cout << ColorText(" Command cannot be understood. Please enter help to see the available commands\n", RED);
    }
    // error message if the command argument is incorrect
    else if (reason.compare("argument") == 0) {
        cout << ColorText("  Incorrect command arguments!\n", RED);
        cout << ColorText("  Type help to know about the command arguments\n", RED);
    }

    else if (reason.compare("invalidRelation") == 0) {
        cout << ColorText("  Invalid relation in file (Relation refers to non-existent element)\n", RED);
    }

    else if (reason.compare("notLoaded") == 0) {
        cout << ColorText("  Operation could be initialized because there is no graph to compute\n  Please load a "
                          "graph first by using 'open' "
                          "command which will read a file\n",
                          RED);
    }

    else if (reason.compare("eqclassfailure") == 0) {
        cout << ColorText("  Equivalence class request could not be executed\n  Possibly the string does", RED)
             << ColorText(" not exist in the set or there is no equivalence relation\n", RED);
    }

    else if (reason.compare("file") == 0) {
        cout << ColorText("  Error occured while reading the input file. Possible reasons:\n  1. File does not exist\n "
                          " 2. Contains a invalid "
                          "graph\n  3. Unreadable "
                          "data\n  Graph could not be loaded successfully\n",
                          RED);
    }

    else if (reason.compare("nonmember") == 0) {
        cout << ColorText(
            "  The requested member does not exist in the set\n  Please type 'list' to know about existing strings\n",
            RED);
    }

    else if (reason.compare("unreachable") == 0) {
        cout << ColorText("  Unreachable!\n", RED);
    }
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
    cout << "  The shortest path distance: " << ColorText(to_string(distance), GREEN) << endl;
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
