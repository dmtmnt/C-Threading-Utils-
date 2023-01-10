#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

class ThreadPool
{
public:

    struct FunctionType
    {
        std::function<int(int)> func;
        int param;
    };
    
    ThreadPool(size_t numThreads) : m_threadCount(numThreads)
    {
        m_isAlive.store(true);
        m_isLast.store(false);
        for(size_t i = 0; i < m_threadCount; ++i)
        {
            m_threadVec.push_back(std::thread(std::bind(&::ThreadPool::Run, this)));
        }
    }
    
    ~ThreadPool()
    {
        m_isAlive.store(false);
        for(size_t i = 0; i < m_threadCount; ++i)
        {
            m_threadVec[i].join();
        }
    }
    
    bool SetIsAlive(bool val)
    {
        m_isAlive.store(val);
    }
    
    void AddFunction(FunctionType func)
    {
        std::lock_guard<std::mutex> lk(m_functionsMutex);
        m_functions.push(std::move(func));
        m_notifier.notify_one();
    }
    
    bool IsLast() const
    {
        return m_isLast;
    }
        
    void Run()
    {
        while(m_isAlive)
        {
            std::unique_lock<std::mutex> lk(m_functionsMutex);
            if (!m_functions.empty())
            {
                auto funcStruct = std::move(m_functions.front());
                m_functions.pop();
                lk.unlock();
                
                auto func = funcStruct.func;
                auto param = funcStruct.param;
               
                func(param);
                
                m_isLast.store(m_functions.empty());
                
            }
            else
            {
                m_notifier.wait(lk, [&] { return m_functions.empty(); } );
                continue;
            }
        }
    }
    
private:
    std::mutex m_functionsMutex;
    std::condition_variable m_notifier;
    std::queue<FunctionType> m_functions;
    std::atomic<bool> m_isLast;
    
    std::atomic<bool> m_isAlive;
    size_t m_threadCount;
    std::vector<std::thread> m_threadVec;
};
