#include <bits/stdc++.h>
using namespace std;

map<string, map<string, string>> parsingTable;
stack<string> st;

void initTable() {
    parsingTable["E"]["id"] = "T E'";
    parsingTable["E"]["("]  = "T E'";

    parsingTable["E'"]["+"] = "+ T E'";
    parsingTable["E'"][")"] = "ε";
    parsingTable["E'"]["$"] = "ε";

    parsingTable["T"]["id"] = "F T'";
    parsingTable["T"]["("]  = "F T'";

    parsingTable["T'"]["*"] = "* F T'";
    parsingTable["T'"]["+"] = "ε";
    parsingTable["T'"][")"] = "ε";
    parsingTable["T'"]["$"] = "ε";

    parsingTable["F"]["id"] = "id";
    parsingTable["F"]["("]  = "( E )";
}

void parse(vector<string> input) {
    st.push("$");
    st.push("E");

    int index = 0;

    while (!st.empty()) {
        string top = st.top();
        string current = input[index];

        if (top == current) {
            st.pop();
            index++;
        }
        else if (parsingTable.find(top) == parsingTable.end()) {
            cout << "Error\n";
            return;
        }
        else {
            string production = parsingTable[top][current];

            if (production == "") {  // same as null check
                cout << "Error\n";
                return;
            }

            st.pop();

            if (production != "ε") {
                vector<string> symbols;
                stringstream ss(production);
                string temp;

                while (ss >> temp) {
                    symbols.push_back(temp);
                }

                reverse(symbols.begin(), symbols.end());

                for (auto &s : symbols) {
                    st.push(s);
                }
            }
        }
    }

    if (index == input.size())
        cout << "Parsing successful\n";
    else
        cout << "Error\n";
}

int main() {
    initTable();

    vector<string> input = {"id", "+", "id", "*", "id", "$"};

    parse(input);

    return 0;
}