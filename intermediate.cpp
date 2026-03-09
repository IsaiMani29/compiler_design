#include <iostream>
#include <string>
using namespace std;

void trim(string &s) {
    int start = 0, end = s.size() - 1;
    while (start <= end && isspace(s[start])) start++;
    while (end >= start && isspace(s[end])) end--;
    s = s.substr(start, end - start + 1);
}

void runIntermediate() {
    cout << "\n--- PHASE 4: INTERMEDIATE CODE GENERATION ---\n\n";
    cout << "Enter statements (type 'exit' to stop)\n\n";

    string line;
    int tempCount = 1;

    while (true) {
        cout << ">> ";
        getline(cin, line);
        trim(line);

        if (line == "exit") break;
        if (line.empty()) continue;

        if (line.back() == ';') line.pop_back();

        if (line.find('=') != string::npos && line.find('+') != string::npos) {
            int eq = line.find('=');
            string lhs = line.substr(0, eq);
            string rhs = line.substr(eq + 1);

            trim(lhs);
            trim(rhs);

            int plus = rhs.find('+');
            string a = rhs.substr(0, plus);
            string b = rhs.substr(plus + 1);

            trim(a);
            trim(b);

            cout << "t" << tempCount << " = " << a << " + " << b << endl;
            cout << lhs << " = t" << tempCount << endl;
            tempCount++;
        } 
        else if (line.find('=') != string::npos) {
            cout << line << endl;
        } 
        else {
            cout << "Invalid statement" << endl;
        }
    }

    cout << "\nIntermediate Code Generation Finished." << endl;
}

int main() {
    runIntermediate();
    return 0;
}