#include <iostream>
#include <memory>
#include "lib/base.h"
#include "lib/ghost.h"
#include <cstdlib>
#include <string>

void TestFunction(std::string cmd = "")
{
    std::cout << "Hello world! Starting a ghost thread\n";
    const char * c_cmd = cmd.c_str();
    ghost::GhostThread t(ghost::GhostThread::KernelScheduler::kCfs, [c_cmd]
                         {
        std::cout << "In Ghost\n";
        struct sched_param param = {};
        sched_setscheduler(0, SCHED_ISO, &param);
        //std::system("sysbench threads --threads=256 run");
        std::system(c_cmd);
    });
    t.Join();
}

int main(int argc, char * argv[])
{
    std::string cmd = "sysbench threads run --threads=";
    cmd += argv[1];
    TestFunction(cmd);
}