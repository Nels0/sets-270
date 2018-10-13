#ifdef _DEBUG
#define DEBUG true
#else
#define DEBUG false
#endif

#include "SetOfStrings.h"

using namespace std;

bool SetOfStrings::isEmpty() {
    if (setv.empty())
        return true;
    else
        return false;
}

int SetOfStrings::size() { return (int)setv.size(); }

bool SetOfStrings::isMember(string s) {
    vector<string>::iterator p = setv.begin();
    while (p != setv.end()) {
        if (*p == s)
            return true;
        ++p;
    }
    return false;
}

void SetOfStrings::insertElement(string s) {
    if (!isMember(s)) {
        setv.push_back(s);
    }
}

string SetOfStrings::ColourText(string s, COLOUR c) {
    string temp;
    switch (c) {
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
void SetOfStrings::print() {
    vector<string>::iterator p = setv.begin();
    while (p != setv.end()) {
        cout << *p << endl;
        ++p;
    }
}

void SetOfStrings::removeElement(string s) {
    vector<string>::iterator p = setv.begin();
    while (p != setv.end()) {
        if (*p == s) {
            setv.erase(p);
            // if(DEBUG){cout<< "Element \"" <<s<< "\" removed" <<endl;}
            return;
        }
        p++;
    }
    // if(DEBUG){cout<<"Element not removed/found"<<endl;}
}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s) {
    SetOfStrings *s1 = new SetOfStrings();
    vector<string>::iterator p;

    for (p = setv.begin(); p != setv.end(); p++) {
        s1->insertElement(*p);
    }
    for (p = s->setv.begin(); p != s->setv.end(); p++) {
        s1->insertElement(*p);
    }

    return s1;
}

bool SetOfStrings::isEqual(SetOfStrings *s) {
    vector<string>::iterator p;
    for (p = setv.begin(); p != setv.end(); p++) {
        if (!s->isMember(*p)) {
            return false;
        }
    }

    return true;
}

string SetOfStrings::returnElement(int index) {
    int i = 0;
    vector<string>::iterator p;
    if (index > size())
        return "\n";
    p = setv.begin();
    while (p != setv.end()) {
        if (i == index)
            return *p;
        else {
            ++i;
            ++p;
        }
    }
    return "\n";
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s) {

    SetOfStrings *out = new SetOfStrings();

    std::vector<string>::iterator p1;

    vector<string>::iterator p = setv.begin();
    while (p != setv.end()) {

        p1 = s->setv.begin();
        while (p1 != s->setv.end()) {
            out->insertElement("(" + *p + "," + *p1 + ")");

            ++p1;
        }

        ++p;
    }
    // if(DEBUG){out->print();}
    return out;
}

bool SetOfStrings::subset(SetOfStrings *s) {

    // cout << s->size() << size() << endl;
    // if(DEBUG){s->print();print();}

    std::vector<string>::iterator p1;

    for (p1 = s->setv.begin(); p1 != s->setv.end(); p1++) {
        // if(DEBUG){cout << "checking if " << *p1 << " is member." << endl;}
        if (!isMember(*p1)) {
            return false;
        }
    }
    return true;
}
