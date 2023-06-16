#pragma once
#include "Game.h"

enum Error{
    NONE,
    READ,
    WRITE,
    FILE_NOT_OPENED
};

Error performanceTest();