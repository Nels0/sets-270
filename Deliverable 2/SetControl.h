#ifndef _SetControl_h
#define _SetControl_h

#include "SetOfStrings.h"
#include "SetUI.h"
#include "StringRelation.h"
#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class SetControl {
  private:
    // members variables
    SetUI *setUI;
    SetOfStrings *setModel;
    StringRelation *relationModel;

    int isReachable(string src,
                    string dst); // this supposed to be in the model... But I
                                 // programmed here for assignment separation

  public:
    // constructor/destructor
    SetControl();
    ~SetControl();

    // members functions
    bool Run();
};
#endif
