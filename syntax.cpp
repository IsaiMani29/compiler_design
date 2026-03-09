#include <iostream>
#include <string>
#include <regex>
using namespace std;

void analyze(string statement) {
    statement = regex_replace(statement, regex("^\\s+|\\s+$"), "");
    string pattern = "^[a-zA-Z_]\\w*\\s*=\\s*([a-zA-Z_]\\w*|\\d+)(\\s*[+\\-*/]\\s*([a-zA-Z_]\\w*|\\d+))?$";
    regex r(pattern);

    if (regex_match(statement, r)) {
        cout << "VALID SYNTAX   : " << statement << endl;
    } else {
        cout << "INVALID SYNTAX : " << statement << endl;
    }
}

int main() {
    string input;

    cout << "SYNTAX ANALYSIS RESULT:\n\n";
    cout << "Type 'exit' to stop.\n\n";

    while (true) {
        cout << "Enter a statement: ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Program terminated." << endl;
            break;
        }

        if (!input.empty()) {
            analyze(input);
        }
    }

    return 0;
}