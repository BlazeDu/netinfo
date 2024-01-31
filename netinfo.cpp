#include <iostream>
#include <cstdio>
using namespace std;

const string serverIPAddress = "208.67.222.222";

bool isNetworkAvailable()
{
    string command = "ping -c 1 -W 1 " + serverIPAddress + " > /dev/null 2>&1";
    int result = system(command.c_str());
    return (result == 0);
}

void printWiFiInfo()
{
    string command = "networksetup -getairportnetwork en0";
    FILE *fp = popen(command.c_str(), "r");
    if (fp)
    {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), fp) != nullptr)
        {
            const char *prefix = "Current Wi-Fi Network: ";
            if (strncmp(buffer, prefix, strlen(prefix)) == 0)
                cout << "Info: \033[1;34m" << (buffer + strlen(prefix)) << "\033[0m";
            else
                cout << buffer;
        }
        pclose(fp);
    }
}

// Function to print text in green color
void printGreenText(const string &text)
{
    cout << "\033[1;32m" << text << "\033[0m";
}

// Function to print text in red color
void printRedText(const string &text)
{
    cout << "\033[1;31m" << text << "\033[0m";
}

void printState()
{
    cout << "State: ";
    if (isNetworkAvailable())
        printGreenText("Available\n");
    else
        printRedText("Not available\n");
}

int main()
{
    printWiFiInfo();
    printState();
    return 0;
}