#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
    vector<string> non_terminals = {"E", "R", "T", "Y", "F"};
    vector<string> terminals = {"+", "*", "(", ")", "i", "$"};

    map<pair<string, string>, string> parsing_table;

    parsing_table[{"E","("}] = "E -> TR";
    parsing_table[{"E","i"}] = "E -> TR";

    parsing_table[{"R","+"}] = "R -> +TR";
    parsing_table[{"R",")"}] = "R -> ε";
    parsing_table[{"R","$"}] = "R -> ε";

    parsing_table[{"T","("}] = "T -> FY";
    parsing_table[{"T","i"}] = "T -> FY";

    parsing_table[{"Y","*"}] = "Y -> *FY";
    parsing_table[{"Y","+"}] = "Y -> ε";
    parsing_table[{"Y",")"}] = "Y -> ε";
    parsing_table[{"Y","$"}] = "Y -> ε";

    parsing_table[{"F","("}] = "F -> (E)";
    parsing_table[{"F","i"}] = "F -> i";

    cout << "LL(1) Parsing Table:\n\n";

    for (auto &nt : non_terminals) {
        for (auto &t : terminals) {
            if (parsing_table.count({nt, t})) {
                cout << "M[" << nt << ", " << t << "] = "
                     << parsing_table[{nt, t}] << endl;
            }
        }
    }

    return 0;
}