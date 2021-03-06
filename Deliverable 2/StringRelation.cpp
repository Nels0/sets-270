#include "StringRelation.h"

// will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

// This helps by assigning the composition member
// s is the pointer to the input set
// and R \subseteq s \times s
void StringRelation::setInput(SetOfStrings *s) { set1 = s; }

// check if the relation provided as input is a
// valid relation i.e., R \subseteq S \times S
// Return true when valid; false otherwise
bool StringRelation::isValid() {
    // Create the product of set1 with itself
    // out= set1 /times set1
    SetOfStrings *out = new SetOfStrings();
    out               = set1->product(set1);
    // Overloaded printRelation method used for printing the relation that is
    // equal to the product set
    if (out->subset(this))
        return true;
    else
        return false;
}

void StringRelation::appendWeight(int weightval) { weight.push_back(weightval); }

int StringRelation::getWeight(int idx) { return weight.at(idx); }

int StringRelation::getWeight(string s) {
    std::vector<string>::iterator p;

    for (p = setv.begin(); p != setv.end(); p++) {
        if (*p == s) {
            return weight.at(p - setv.begin());
        }
    }
    return -1;
}

// This is one of the main helper function provided as a
// tokenizer to parse relational elements and separate them into components
// This takes a relation element in the form "a,b" and returns
// a string vector containing "a" and "b"
vector<string> StringRelation::makeTokens(string next) {
    vector<string> out;
    vector<string>::iterator p;
    char *a = new char[next.length() + 1];
    strcpy(a, next.c_str());
    char *token = std::strtok(a, ",");
    int index   = 0;
    while (token != NULL) {
        out.push_back(token);
        token = std::strtok(NULL, ",");
        index++;
    }
    return out;
}

// helper function that returns the string "a,a" when input is "a"
string StringRelation::createReflexiveElement(string s) {
    string next, next1;
    next  = s;
    next1 = next;
    next.append(",");
    next.append(next1);
    return next;
}

// helper function that creates a dual of "a,b" as "b,a"
string StringRelation::computeDual(string s) {

    vector<string> tokens = makeTokens(s);
    vector<string>::iterator p;
    p = tokens.begin();
    string other, other1;
    while (p != tokens.end() - 1) {
        other  = *p;
        other1 = *(p + 1);
        other1.append(",");
        other1.append(other);
        ++p;
    }
    return other1;
}

// return "b" if s is of the form "a,b"
string StringRelation::returnSecondComponent(string s) {
    vector<string> tokens;
    vector<string>::iterator p;
    tokens = makeTokens(s);
    p      = tokens.begin();
    return *(p + 1);
}

// check if s is of the form "a,a" and return true if so
// return false otherwise
bool StringRelation::isReflexiveElement(string s) {

    std::vector<string> elements = makeTokens(s);

    if (elements[0] != elements[1]) {
        return false;
    }

    return true;
}

// check if the relation is reflexive
// if for all s \in set1, (s,s) \in r then reflexive
bool StringRelation::isReflexive() {

    // Iterate over every element of child set
    for (int i = 0; i != set1->size(); i++) {

        // Check if there is a matching reflexive element
        if (!isMember(createReflexiveElement(set1->returnElement(i)))) {
            return false;
        }
    }

    return true;
}

// check if the relation is symmetric
// if for any s1,s2 \in set1, (s1,s2) \in R implies (s2,s1) \in R
bool StringRelation::isSymmetric() {

    std::vector<string>::iterator p;

    for (p = setv.begin(); p != setv.end(); p++) {
        if (!isMember(computeDual(*p))) {
            return false;
        }
    }

    return true;
}

// check if the relation is transitive
// for all x,y,z \in set1, (x -> y AND y -> z) implies x -> z
bool StringRelation::isTransitive() {
    // Assumes only binary relations

    std::vector<string>::iterator p1, p2;
    std::vector<string> rel1, rel2;

    for (p1 = setv.begin(); p1 != setv.end(); p1++) {
        // For every element
        rel1 = makeTokens(*p1);
        for (p2 = setv.begin(); p2 != setv.end(); p2++) {
            // Check if any sequential relations exist
            rel2 = makeTokens(*p2);
            if (rel1.at(1) == rel2.at(0)) { // Check if this is a sequential relation
                if (!isMember(rel1.at(0) + "," + rel2.at(1))) {
                    // Check if transitive element exists
                    // i.e if a,b and b,c exist, check a,c exists
                    return false;
                }
            }
        }
    }

    return true;
}

// return true if the relation is an equivalence relation
// return false otherwise
bool StringRelation::isEquivalence() {

    // In order of complexity so faster operations can be evaluated first
    if (isReflexive() && isSymmetric() && isTransitive()) {
        return true;
    }
    return false;
}

// s1 is of the form "a" while s2 is of the form "p,q"
// if a==p then return true
bool StringRelation::isFirstComponent(string s1, string s2) {
    std::vector<string> s2Tokens = makeTokens(s2);
    if (s1 == s2Tokens[0]) {
        return true;
    }
    return false;
}

