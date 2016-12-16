#include "WorkerThread.h"

using starlight::util::WorkerThread;

namespace { // helpers
    void EnterNew(void* arg) {
        static_cast<WorkerThread*>(arg)->ThreadMain();
    }
}

WorkerThread::WorkerThread() {
    svcCreateEvent(&sync, RESET_ONESHOT);
    s32 priority = 0;
    svcGetThreadPriority(&priority, CUR_THREAD_HANDLE);
    thread = threadCreate(EnterNew, static_cast<void*>(this), 4*1024, priority-1, -2, false);
}

WorkerThread::~WorkerThread() {
    kill = true;
    threadJoin(thread, U64_MAX);
    threadFree(thread);
}

void WorkerThread::ThreadMain() {
    if (running) return; // wait, how did you get here twice?
    running = true;
    while (!kill) {
        svcWaitSynchronization(sync, U64_MAX);
        while (lock) { }
        lock = true;
        while (!queue.empty()) {
            auto func = queue.front();
            queue.pop_front();
            lock = false;
            
            (*func)();
            delete func;
            
            while (lock) { }
            lock = true;
        }
        lock = false;
    }
    running = false;
}

void WorkerThread::Push(std::function<void()>* func) {
    while (lock) { }
    lock = true;
    queue.push_back(func);
    lock = false;
    svcSignalEvent(sync);
}
