#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;

void addProduction(string lhs, string rhs) {
    grammar[lhs].push_back(rhs);
}

void removeLeftRecursion(string nonTerminal) {
    vector<string> prods = grammar[nonTerminal];
    vector<string> alpha, beta;

    for (auto &p : prods) {
        if (p.substr(0, nonTerminal.length()) == nonTerminal) {
            alpha.push_back(p.substr(nonTerminal.length()));
        } else {
            beta.push_back(p);
        }
    }

    if (!alpha.empty()) {
        string newNT = nonTerminal + "'";

        vector<string> newProds;
        for (auto &b : beta) {
            newProds.push_back(b + newNT);
        }
        grammar[nonTerminal] = newProds;

        vector<string> alphaProds;
        for (auto &a : alpha) {
            alphaProds.push_back(a + newNT);
        }
        alphaProds.push_back("ε");

        grammar[newNT] = alphaProds;
    }
}

void leftFactor(string nonTerminal) {
    vector<string> prods = grammar[nonTerminal];
    map<string, vector<string>> prefixMap;

    for (auto &p : prods) {
        string prefix(1, p[0]);  // first character
        prefixMap[prefix].push_back(p);
    }

    for (auto &entry : prefixMap) {
        if (entry.second.size() > 1) {
            string newNT = nonTerminal + "'";

            vector<string> newProds;
            for (auto &p : entry.second) {
                string rest = (p.length() > 1) ? p.substr(1) : "ε";
                newProds.push_back(rest);
            }

            grammar[newNT] = newProds;

            // remove old productions
            vector<string> &orig = grammar[nonTerminal];
            for (auto &p : entry.second) {
                orig.erase(remove(orig.begin(), orig.end(), p), orig.end());
            }

            // add factored production
            orig.push_back(entry.first + newNT);
        }
    }
}

void printGrammar() {
    for (auto &e : grammar) {
        cout << e.first << " -> ";
        for (int i = 0; i < e.second.size(); i++) {
            cout << e.second[i];
            if (i != e.second.size() - 1) cout << " | ";
        }
        cout << endl;
    }
}

int main() {
    addProduction("E", "E+T");
    addProduction("E", "T");
    addProduction("T", "T*F");
    addProduction("T", "F");
    addProduction("F", "(E)");
    addProduction("F", "id");

    cout << "Original Grammar:\n";
    printGrammar();

    removeLeftRecursion("E");
    removeLeftRecursion("T");

    cout << "\nAfter Removing Left Recursion:\n";
    printGrammar();

    leftFactor("E");
    leftFactor("T");

    cout << "\nAfter Left Factoring:\n";
    printGrammar();

    return 0;
}