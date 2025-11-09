#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

void displayCPUInfo();
void displayMemoryInfo();
void showProcessList(int topN);
int promptAndKill();

//real-time system monitor
void startMonitor() {
    while (true) {
        system("clear");   // Clear terminal screen

        // Show system information
        displayCPUInfo();
        displayMemoryInfo();
        showProcessList(5);

        std::cout << "\nPress Ctrl + C to exit.\n";

        // Wait 2 seconds before refresh
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

