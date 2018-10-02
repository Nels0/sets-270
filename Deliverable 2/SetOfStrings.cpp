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

void SetOfStrings::removeElement(string s)
{
	//You have implemented this in the lab

}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
	//You have implemented this in the lab

	SetOfStrings *out = new SetOfStrings();
	return out;
}

bool SetOfStrings::isEqual(SetOfStrings *s)
{
	//You have implemented this in the lab
	return true;
}

string SetOfStrings::returnElement(int index)
{
	if (index < (int)setv.size() && index >= 0)
		return setv.at(index);
	else
		return "\n";
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
	//You are required to implement this as this
	SetOfStrings *out = new SetOfStrings();
	return out;
}

bool SetOfStrings::subset(SetOfStrings *s)
{
	//You are required to implement this as this
	return true;
}
