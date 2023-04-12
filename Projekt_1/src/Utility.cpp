#include "../inc/Utility.h"
#include <set>

bool contains(const std::set<int>& genNum, const int &num)
{
    if(genNum.find(num) != genNum.end())
        return true;
    return false;
}
