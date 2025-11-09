#include <iostream>
#include <string>
#include <csignal>
#include <cerrno>
#include <cstring>
#include <unistd.h>

bool killProcessByPid(pid_t pid) {
    if (pid <= 0) return false;

    if (pid == 1) {
        std::cerr << "Refusing to kill PID 1 (system process).\n";
        return false;
    }

    if (kill(pid, SIGTERM) == 0) {
        return true;
    }

    if (errno == EPERM) {
        std::cerr << "Permission denied (need root) to kill PID " << pid << ".\n";
        return false;
    }

    if (kill(pid, SIGKILL) == 0) {
        return true;
    }

    std::cerr << "Failed to kill PID " << pid << ": " << std::strerror(errno) << "\n";
    return false;
}


int promptAndKill() {
    std::string line;
    std::cout << "Enter PID to kill (or 0 to skip): ";
    if (!std::getline(std::cin, line)) return -1; // EOF

    if (line.empty()) return 0;

    int pid = 0;
    try {
        pid = std::stoi(line);
    } catch (...) {
        std::cout << "Invalid input. Please enter a numeric PID.\n";
        return 0;
    }

    if (pid == 0) {
        std::cout << "Skipping kill.\n";
        return 0;
    }


    std::cout << "Are you sure you want to kill PID " << pid << "? (y/N): ";
    if (!std::getline(std::cin, line)) return -1;
    if (line.size() == 0 || (line[0] != 'y' && line[0] != 'Y')) {
        std::cout << "Cancelled.\n";
        return 0;
    }

    // Attempt to kill
    bool ok = killProcessByPid(static_cast<pid_t>(pid));
    if (ok) std::cout << "Signal sent to PID " << pid << ".\n";
    return pid;
}

