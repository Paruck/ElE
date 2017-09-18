#pragma once
#include "ElEDefines.h"

#ifdef RASPBERRY_COMPILE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <regex.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#endif // RASPBERRY_COMPILE

class ElEInput{
public:
    static ElEInput* ElEcall getInstance() { return instance == nullptr ? instance = new ElEInput() : instance; }
    ElEbool ElEcall keyPressed(const ElEKey& key);
    ElEPosHelper ElEcall mousePosition();
private:
    ElEInput() {}
    static ElEInput* instance;
#ifdef RASPBERRY_COMPILE
    ElEint  kbfd = -1,
            mfd = -1;
#else

#endif
};
