#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
using namespace std;

map<string, vector<string>> grammar;
vector<string> nonTerminals;
vector<string> terminals = {"+", "*", "(", ")", "i"};
string startSymbol = "E";
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;

bool isTerminal(string s) {
    for (auto &t : terminals) if (t == s) return true;
    return false;
}

set<string> computeFirst(string symbol) {
    if (isTerminal(symbol)) return {symbol};
    if (symbol == "ε") return {"ε"};

    set<string> &resultSet = FIRST[symbol];

    for (auto &production : grammar[symbol]) {
        bool broke = false;
        for (int i = 0; i < production.length(); i++) {
            string charAt(1, production[i]);
            set<string> charFirst = computeFirst(charAt);

            for (auto &x : charFirst) {
                if (x != "ε") resultSet.insert(x);
            }

            if (!charFirst.count("ε")) {
                broke = true;
                break;
            }
        }
        if (!broke) resultSet.insert("ε");
    }

    return resultSet;
}

void computeFollow() {
    FOLLOW[startSymbol].insert("$");

    bool changed = true;
    while (changed) {
        changed = false;

        for (auto &entry : grammar) {
            string head = entry.first;

            for (auto &prod : entry.second) {
                for (int i = 0; i < prod.length(); i++) {
                    string symbol(1, prod[i]);

                    bool isNT = false;
                    for (auto &nt : nonTerminals) if (nt == symbol) isNT = true;

                    if (isNT) {
                        set<string> &symbolFollow = FOLLOW[symbol];
                        int before = symbolFollow.size();

                        if (i + 1 < prod.length()) {
                            set<string> firstNext;
                            bool allDeriveEpsilon = true;

                            for (int j = i + 1; j < prod.length(); j++) {
                                string nextSym(1, prod[j]);
                                set<string> nextFirst = computeFirst(nextSym);

                                for (auto &x : nextFirst) {
                                    if (x != "ε") firstNext.insert(x);
                                }

                                if (!nextFirst.count("ε")) {
                                    allDeriveEpsilon = false;
                                    break;
                                }
                            }

                            symbolFollow.insert(firstNext.begin(), firstNext.end());

                            if (allDeriveEpsilon) {
                                symbolFollow.insert(FOLLOW[head].begin(), FOLLOW[head].end());
                            }
                        } else {
                            symbolFollow.insert(FOLLOW[head].begin(), FOLLOW[head].end());
                        }

                        if (symbolFollow.size() > before) changed = true;
                    }
                }
            }
        }
    }
}

int main() {
    grammar["E"] = {"TR"};
    grammar["R"] = {"+TR", "ε"};
    grammar["T"] = {"FY"};
    grammar["Y"] = {"*FY", "ε"};
    grammar["F"] = {"(E)", "i"};

    for (auto &g : grammar) nonTerminals.push_back(g.first);

    for (auto &nt : nonTerminals) {
        FIRST[nt] = {};
        FOLLOW[nt] = {};
    }

    for (auto &nt : nonTerminals) computeFirst(nt);

    computeFollow();

    cout << "FIRST Sets:\n";
    for (auto &nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (auto &x : FIRST[nt]) cout << x << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW Sets:\n";
    for (auto &nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (auto &x : FOLLOW[nt]) cout << x << " ";
        cout << "}\n";
    }

    return 0;
}