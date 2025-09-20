#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

// Function: Convert IP string (e.g., "192.168.1.1") into unsigned int format
unsigned int ipToInt(const string& ip) {
    unsigned int result = 0;
    int shift = 24;
    stringstream ss(ip);
    string token;
    // in 32 bit integer move ip into each octet first 24-31,16-23 
    while (getline(ss, token, '.')) {   // split by '.'
        result += stoi(token) << shift; // left shift
        shift -= 8;         // move right 
    }
    return result;
}

// Function: Convert unsigned int back to dotted IP string
string intToIp(unsigned int ipInt) {
    return to_string((ipInt >> 24) & 0xFF) + "." +   // 1st octet
           to_string((ipInt >> 16) & 0xFF) + "." +   // 2nd octet
           to_string((ipInt >> 8) & 0xFF) + "." +    // 3rd octet
           to_string(ipInt & 0xFF);                  // 4th octet
}

// Structure to store IP Class details
struct IPClass {
    string name;          // Class name (A/B/C)
    unsigned int start;   // Starting IP of the class
    unsigned int end;     // Ending IP of the class
    int defaultMaskBits;  // Default mask bits
    string defaultMask;   // Default subnet mask in dotted decimal
};

// range of the ip start-end class A 0.0.0.0 - 127.255.255.255
// 8 = network bits
// 255.0.0.0 subnet mask
const IPClass classes[] = {
    {"A", ipToInt("0.0.0.0"), ipToInt("127.255.255.255"), 8, "255.0.0.0"},
    {"B", ipToInt("128.0.0.0"), ipToInt("191.255.255.255"), 16, "255.255.0.0"},
    {"C", ipToInt("192.0.0.0"), ipToInt("223.255.255.255"), 24, "255.255.255.0"}
};

const IPClass* getClass(unsigned int ip) {
    for (auto &c : classes) {
        if (ip >= c.start && ip <= c.end)  // ip in which range
            return &c;
    }
    return nullptr;  // if not A/B/C
}

// Function: Generate subnet mask from number of mask bits
string maskFromBits(int bits) {// bits=26
    unsigned int mask = 0xFFFFFFFF << (32 - bits); 
    // 0xFFFFFFFF = 11111111.11111111.11111111.11111111
    //0xFFFFFFFF<<(32-26) = 8 = 11111111.11111111.11111111.00000000
    return intToIp(mask);
}

// Function: Subnetting based on number of subnets
void subnetByNetwork(unsigned int ipInt, const IPClass* ipClass) {
    int requiredSubnets;
    cout << "Enter number of required subnets: ";
    cin >> requiredSubnets;

    // find how many bits to borrow
    int bitsToBorrow = 0;
    while (pow(2, bitsToBorrow) < requiredSubnets) {
        bitsToBorrow++;  // check all 2^0,2^1,2^2,2^3 the time > n value got n=no.of network bit
    }
    // tells increase subnet length if 24 first then n=2 so 24+2=26
    int newMaskBits = ipClass->defaultMaskBits + bitsToBorrow;  // new mask length
    if (newMaskBits > 30) {  // sanity check
        cout << "Too many bits borrowed; less than 2 hosts possible." << endl;
        return;
    }

    int hostBits = 32 - newMaskBits;        // remaining host bits 32-24
    int noOfSubnets = pow(2, bitsToBorrow);                // subnets created
    int hostsPerSubnet = pow(2, hostBits) - 2;  // usable hosts

    cout << "Bits borrowed: " << bitsToBorrow << endl;
    cout << "New subnet mask: " << maskFromBits(newMaskBits) << " /" << newMaskBits << endl;
    cout << "Number of subnets: " << noOfSubnets << endl;
    cout << "Number of hosts per subnet: " << hostsPerSubnet << endl << endl;

    // Calculate network, broadcast, and range for each subnet
    unsigned int subnetSize = pow(2, hostBits);
    for (int i = 0; i < noOfSubnets; i++) {
        //192.168.6.130 binary 11000000 10101000 00000110 10000010
        // subnet 11111111 11111111 11111111 00000000
        // 11000000 10101000 00000110 00000000 bitwise remove host

        unsigned int subnetNetwork = (ipInt & (0xFFFFFFFF << (32 - newMaskBits))) + (i * subnetSize);
        // first it i*subnetSize = 0, second it =64
        // broadcast n/w+subnetsize-1
        unsigned int subnetBroadcast = subnetNetwork + subnetSize - 1;

        cout << "Subnet " << (i + 1) << ":\n";
        cout << "  Network Address:   " << intToIp(subnetNetwork) << "\n";
        cout << "  Broadcast Address: " << intToIp(subnetBroadcast) << "\n";
        cout << "  Host IP Range:     " << intToIp(subnetNetwork + 1) << " - " 
             << intToIp(subnetBroadcast - 1) << "\n\n";
    }
}

// Function: Subnetting based on number of hosts per subnet
void subnetByHosts(unsigned int ipInt, const IPClass* ipClass) {
    int requiredHosts;
    cout << "Enter number of required hosts per subnet: ";
    cin >> requiredHosts;

    // calculate required host bits
    int hostBits = 0;
    while ((pow(2, hostBits) - 2) < requiredHosts) {
        hostBits++;
    }

    int newMaskBits = 32 - hostBits;                           // new subnet mask length
    int borrowedBits = newMaskBits - ipClass->defaultMaskBits;
    if (newMaskBits < ipClass->defaultMaskBits) {
        cout << "Not possible with this IP class." << endl;
        return;
    }

    int hostsPerSubnet = pow(2, hostBits) - 2;                 // usable hosts
    int noOfSubnets = pow(2, borrowedBits);             // number of subnets

    cout << "Host bits (h): " << hostBits << endl;
    cout << "New subnet mask: " << maskFromBits(newMaskBits) << " /" << newMaskBits << endl;
    cout << "Number of subnets: " << noOfSubnets << endl;
    cout << "Number of hosts per subnet: " << hostsPerSubnet << endl << endl;

    // Calculate subnet ranges
    unsigned int subnetSize = pow(2, hostBits);
    for (int i = 0; i < noOfSubnets; i++) {
        unsigned int subnetNetwork = (ipInt & (0xFFFFFFFF << (32 - newMaskBits))) + (i * subnetSize);
        unsigned int subnetBroadcast = subnetNetwork + subnetSize - 1;

        cout << "Subnet " << (i + 1) << ":\n";
        cout << "  Network Address:   " << intToIp(subnetNetwork) << "\n";
        cout << "  Broadcast Address: " << intToIp(subnetBroadcast) << "\n";
        cout << "  Host IP Range:     " << intToIp(subnetNetwork + 1) << " - " 
             << intToIp(subnetBroadcast - 1) << "\n\n";
    }
}

int main() {
    string ip;
    int choice;

    cout << "Enter IP Address (e.g., 192.168.1.0): ";
    cin >> ip;  // take IP from user

    unsigned int ipInt = ipToInt(ip);  // convert to int
    const IPClass* ipClass = getClass(ipInt);  // detect class

    if (!ipClass) {
        cout << "Invalid or unsupported IP address class." << endl;
        return 1;
    }

    // Show detected class and default mask
    cout << "Detected IP Class: " << ipClass->name << endl;
    cout << "Default subnet mask: " << ipClass->defaultMask << endl;

    // Ask user choice
    cout << "\nChoose option:\n";
    cout << "1. Subnetting based on number on networks\n";
    cout << "2. Subnetting based on number on hosts \n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            subnetByNetwork(ipInt, ipClass);
            break;
        case 2:
            subnetByHosts(ipInt, ipClass);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
