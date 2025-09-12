#include <bits/stdc++.h>
using namespace std;

// Structures
struct MacroTableEntry {
    int id;
    string macroName;
    int positionalCount, keywordCount, mdtIndex, kpdtIndex;
};

struct KeywordParamEntry {
    int id;
    string paramName;
    string defaultValue;
};

// Data structures
map<string, vector<string>> paramTable;       // Macro → list of parameters
map<string, map<string, int>> pntabIndex;     // Macro → (paramName → index)
vector<MacroTableEntry> macroTable;           // MNT
vector<KeywordParamEntry> keywordParamTable;  // KPDTAB
vector<string> macroDefTable;                 // MDT

int main() {
    ifstream input("input.asm");
    ofstream mntFile("mnt.txt");
    ofstream pntabFile("pntab.txt");
    ofstream kpdtFile("kpdt.txt");
    ofstream mdtFile("mdt.txt");

    if (!input.is_open()) {
        cerr << "Error opening input.asm\n";
        return 1;
    }

    string line;
    bool insideMacro = false;
    bool headerProcessed = false;
    string currentMacro;
    int mntCounter = 1, kpdtCounter = 1;

    while (getline(input, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> tokens;
        string word;
        while (ss >> word) tokens.push_back(word);

        if (tokens.empty()) continue;

        // Start of macro
        if (tokens[0] == "MACRO") {
            insideMacro = true;
            headerProcessed = false;
            continue;
        }

        // Macro header
        if (insideMacro && !headerProcessed) {
            if (tokens.size() < 2) continue;

            currentMacro = tokens[0];

            string joined;
            for (size_t i = 1; i < tokens.size(); i++) joined += tokens[i] + " ";

            vector<string> params;
            string param;
            stringstream pss(joined);
            while (getline(pss, param, ',')) {
                param.erase(remove_if(param.begin(), param.end(), ::isspace), param.end());
                if (!param.empty()) params.push_back(param);
            }

            int positional = 0, keyword = 0, kpdtStart = 0;
            paramTable[currentMacro] = {};
            pntabIndex[currentMacro] = {};

            for (auto &p : params) {
                if (p[0] == '&') {
                    size_t eq = p.find('=');
                    if (eq == string::npos) {
                        string pname = p.substr(1);
                        paramTable[currentMacro].push_back(pname);
                        pntabIndex[currentMacro][pname] = positional + keyword + 1;
                        positional++;
                    } else {
                        string pname = p.substr(1, eq - 1);
                        string defval = (eq + 1 < p.size()) ? p.substr(eq + 1) : "---";
                        paramTable[currentMacro].push_back(pname);
                        pntabIndex[currentMacro][pname] = positional + keyword + 1;
                        keyword++;
                        if (keyword == 1) kpdtStart = kpdtCounter;
                        keywordParamTable.push_back({kpdtCounter++, pname, defval});
                    }
                }
            }

            macroTable.push_back({mntCounter++, currentMacro, positional, keyword,
                                  (int)macroDefTable.size() + 1,
                                  (keyword ? kpdtStart : -1)});
            headerProcessed = true;
            continue;
        }

        // Macro body
        if (insideMacro) {
            if (tokens[0] == "MEND") {
                macroDefTable.push_back("MEND");
                insideMacro = false;
                currentMacro.clear(); // Clear only after macro ends
                continue;
            } else {
                string processed = "";
                for (auto &tok : tokens) {
                    if (tok.back() == ',') tok.pop_back();

                    size_t amp = tok.find('&');
                    if (amp != string::npos) {
                        string before = tok.substr(0, amp);
                        string pname = tok.substr(amp + 1);
                        int pos = pntabIndex[currentMacro][pname];
                        processed += before + "(P," + to_string(pos) + ") ";
                    } else {
                        processed += tok + " ";
                    }
                }
                macroDefTable.push_back(processed);
            }
        }
    }

    // Write MNT
    mntFile << "Index\tName\tPP\tKP\tMDTP\tKPDTP\n";
    for (auto &e : macroTable) {
        mntFile << e.id << "\t" << e.macroName << "\t" << e.positionalCount << "\t"
                << e.keywordCount << "\t" << e.mdtIndex << "\t"
                << (e.kpdtIndex == -1 ? "---" : to_string(e.kpdtIndex)) << "\n";
    }

    // Write PNTAB
    pntabFile << "PNTAB (Macro → Parameters with Index)\n";
    for (const auto& kv : paramTable) {
        const string& macroName = kv.first;
        const vector<string>& params = kv.second;

        pntabFile << macroName << " : ";
        for (const string& param : params) {
            auto it = pntabIndex[macroName].find(param);
            if (it != pntabIndex[macroName].end()) {
                pntabFile << param << "(" << it->second << ") ";
            } else {
                pntabFile << param << "(?) ";
            }
        }
        pntabFile << "\n";
    }

    // Write KPDTAB
    kpdtFile << "Index\tParam\tDefault\n";
    for (auto &e : keywordParamTable) {
        kpdtFile << e.id << "\t" << e.paramName << "\t" << e.defaultValue << "\n";
    }

    // Write MDT
    mdtFile << "MDT\n";
    for (int i = 0; i < macroDefTable.size(); i++) {
        mdtFile << (i + 1) << "\t" << macroDefTable[i] << "\n";
    }

    cout << "Pass-I Completed. Files generated: mnt.txt, pntab.txt, kpdt.txt, mdt.txt\n";
    return 0;
}
