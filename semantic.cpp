#include <iostream>
#include <string>
#include <set>
#include <sstream>
using namespace std;

void runSemantic() {
    cout << "\n--- PHASE 3: SEMANTIC ANALYSIS ---\n\n";
    cout << "Enter statements (type 'exit' to stop)\n\n";

    set<string> symbolTable;
    string line;

    while (true) {
        cout << ">> ";
        getline(cin, line);

        if (line == "exit") break;
        if (line.empty()) continue;

        if (!line.empty() && line.back() == ';') {
            line.pop_back();
        }

        if (line.rfind("int ", 0) == 0) {
            string vars = line.substr(4);
            stringstream ss(vars);
            string var;

            while (getline(ss, var, ',')) {
                while (!var.empty() && var.front() == ' ') var.erase(var.begin());
                while (!var.empty() && var.back() == ' ') var.pop_back();

                if (symbolTable.count(var)) {
                    cout << "ERROR: " << var << " already declared" << endl;
                } else {
                    symbolTable.insert(var);
                    cout << "Declared: " << var << endl;
                }
            }
        }
        else if (line.find('=') != string::npos) {
            int pos = line.find('=');
            string lhs = line.substr(0, pos);

            while (!lhs.empty() && lhs.front() == ' ') lhs.erase(lhs.begin());
            while (!lhs.empty() && lhs.back() == ' ') lhs.pop_back();

            if (!symbolTable.count(lhs)) {
                cout << "ERROR: " << lhs << " not declared" << endl;
            } else {
                cout << "OK: " << line << endl;
            }
        }
        else {
            cout << "Invalid statement" << endl;
        }
    }

    cout << "\nFinal Symbol Table: ";
    for (auto &s : symbolTable) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    runSemantic();
    return 0;
}