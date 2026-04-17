#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> nonTerminals = {"E", "R", "T", "Y", "F"};
    vector<string> terminals = {"+", "*", "(", ")", "i", "$"};

    map<string, map<string, string>> table;

    table["E"]["("] = "E -> TR";
    table["E"]["i"] = "E -> TR";

    table["R"]["+"] = "R -> +TR";
    table["R"][")"] = "R -> ε";
    table["R"]["$"] = "R -> ε";

    table["T"]["("] = "T -> FY";
    table["T"]["i"] = "T -> FY";

    table["Y"]["*"] = "Y -> *FY";
    table["Y"]["+"] = "Y -> ε";
    table["Y"][")"] = "Y -> ε";
    table["Y"]["$"] = "Y -> ε";

    table["F"]["("] = "F -> (E)";
    table["F"]["i"] = "F -> i";

    cout << "LL(1) Parsing Table:\n\n";

    for (auto &nt : nonTerminals) {
        for (auto &t : terminals) {
            if (table.count(nt) && table[nt].count(t)) {
                cout << "M[" << nt << ", " << t << "] = "
                     << table[nt][t] << endl;
            }
        }
    }

    return 0;
}