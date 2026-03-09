#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

bool isNumeric(const string &str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void trim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

void runOptimization() {
    cout << "\n--- PHASE 5: CODE OPTIMIZATION ---\n\n";
    cout << "Enter statements (type 'exit' to stop)\n\n";

    string line;

    while (true) {
        cout << ">> ";
        getline(cin, line);
        trim(line);

        if (line == "exit") {
            break;
        }

        if (line.empty()) {
            continue;
        }

        // Remove semicolon
        if (!line.empty() && line.back() == ';') {
            line.pop_back();
        }

        // 1. Constant Folding (x = 5 + 10 -> x = 15)
        if (line.find('=') != string::npos && line.find('+') != string::npos) {
            size_t eq = line.find('=');
            string lhs = line.substr(0, eq);
            string rhs = line.substr(eq + 1);

            trim(lhs);
            trim(rhs);

            size_t plus = rhs.find('+');
            if (plus != string::npos) {
                string a = rhs.substr(0, plus);
                string b = rhs.substr(plus + 1);

                trim(a);
                trim(b);

                if (isNumeric(a) && isNumeric(b)) {
                    int result = stoi(a) + stoi(b);
                    cout << lhs << " = " << result << endl;
                    continue;
                }
            }
        }

        // 2. Redundant Assignment Removal (x = x)
        if (line.find('=') != string::npos) {
            size_t eq = line.find('=');
            string lhs = line.substr(0, eq);
            string rhs = line.substr(eq + 1);

            trim(lhs);
            trim(rhs);

            if (lhs == rhs) {
                cout << "Removed redundant assignment: " << line << endl;
                continue;
            }
        }

        // Default: print original line
        cout << line << endl;
    }

    cout << "\nOptimization Finished." << endl;
}

int main() {
    runOptimization();
    return 0;
}