#include "../inc/Utility.h"
#include <fstream>
#include <random>
#include <set>
#include <list>

bool contains(const std::set<int>& genNum, const int &num)
{
    if(genNum.find(num) != genNum.end())
        return true;
    return false;
}

// bool outData(const std::vector<std::string>& data , const int &size)
// {
//     if (size == 0)
//         return false;
//     std::ofstream ostrm("../txt/out.txt", std::ios::app);
//     std::vector<int> genNum;
//     srand((unsigned)time(NULL));
//     int i = rand() % size;
//     while (genNum.size() != size)
//     {
//         try
//         {
//             ostrm << data[i] << " ";
//             genNum.push_back(i);
//             while (contains(genNum, i) && genNum.size() != size)
//             {
//                 i = rand() % size;
//             }
//         }
//         catch (const std::exception &errWrite)
//         {
//             std::cerr << errWrite.what() << '\n';
//             ostrm.close();
//             return false;
//         }
//     }
//     ostrm.close();
//     return true;
// }

// bool inData(std::vector<std::string>& out)
// {   
//     std::string tmp = "";
//     std::ifstream istrm("../txt/in.txt", std::ios::in);
//     while(!istrm.eof()){
//         try
//         {  
//            istrm >> tmp;
//            out.push_back(tmp);
//         }
//         catch(const std::exception& errRead)
//         {
//             std::cerr << errRead.what() << '\n';
//             istrm.close();
//             return false;
//         }
//     }
//     return true;
// }
