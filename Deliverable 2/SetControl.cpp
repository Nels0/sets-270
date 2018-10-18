/* This is the controller part for your program.
 * In this file, students are required to complete the "control" logic.
 * The controller accepts keyboard inputs from the user through View, and
 * manipulate data in Model. Then, the result from Model is sent back to user
 * through View. Think about the design before the actual implementation.
 */
#include "SetControl.h"

SetControl::SetControl() {
    cout << "Initializing the calculator, please wait! ... \n" << endl;

    // instansiate all members
    setUI         = new SetUI();
    setModel      = new SetOfStrings();
    relationModel = new StringRelation();
}

SetControl::~SetControl() {
    // dispose all members
    delete setUI;
    delete setModel;
    delete relationModel;
}

bool SetControl::argCheck(int argMin, int argMax, int &argc) {
    if (argc > argMax || argc < argMin) {
        setUI->printError("argument");
        return false;
    }
    return true;
}

bool SetControl::argCheck(int argCount, int &argc) {
    if (argc != argCount) {
        setUI->printError("argument");
        return false;
    }
    return true;
}

bool SetControl::loadedCheck() {
    if (setModel->isEmpty() || relationModel->isEmpty()) {
        setUI->printError("notLoaded");
        return false;
    }
    return true;
}

bool SetControl::Run() {
    string command;

    // invoke the main user interaction
    while (true) {

        // show the menu and get user command
        command  = setUI->GetCommand();
        int argc = 0;

        // string tokenizer to split string by using " " as the separator.
        // stores the values in argv array while the number of argument is argc.
        vector<string> argv;
        int i = 0;
        size_t found;
        while ((found = command.find(" ", i)) != std::string::npos) {
            string t_command = command.substr(i, found - i);
            if (t_command.compare("") != 0) {
                argv.push_back(t_command);
            }
            i = found + 1;
        }
        if (command.substr(i, found - i).compare("") != 0) {
            argv.push_back(command.substr(i));
        }

        argc = argv.size();
        // if enter is pressed
        if (argc == 0)
            continue;

        // help command execution (Completed)
        if (argv.at(0).compare("help") == 0) {
            setUI->Help();
        }
        // ls command execution (Completed)
        else if (argv.at(0).compare("ls") == 0) {

            if (argCheck(1, 2, argc)) {
                if (argc == 2) {
                    string cmd(argv[1]);
                    cmd = "ls " + cmd;
                    system(cmd.c_str());
                } else {
                    system("ls");
                }
            }
        }
        // open command execution (Incompleted)
        //**complete this function first.
        else if (argv.at(0).compare("open") == 0) {
            if (argCheck(2, 3, argc)) {
                SetOfStrings *temps   = new SetOfStrings();
                StringRelation *tempr = new StringRelation();
                if (argc == 2) {
                    setUI->ReadFromFile(argv.at(1), temps, tempr, false);

                    // Delete old relation to prevent memory leak
                    delete setModel;
                    delete relationModel;
                    // reassign pointers
                    setModel      = temps;
                    relationModel = tempr;
                } else {
                    // if the file cannot be read
                    if (!setUI->ReadFromFile(argv.at(1), temps, tempr, (argv.at(2).compare("-v") == 0) ? true : false)) {
                        setUI->printError("file"); // print an error message
                        continue;
                    } else {
                        // Delete old relation to prevent memory leak
                        delete setModel;
                        delete relationModel;
                        // reassign pointers
                        setModel      = temps;
                        relationModel = tempr;
                    }
                }
            }

        }

        else if (argv.at(0).compare("list") == 0) {

            // cout << "Listing...";
            if (loadedCheck() && argCheck(1, argc)) {
                setUI->ListMembers(setModel);
                setUI->ListMembers(relationModel);
            }
        }

        else if (argv.at(0).compare("check") == 0) {
            if (loadedCheck() && argCheck(2, argc)) {
                if (argv.at(1).compare("-r") == 0) {
                    setUI->printProperties("reflexive", relationModel->isReflexive());
                } else if (argv.at(1).compare("-s") == 0) {
                    setUI->printProperties("symmetric", relationModel->isSymmetric());
                } else if (argv.at(1).compare("-t") == 0) {
                    setUI->printProperties("transitive", relationModel->isTransitive());
                } else if (argv.at(1).compare("-e") == 0) {
                    setUI->printProperties("equivalence", relationModel->isEquivalence());
                }
            }
        }

        else if (argv.at(0).compare("clear") == 0) {
            if (argCheck(1, argc)) {
                system("clear");
                setUI->TopicScreen();
            }
        }

        else if (argv.at(0).compare("eqclass") == 0) {

            if (argCheck(2, argc) && loadedCheck()) {
                SetOfStrings *tempEQClass = relationModel->computeEquivalenceClass(argv.at(1));

                if (tempEQClass->isEmpty()) {
                    setUI->printError("eqclassfailure");
                    continue;
                } else {
                    setUI->printEquivalenceClass(argv.at(1), tempEQClass);
                }
            }
        }

        else if (argv.at(0).compare("reachable") == 0) {

            if (argCheck(3, argc) && loadedCheck()) {
                if (!setModel->isMember(argv.at(1)) || !setModel->isMember(argv.at(2))) {
                    setUI->printError("nonmember");
                } else if (argv.at(1).compare(argv.at(2)) == 0) {
                    setUI->printReachable(true, true);
                } else {
                    std::list<string> *visited = new std::list<string>;
                    setUI->printReachable(relationModel->isReachable(argv.at(1), argv.at(2), visited), false);
                }
            }

        }

        else if (argv.at(0).compare("path") == 0) {
            if (argCheck(3, argc) && loadedCheck()) {
                if (!setModel->isMember(argv.at(1)) || !setModel->isMember(argv.at(2))) {
                    setUI->printError("nonmember");
                } else {
                    int distance = relationModel->computeShortest(argv.at(1), argv.at(2));
                    string path  = relationModel->getPath();
                    if (distance != -1) {
                        setUI->printShortestPath(distance, path);
                    } else {
                        setUI->printError("unreachable");
                    }
                }
            }
        }

        // exit command execution (Completed)
        else if (argv.at(0).find("exit") != string::npos) {
            exit(0);
        }
        // Command is invalid
        else {
            setUI->printError("command");
        }
    }

    return true;
}
