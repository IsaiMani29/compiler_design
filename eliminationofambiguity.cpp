#include <iostream>
#include <vector>
#include <string>
using namespace std;

void eliminateLeftRecursion(string nt, vector<string> productions) {
    vector<string> alpha;
    vector<string> beta;

    for (string prod : productions) {
        if (prod.substr(0, nt.length()) == nt) {
            alpha.push_back(prod.substr(nt.length()));
        } else {
            beta.push_back(prod);
        }
    }

    if (alpha.empty()) {
        for (string p : productions)
            cout << p << " ";
        cout << endl;
        return;
    }

    string newNt = nt + "'";

    cout << nt << " -> ";
    for (string b : beta) {
        cout << b + newNt << " ";
    }
    cout << endl;

    cout << newNt << " -> ";
    for (string a : alpha) {
        cout << a + newNt << " ";
    }
    cout << "ε";
    cout << endl;
}

void leftFactoring(string nt, vector<string> productions) {
    if (productions.empty()) return;

    string prefix = productions[0];

    for (int i = 1; i < productions.size(); i++) {
        string prod = productions[i];
        int j = 0;

        while (j < prefix.length() && j < prod.length() && prefix[j] == prod[j]) {
            j++;
        }

        prefix = prefix.substr(0, j);
    }

    if (prefix.empty()) {
        cout << "No common prefix found.\n";
        return;
    }

    string newNt = nt + "'";

    cout << nt << " -> " << prefix << newNt << endl;
    cout << newNt << " -> ";

    for (string prod : productions) {
        cout << prod.substr(prefix.length()) << " ";
    }
    cout << endl;
}

int main() {

    string nt = "A";
    vector<string> productions = {"Aa", "Ab", "c"};

    cout << "Original Productions: ";
    for (string p : productions) cout << p << " ";
    cout << endl;

    cout << "\nAfter Eliminating Left Recursion:\n";
    eliminateLeftRecursion(nt, productions);

    cout << "\nAfter Left Factoring:\n";
    leftFactoring("A", {"ab", "ac"});

    return 0;
}