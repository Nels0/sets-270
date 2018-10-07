#ifdef _DEBUG
#define DEBUG true
#else
#define DEBUG false
#endif

#include "SetOfStrings.h"

using namespace std;

bool SetOfStrings::isEmpty()
{
    if(setv.empty()) return true;
    else return false;
}

int SetOfStrings::size(){
    return (int) setv.size();
}

bool SetOfStrings::isMember(string s)
{
    p=setv.begin();
    while(p!=setv.end()){
        if(*p==s)return true;
        ++p;
    }
    return false;
}

void SetOfStrings::insertElement(string s)
{
    if(!isMember(s)){
        setv.push_back(s);
    }
}

string SetOfStrings::ColourText(string s, COLOUR c)
{
	string temp;
	switch (c) {
		case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
		case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
		case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
		case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
		case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
		default: temp = "\033[0m" + s; break;
	}
	return temp;
}
void SetOfStrings::print()
{
   p=setv.begin();
   while(p!=setv.end()){
        cout << *p << endl;
        ++p;
   }
}

void SetOfStrings::removeElement(string s)
{
    p=setv.begin();
    while(p!=setv.end()){
        if(*p == s){
            setv.erase(p);
            if(DEBUG){cout<< "Element \"" <<s<< "\" removed" <<endl;}
            return;
        }
    }
    if(DEBUG){cout<<"Element not removed/found"<<endl;}

}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
    SetOfStrings *s1 = new SetOfStrings();

    for(p=setv.begin(); p!=setv.end(); p++){
        s1->insertElement(*p);
    }
    for(p=s->setv.begin(); p!= s->setv.end(); p++){
        s1->insertElement(*p);
    }

    return s1;
}

bool SetOfStrings::isEqual(SetOfStrings *s)
{
    for(p=setv.begin(); p!=setv.end(); p++){
        if(!s->isMember(*p)){
            return false;
        }
    }

    return true;
}

string SetOfStrings::returnElement(int index)
{
	int i=0;
	if(index > size()) return "\n";
    p=setv.begin();
    while(p!=setv.end()){
       if(i==index)
    	   return  *p;
       else
       	   {
    	   	   ++i;
    	   	   ++p;
       	   }
    }
    return "\n";
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
	//You are required to implement this
    SetOfStrings *out = new SetOfStrings();
    return out;
}

bool SetOfStrings::subset(SetOfStrings *s)
{
    //You are required to implement this
    return true;
}
