#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;
set<string> terminals;

void addProduction(string lhs, string rhs) {
    grammar[lhs].push_back(rhs);
}

set<string> leading(string nonTerminal) {
    set<string> result;

    for (auto prod : grammar[nonTerminal]) {
        string first(1, prod[0]);  // first symbol

        if (terminals.count(first)) {
            result.insert(first);
        } else {
            set<string> temp = leading(first);
            result.insert(temp.begin(), temp.end());
        }
    }

    return result;
}

set<string> trailing(string nonTerminal) {
    set<string> result;

    for (auto prod : grammar[nonTerminal]) {
        string last(1, prod[prod.length() - 1]);  // last symbol

        if (terminals.count(last)) {
            result.insert(last);
        } else {
            set<string> temp = trailing(last);
            result.insert(temp.begin(), temp.end());
        }
    }

    return result;
}

int main() {
    terminals.insert("a");
    terminals.insert("b");
    terminals.insert("c");
    terminals.insert("+");
    terminals.insert("*");

    addProduction("E", "TA");
    addProduction("A", "+TA");
    addProduction("A", "ε");
    addProduction("T", "FB");
    addProduction("B", "*FB");
    addProduction("B", "ε");
    addProduction("F", "a");
    addProduction("F", "b");
    addProduction("F", "(E)");

    cout << "LEADING(E): ";
    for (auto x : leading("E")) cout << x << " ";
    cout << endl;

    cout << "TRAILING(E): ";
    for (auto x : trailing("E")) cout << x << " ";
    cout << endl;

    cout << "LEADING(T): ";
    for (auto x : leading("T")) cout << x << " ";
    cout << endl;

    cout << "TRAILING(T): ";
    for (auto x : trailing("T")) cout << x << " ";
    cout << endl;

    return 0;
}