#pragma once
#include <iostream>

class Downloader
{
public:
    int downloadTaskA(int id)
    {
        std::stringstream ss;
        ss << "downloadTaskA " << id;
        printMsg(ss.str());
    }

    int downloadTaskB(int id)
    {
        std::stringstream ss;
        ss << "downloadTaskB " << id;
        printMsg(ss.str());
    }
private:
    std::mutex mutexPrint;
    void printMsg(const std::string& msg)
    {
        std::lock_guard<std::mutex> lk(mutexPrint);
        std::cout << msg << std::endl;
    }
};

