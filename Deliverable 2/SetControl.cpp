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

bool SetControl::Run() {
    string command;

    /* Todo:
     * 	  Implement control logics for handling user commands.
     *	  Some commands are already programmed for you.
     *	  Your final code should have no 'cout' in this file.
     * 	  Also, your "Model" should never print anything to console.
     * 	  Printing is done only using "View".
     */

    // invoke the main user interaction
    while (true) {

        // show the menu and get user command
        command = setUI->GetCommand();

        int argc = 0;

        // string tokenizer to split string by using " " as the separator.
        // stores the values in argv array while the number of argument is argc.
        vector<string> argv;
        int i = 0;
        size_t found;
        while ((found = command.find(" ", i)) != std::string::npos) {
            argv.push_back(command.substr(i, found - i));
            i = found + 1;
        }
        argv.push_back(command.substr(i));

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
            if (!(argc == 1 || argc == 2)) {
                setUI->printError("argument");
                continue;
            }
            if (argc == 2) {
                string cmd(argv[1]);
                cmd = "ls " + cmd;
                system(cmd.c_str());
            } else
                system("ls");
        }
        // open command execution (Incompleted)
        //**complete this function first.
        else if (argv.at(0).compare("open") == 0) {
            if (!(argc == 2 || argc == 3)) {
                setUI->printError("argument");
                continue;
            }
            SetOfStrings *temps   = new SetOfStrings();
            StringRelation *tempr = new StringRelation();
            if (argc == 2) {
                setUI->ReadFromFile(argv.at(1), temps, tempr, false);
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

        else if (argv.at(0).compare("list") == 0) {
            // cout << "Listing...";
            if (setModel->isEmpty() || relationModel->isEmpty()) {
                setUI->printError("notLoaded");
            } else {
                setUI->ListMembers(setModel);
                setUI->ListMembers(relationModel);
            }
        }

        else if (argv.at(0).compare("check") == 0) {

            if (setModel->isEmpty() || relationModel->isEmpty()) {
                setUI->printError("notLoaded");
                continue;
            } else {
                if (argc == 2) {
                    if (argv.at(1).compare("-r") == 0) {
                        setUI->printProperties("reflexive", relationModel->isReflexive());
                    } else if (argv.at(1).compare("-s") == 0) {
                        setUI->printProperties("symmetrical", relationModel->isSymmetric());
                    } else if (argv.at(1).compare("-t") == 0) {
                        setUI->printProperties("transitive", relationModel->isTransitive());
                    } else if (argv.at(1).compare("-e") == 0) {
                        setUI->printProperties("equivalence", relationModel->isEquivalence());
                    }
                } else {
                    setUI->printError("argument");
                    continue;
                }
            }
        }

        else if (argv.at(0).compare("clear") == 0) {
            if (argc == 1) {
                system("clear");
            } else {
                setUI->printError("argument");
                continue;
            }
        }

        else if (argv.at(0).compare("eqclass") == 0) {
            // cout << "argc = " << argc << endl;
            if (argc != 2) {
                setUI->printError("argument");
                continue;
            } else if (setModel->isEmpty() || relationModel->isEmpty()) {
                setUI->printError("notLoaded");
                continue;
            }

            SetOfStrings *tempEQClass = relationModel->computeEquivalenceClass(argv.at(1));

            if (tempEQClass->isEmpty()) {
                setUI->printError("eqclassfailure");
                continue;
            } else {
                setUI->printEquivalenceClass(argv.at(1), tempEQClass);
            }

        }

        else if (argv.at(0).compare("reachable") == 0) {
            if (argc != 3) { // TODO: Put these into a function called  argCheck(int argc) or something
                setUI->printError("argument");
                continue;
            } else if (setModel->isEmpty() || relationModel->isEmpty()) {
                setUI->printError("notLoaded");
                continue;
            }

            if (!setModel->isMember(argv.at(1)) || !setModel->isMember(argv.at(2))) {
                setUI->printError("nonmember");
            } else if (argv.at(1).compare(argv.at(2)) == 0) {
                setUI->printReachable(true, true);
            } else {
                std::list<string> *visited = new std::list<string>;
                setUI->printReachable(relationModel->isReachable(argv.at(1), argv.at(2), visited), false);
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
