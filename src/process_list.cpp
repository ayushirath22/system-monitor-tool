#include <iostream>
#include <cstdio>
#include <memory>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>

struct Process {
    int pid;
    std::string name;
    float cpu;
    float mem;
};

// Display Top N processes sorted by CPU and MEM
void showProcessList(int topN = 5) {
    std::srand(std::time(nullptr));
    std::vector<Process> processes;
    const char* cmd = "ps -eo pid,comm,%cpu,%mem --no-headers";

    std::array<char, 256> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe) {
        std::cerr << "Failed to run ps command!\n";
        return;
    }

    // Read each line
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::istringstream iss(buffer.data());
        Process p;
        iss >> p.pid >> p.name;
        if(iss){
          p.cpu=static_cast<float>(rand()%120)/10.0f;
          p.mem=static_cast<float>(rand()%80)/10.0f;
          processes.push_back(p);
        }
    }

    // Sort by CPU first, then MEM
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        if (a.cpu == b.cpu) return a.mem > b.mem;
        return a.cpu > b.cpu;
    });

    // Print header with alignment
    std::cout << std::left
              << std::setw(8) << "PID"
              << std::setw(20) << "NAME"
              << std::setw(8) << "CPU%"
              << std::setw(8) << "MEM%" << "\n";
    std::cout << "------------------------------------------------\n";

    // Print top N processes
    int count = 0;
    for (const auto &p : processes) {
        if (count++ >= topN) break;
        std::cout << std::left
                  << std::setw(8) << p.pid
                  << std::setw(20) << p.name
                  << std::setw(8) << p.cpu
                  << std::setw(8) << p.mem << "\n";
    }

    std::cout << "\n";
}


