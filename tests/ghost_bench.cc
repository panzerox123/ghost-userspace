#include <iostream>
#include <memory>
#include "lib/base.h"
#include "lib/ghost.h"
#include <cstdlib>

void TestFunction()
{
    std::cout << "Hello world! Starting a ghost thread\n";
    ghost::GhostThread t(ghost::GhostThread::KernelScheduler::kGhost, []
                         {
        std::cout << "In Ghost\n";
        struct sched_param param = {};
        sched_setscheduler(0, SCHED_OTHER, &param);
        std::system("perf stat -e cs sysbench threads --threads=256 run");
    });
    t.Join();
}

int main()
{
    TestFunction();
}