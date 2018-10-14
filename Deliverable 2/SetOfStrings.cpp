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
    p = setv.begin();
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

void SetOfStrings::removeElement(string s) {
    vector<string>::iterator p = setv.begin();
    while (p != setv.end()) {
        if (*p == s) {
            setv.erase(p);
            return;
        }
        p++;
    }
}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s) {
    SetOfStrings *s1 = new SetOfStrings();
    vector<string>::iterator p;

    for (p = setv.begin(); p != setv.end(); p++) {
        s1->insertElement(*p);
    }
    for (p = s->setv.begin(); p != s->setv.end(); p++) {
        s1->insertElement(*p); // Duplicate elements handled
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
    if (index < (int)setv.size() && index >= 0)
        return setv.at(index);
    else
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

    return out;
}

bool SetOfStrings::subset(SetOfStrings *s) {
    for (p = s->setv.begin(); p != s->setv.end(); p++) {
        if (!isMember(*p)) {
            return false;
        }
    }
    return true;
}
