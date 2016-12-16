#pragma once

#include <3ds.h>

#include <functional>
#include <list>

namespace starlight {
    namespace util {
        class WorkerThread {
        private:
            Thread thread;
            Handle sync;
            volatile bool lock = false;
            volatile bool kill = false;
            volatile bool running = false;
            std::list<std::function<void()>*> queue;
        public:
            
            WorkerThread();
            ~WorkerThread();
            
            void ThreadMain();
            
            void Push(std::function<void()>* func);
        };
    }
}

