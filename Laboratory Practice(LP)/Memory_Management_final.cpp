#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Memory {
    int *blocks, *process, *flags;
    int b_size, p_size;

public:
    Memory() {
        b_size = 0;
        p_size = 0;
    }

    void take_input();
    void give_output(string, map<int, int>);
    void first_fit();
    void best_fit();
    void worst_fit();
};

void Memory::take_input() {
    cout << "\nEnter number of blocks: ";
    cin >> b_size;
    cout << "\nEnter number of processes: ";
    cin >> p_size;

    blocks = new int[b_size];
    process = new int[p_size];
    flags = new int[b_size];

    cout << "\nEnter block sizes: ";
    for (int i = 0; i < b_size; i++)
        cin >> blocks[i];

    cout << "\nEnter process sizes: ";
    for (int i = 0; i < p_size; i++)
        cin >> process[i];
}

void Memory::give_output(string algo, map<int, int> mp) {
    cout << "\n------------------------ " << algo << " ------------------------\n";
    cout << "Block No" << setw(15) << "Block Size" 
         << setw(20) << "Process Size" 
         << setw(20) << "Waste Memory\n";

    for (auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first << setw(15) 
             << blocks[it->first] << setw(20) 
             << it->second << setw(20) 
             << blocks[it->first] - it->second << "\n";
    }
}

void Memory::first_fit() {
    map<int, int> mp;
    int *not_allocated = new int[p_size];

    for (int i = 0; i < b_size; i++) flags[i] = 0;
    for (int i = 0; i < p_size; i++) not_allocated[i] = 0;

    for (int i = 0; i < p_size; i++) {
        for (int j = 0; j < b_size; j++) {
            if (process[i] <= blocks[j] && flags[j] == 0) {
                mp[j] = process[i];
                flags[j] = 1;
                not_allocated[i] = 1;
                break;
            }
        }
    }

    give_output("First Fit", mp);

    cout << "\nProcesses not allocated:";
    for (int i = 0; i < p_size; i++) {
        if (not_allocated[i] == 0)
            cout << "\nProcess " << process[i];
    }
    cout << endl;
    delete[] not_allocated;
}

void Memory::best_fit() {
    map<int, int> mp;
    int *not_allocated = new int[p_size];

    for (int i = 0; i < b_size; i++) flags[i] = 0;
    for (int i = 0; i < p_size; i++) not_allocated[i] = 0;

    int wastage[b_size];

    for (int i = 0; i < p_size; i++) {
        for (int k = 0; k < b_size; k++) wastage[k] = 9999;

        for (int j = 0; j < b_size; j++) {
            if (process[i] <= blocks[j] && flags[j] == 0) {
                wastage[j] = blocks[j] - process[i];
            }
        }

        int min_val = *min_element(wastage, wastage + b_size);
        if (min_val == 9999) {
            not_allocated[i] = 0;
            continue;
        }

        int pos = find(wastage, wastage + b_size, min_val) - wastage;
        mp[pos] = process[i];
        flags[pos] = 1;
        not_allocated[i] = 1;
    }

    give_output("Best Fit", mp);

    cout << "\nProcesses not allocated:";
    for (int i = 0; i < p_size; i++) {
        if (not_allocated[i] == 0)
            cout << "\nProcess " << process[i];
    }
    cout << endl;
    delete[] not_allocated;
}

void Memory::worst_fit() {
    map<int, int> mp;
    int *not_allocated = new int[p_size];

    for (int i = 0; i < b_size; i++) flags[i] = 0;
    for (int i = 0; i < p_size; i++) not_allocated[i] = 0;

    int wastage[b_size];

    for (int i = 0; i < p_size; i++) {
        for (int k = 0; k < b_size; k++) wastage[k] = -1;

        for (int j = 0; j < b_size; j++) {
            if (process[i] <= blocks[j] && flags[j] == 0) {
                wastage[j] = blocks[j] - process[i];
            }
        }

        int max_val = *max_element(wastage, wastage + b_size);
        if (max_val == -1) {
            not_allocated[i] = 0;
            continue;
        }

        int pos = find(wastage, wastage + b_size, max_val) - wastage;
        mp[pos] = process[i];
        flags[pos] = 1;
        not_allocated[i] = 1;
    }

    give_output("Worst Fit", mp);

    cout << "\nProcesses not allocated:";
    for (int i = 0; i < p_size; i++) {
        if (not_allocated[i] == 0)
            cout << "\nProcess " << process[i];
    }
    cout << endl;
    delete[] not_allocated;
}

int main() {
    Memory m;
    m.take_input();
    m.first_fit();
    m.best_fit();
    m.worst_fit();
    return 0;
}
