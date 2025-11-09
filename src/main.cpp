#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void startMonitor();
void showProcessList(int topN);
int promptAndKill();

void displayMemoryInfo(){
     ifstream memFile("/proc/meminfo");
     string line;
     cout << "Memory Info:\n";
     while (getline(memFile, line)){
         cout << line << endl;
     }
     memFile.close();
}

void displayCPUInfo(){
     ifstream cpuFile("/proc/stat");
     string line;
     getline(cpuFile, line);
     cout << "CPU Info:\n" << line << endl;
     cpuFile.close();
}

int main(){
    cout << "CPU Info and Memory Info...\n";
    displayCPUInfo();
    cout << endl;
    displayMemoryInfo();
    cout << endl;
    showProcessList(5);
    int res = promptAndKill();
    if(res>0){
       cout << "\nRefreshing process list...\n";
    }
   startMonitor();
   return 0;

}

