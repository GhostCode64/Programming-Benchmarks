#include <iostream>
#include <limits>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>
#include <string>

using namespace std;
//returns the output of a command to a string var
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

//gets the (very) simple OS name
std::string getOsName() {
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}  

//clears the screen based on the OS
void clearScreen() {
    if (getOsName() == "Windows 32-bit" || getOsName() == "Windows 64-bit") {
            system("cls");
        } else {
            system("clear"); 
        }
}

//tells the user that the feature they tried access is not yet implemented
void notYetImplemented(string feature){
    cout << "This feature is not yet implemented. If you see the developer around, tell them you found this message and the feature you tried to access (which was " + feature + ")" << endl;
}

//has the system wait for enter
void pressEnterToContinue() {
    cout << "Press Enter to continue..." << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

//gets the current system specifications (in a system depended method) UNDER CONSTRUCTION 
void showSystemSpecs(string OS) { 
    if(OS == "Linux" || OS == "Unix") {
        //get the CPU name and erase the trailing newline
        string cpuName  = exec("cat /proc/cpuinfo | grep \"model name\" -m 1");
        cpuName.erase(std::remove(cpuName.begin(), cpuName.end(), '\n'), cpuName.end());

        //gets the clock speed of the CPU and erase the trailing newline
        string cpuMHZ   = exec("cat /proc/cpuinfo | grep \"cpu MHz\" -m 1");
        cpuMHZ.erase(std::remove(cpuMHZ.begin(), cpuMHZ.end(), '\n'), cpuMHZ.end());

        //gets the CPU vendor ID and erase the trailing new line
        string vendorID = exec("cat /proc/cpuinfo | grep \"vendor_id\" -m 1");
        vendorID.erase(std::remove(vendorID.begin(), vendorID.end(), '\n'), vendorID.end());

        //gets the level 1 cache and remove the trailing new line
        string l1Cache  = exec("cat /proc/cpuinfo | grep \"cache size\" -m 1");
        l1Cache.erase(std::remove(l1Cache.begin(), l1Cache.end(), '\n'), l1Cache.end());

        //gets the size of the available RAM and cleanses the output to be used as an int for calculations
        string meminfo  = exec("cat /proc/meminfo | grep \"MemTotal\" -m 1");
        meminfo.erase(std::remove(meminfo.begin(), meminfo.end(), '\n'), meminfo.end());
        meminfo.erase(std::remove(meminfo.begin(), meminfo.end(), 'kb'), meminfo.end());
        meminfo.erase(0, 16);

        //convert mem size to megabytes and gigabytes
        int meminfoMB = std::stoi(meminfo) / 1024;
        int meminfoGB = meminfoMB / 1024;

        //print out the info
        cout << "Basic OS Info   : " + OS << endl; 
        cout << cpuName << endl;
        cout << cpuMHZ + " MHZ" << endl;
        cout << vendorID << endl;
        cout << l1Cache << endl;
        cout << "MemTotal        : " + meminfo + " (" + std::to_string(meminfoMB) + " MB, " + std::to_string(meminfoGB) + " GB)" << endl;
        return;
    } if(OS == "Windows 32-bit" || OS == "Windows 64-bit") {
        notYetImplemented("Windows OS information");
    } if(OS == "Mac OSX") {
        cout << "System is macOS, this feature is not yet fully implemented" << endl;

        //get the system version number and then cleanse the output
        string systemVersionNumber = exec("sw_vers | grep ProductVersion");
        systemVersionNumber.erase(0,16);
        systemVersionNumber.erase(std::remove(systemVersionNumber.begin(), systemVersionNumber.end(), '\n'), systemVersionNumber.end());
        
        //get the cpu Info
        string cpuInfo = exec("sysctl -n machdep.cpu.brand_string");
        cpuInfo.erase(std::remove(cpuInfo.begin(), cpuInfo.end(), '\n'), cpuInfo.end());

        //get the RAM size and cleanse the output
        string meminfo  = exec("sysctl hw.memsize");
        meminfo.erase(std::remove(meminfo.begin(), meminfo.end(), '\n'), meminfo.end());
        meminfo.erase(0,12);

        //convert from bytes to KB, to MB, to GB
        long meminfoKB = std::stol(meminfo) /1024;
        long meminfoMB = meminfoKB / 1024;
        long meminfoGB = meminfoMB / 1024;

        cout << "OS Info : " + OS + " " + systemVersionNumber << endl; 
        cout << "CPU Info : " + cpuInfo << endl;
        cout << "RAM Amount : " + std::to_string(meminfoKB) + " KB (" + std::to_string(meminfoMB) + " MB, " + std::to_string(meminfoGB) + " GB)" << endl;
    }
}

//this checks to see if all the required builders/compilers are present UNDER CONSTRUCTION
void checkCompatabilites() {
    //TODO: When the programs to be compiled are programed in, write this
    notYetImplemented("Checking computer benchmark compatabilites");
}

//the main method UNDER CONSTRUCTION
int main() {
    clearScreen();
    //constant variable list
    const string WELCOME_MESSAGE = "GhostCode\'S PROGRAMMING BENCHMARKS (UNIVERSAL COMPATABILITY EDITION)";
    const string CONTINUE_FORWARD = "Press enter to continue...";
    const string OS = getOsName();
    const bool isWindows = OS == "Windows 32-bit" || OS == "Windows 64-bit";

    //check if the OS is Windows...
    if (!isWindows) {
        //if it isn't then try to do the cool multicolor intro
        if (exec("command -v lolcat") != "") {
            string commandToExecute = "echo \"" + WELCOME_MESSAGE + "\" | lolcat -a --duration=20";
            system(commandToExecute.c_str());
        } else { //if not just post the normal message
            cout << WELCOME_MESSAGE << endl;
        }
    } else { //if it is windows we won't have any colorful console output so just post message as normal.
        cout << WELCOME_MESSAGE << endl;
    }
    
    //Copyright info, and also none supported OS alert (should not appear for 99% of users)
    if(getOsName() ==  "Other"){
        cout << "Unfortunately, I could not detect what OS you have. It is very likely that this program has not been designed for this OS and as a result there is no guarantee that this software will be compatible with your computer, so proceed at your own risk.\nThe officially supported operating systems are Windows (tested on 10), macOS (tested on High Serria) and Linux (tested in Ubuntu).\nThis software is provided AS IS and with no warranty. Use this program at your own risk (Possible issues could that arise from using these benchmarks is overheating and damaging parts).\nThis program has certain dependencies, please use the menu to check that you have the dependencies installed.\n(C) GhostCode 2020, this program is distributed using the GNU GPLv3." << endl;
    } if(getOsName() ==  "FreeBSD" || getOsName() == "Unix"){
        cout << "Your OS is: " + OS + ". This program has not been designed to work with this OS and as a result it most likely will not work here. There is no guarantee that this software will be compatible with your computer, proceed at your own risk.\nThe officially supported operating systems are Windows (tested on 10), macOS (tested on High Serria) and Linux (tested in Ubuntu).\nThis software is provided AS IS and with no warranty. Use this program at your own risk (Possible issues could that arise from using these benchmarks is overheating and damaging parts).\nThis program has certain dependencies, please use the menu to check that you have the dependencies installed.\n(C) GhostCode 2020, this program is distributed using the GNU GPLv3." << endl;
    }
     else {
        cout << "Your OS is: " + OS + ". This software is provided AS IS and with no warranty. Use this program at your own risk (Possible issues could that arise from using these benchmarks is overheating and damaging parts).\nThis program has certain dependencies, please use the menu to check that you have the dependencies installed.\n(C) GhostCode 2020, this program is distributed using the GNU GPLv3." << endl;
    }
    pressEnterToContinue();

    //menu loop
    while (true) {
        clearScreen();

        cout << "+----------------------- MAIN MENU ------------------------+" << endl;
        cout << "| 1: View system specifications                            |" << endl;
        cout << "| 2: Check compatabilites                                  |" << endl;
        cout << "| 3: Begin benchmarking (goes to a menu to select options) |" << endl;
        cout << "| 0: Exit                                                  |" << endl;
        cout << "+----------------------------------------------------------+" << endl;;
        cout << "➜ ";

        //conversion of the input to int
        std::string userInputRaw;
        std::getline(std::cin, userInputRaw);

        //if the user input letters/special characters/out of bound choice for some reason alert them to try again
        try {
            int userInput = std::stoi(userInputRaw);
            if(userInput < 0 || userInput > 3){
                cout << "Input not valid, please try again." << endl;
            }
        } catch (exception ex) {
            cout << "Bad input, please try again." << endl;
        }

        //selection for menu input
        if (userInputRaw == "1") {
            showSystemSpecs(OS);
        }
        if (userInputRaw == "2") {
            checkCompatabilites();
        }
        if (userInputRaw == "3") {
            notYetImplemented("Benchmarking");
        }
        if (userInputRaw == "0") {
            break;
        }

        pressEnterToContinue();
    }

    //end program
    return 0;
}