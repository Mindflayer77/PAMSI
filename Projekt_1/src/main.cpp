#include "../inc/SLPQueue.h"
#include "../inc/Utility.h"

int main()
{
    time_t start, end;
    SLPQueue<int> queue;
    //std::cout << queue.isEmpty() << std::endl;
    std::string test[] = {"Siema", "co", "tam", "u", "was?"};
    std::string *testRead;
    std::vector<std::string> data;

    time(&start);
    inData(data);
    int size = data.size();
    outData(data, size);
    time(&end);
    std::cout << "Number of packets: " << size << std::endl;
    std::cout << "Execution time: " << double(end-start) << "seconds" << std::endl;

    // std::cout << queue.getBack() <<std::endl;
}