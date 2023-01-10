#include <iostream>
#include <sstream>
#include <downloader.h>
#include <thread_pool.h>

int main()
{
    size_t numThreads = 2;
    Downloader downloadObj;
    ThreadPool pool(numThreads);
    
    ThreadPool::FunctionType f1;
    f1.func = [&downloadObj](int id) { return downloadObj.downloadTaskA(id); };
    f1.param = 123;
    
    ThreadPool::FunctionType f2;
    f2.func = [&downloadObj](int id) { return downloadObj.downloadTaskB(id); };
    f2.param = 124;
    
    pool.AddFunction(f1);
    pool.AddFunction(f2);
   
    while(!pool.IsLast())
    {
        // wait for tasks completion
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
    
    



        

    



        
