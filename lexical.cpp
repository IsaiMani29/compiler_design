#include <iostream>
#include <string>
#include <set>
#include <regex>
using namespace std;

int main() {
    set<string> KEYWORDS = {"int","float","if","else","while","return","for","switch","elif"};
    set<string> OPERATORS = {"+","-","*","/","=",">","<"};
    set<string> DELIMITERS = {";","(",",",")","{","}"};

    string line, code;
    cout << "Enter the source code (end input with an empty line):\n";

    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        code += line + "\n";
    }

    cout << "\nLEXICAL ANALYSIS OUTPUT:\n\n";

    regex pattern("[A-Za-z_]\\w*|\\d+|\\S");
    auto words_begin = sregex_iterator(code.begin(), code.end(), pattern);
    auto words_end = sregex_iterator();

    for (auto i = words_begin; i != words_end; ++i) {
        string token = i->str();
        string type;

        if (KEYWORDS.count(token)) {
            type = "KEYWORD";
        } else if (OPERATORS.count(token)) {
            type = "OPERATOR";
        } else if (DELIMITERS.count(token)) {
            type = "DELIMITER";
        } else if (regex_match(token, regex("\\d+"))) {
            type = "NUMBER";
        } else {
            type = "IDENTIFIER";
        }

        cout << token << " -> " << type << endl;
    }

    return 0;
}