// Given a member of set1, this function determine the equivalence class
// for this element s1 i.e. {s| (s,s1) \in R and R is a equivalence relation}
SetOfStrings *StringRelation::computeEquivalenceClass(string element) {

    SetOfStrings *out = new SetOfStrings();

    if (isEquivalence()) {                        // Check relation is an equivalence relation
        for (int i = 0; i != set1->size(); i++) { // foreach in set
            if (isMember(element + "," + set1->returnElement(i))) {
                // Find if the given element is related to element i in set
                out->insertElement(set1->returnElement(i));
                // Append element i to equivalence class
            }
        }
    }

    return out;
}

bool StringRelation::isReachable(string start, string finish, std::list<string> *visited) {

    // A depth-first recursive search for a path between start and finish objects

    bool inList;

    visited->push_back(start);

    if (isMember(start + "," + finish)) { // Check if we can reach the destination node from current node
        return true;
    } else {
        for (int i = 0; i != set1->size(); i++) {        // check every node
            string nextElement = set1->returnElement(i); // The potential next node
            // Search for nextElement in the list
            for (std::list<string>::iterator it = visited->begin(); it != visited->end(); it++) {
                inList = false;
                if (nextElement.compare(*it) == 0) {
                    inList = true;
                }
            }
            if (!inList && isMember(start + "," + nextElement)) {
                // If the next node hasn't been visited
                // and the path between nodes exists
                if (isReachable(nextElement, finish, visited)) {
                    return true;
                } // search from next element to finish
            }
        }
        return false;
    }
}

std::string StringRelation::pathTrace(string source, int endidx, string previous[]) {

    if (previous[endidx].compare(source) == 0) {
        return previous[endidx] + " -> ";

    } else {

        int nextEndidx = -1;
        for (int i = 0; i != set1->size(); i++) { // Find the index of previous[end] is
            if (set1->returnElement(i).compare(previous[endidx]) == 0) {
                nextEndidx = i;
            }
        }
        if (nextEndidx == -1) {
            return "\n";
        }

        return pathTrace(source, nextEndidx, previous) + previous[endidx] + " -> ";
    }
}

// Dijkstra algorithm implementation
// Input: source node, destination node
// Output: path length (integer)
// Note: the generated path is also stored in "path" variable
int StringRelation::computeShortest(string source, string destination) {

    // We'll call this infinity and hope that the weight doesn't overflow
    int MAX_INT = std::numeric_limits<int>::max();

    bool visited[setv.size()]; // Default initialisation is to false;
    int dist[setv.size()];
    std::string previous[setv.size()];

    int destNodeidx = -1;

    // Initialisation of state arrays
    for (int i = 0; i != set1->size(); i++) {
        visited[i] = false; // Just to make sure we don't run into undefined behaviour
        if (set1->returnElement(i) == source) {
            dist[i] = 0; // Distance to source = zero
        } else {
            dist[i] = MAX_INT; // Distance to everywhere else is infinity
        }
        if (set1->returnElement(i) == destination) {
            destNodeidx = i; // Easy tracking of wether algorithm complete
        }
    }
    // Preallocation of variables to save like a nanosecond and prevent scope issues
    int tdist;
    int tnextdist;
    string tmember;
    int selectedObject;
    bool done = false;

    // Dijkstra's actual algorithm
    do {

        tdist          = MAX_INT; // Initialisation for next node search
        selectedObject = MAX_INT;

        for (int i = 0; i != set1->size(); i++) { // Select next unvisited node with lowest distance from origin
            if (!visited[i] && dist[i] < tdist) {
                tdist          = dist[i];
                selectedObject = i;
            }
        }

        if (tdist != MAX_INT && selectedObject != MAX_INT && !visited[destNodeidx]) { // checks if everything has been
                                                                                      // visited or the final node has
                                                                                      // been found thus algorithm done
                                                                                      //
            for (int j = 0; j != set1->size(); j++) {                                 // Search for neighbours
                tmember = set1->returnElement(selectedObject) + "," + set1->returnElement(j); // Create potential edge
                if (isMember(tmember)) {                                                      // If edge exists
                    tnextdist =
                        getWeight(tmember) + dist[selectedObject]; // Get distance to neighbour through current node
                    if (tnextdist < dist[j]) {
                        dist[j]     = tnextdist; // Update distance to neighbour if this route is shorter
                        previous[j] = set1->returnElement(selectedObject); // Update path to node
                    }
                }
            }
            visited[selectedObject] = 1; // Say this one is visited

        } else if (tdist == MAX_INT && selectedObject == MAX_INT && !visited[destNodeidx]) { // Checks if unreachable

            return -1;
        } else {
            done = true;
        }

    } while (!done);

    // Follow path in reverse, recursively
    path = pathTrace(source, destNodeidx, previous) + destination;

    return dist[destNodeidx]; // return distance to destination node
}
