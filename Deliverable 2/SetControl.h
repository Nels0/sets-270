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
    bool argCheck(int argCount, int &argc);
    bool argCheck(int argMin, int argMax, int &argc);
    bool loadedCheck();

  public:
    // constructor/destructor
    SetControl();
    ~SetControl();

    // members functions
    bool Run();
};
#endif
