#include <iostream>
#include <stack>
#include <map>
#include <regex>
#include <string>
using namespace std;

class CodeGenerator {
private:
    stack<string> operatorStack;
    stack<string> operandStack;
    int tempCount = 0;
    map<string, int> PRECEDENCE;

public:
    CodeGenerator() {
        PRECEDENCE["+"] = 1;
        PRECEDENCE["-"] = 1;
        PRECEDENCE["*"] = 2;
        PRECEDENCE["/"] = 2;
        PRECEDENCE["^"] = 3;
    }

    string newTemp() {
        tempCount++;
        return "t" + to_string(tempCount);
    }

    string generateInstruction(string op, string arg1, string arg2) {
        string tempVar = newTemp();
        cout << tempVar << " = " << arg1 << " " << op << " " << arg2 << endl;
        return tempVar;
    }

    void processOperator() {
        if (operandStack.size() < 2) return;

        string op = operatorStack.top();
        operatorStack.pop();

        string right = operandStack.top();
        operandStack.pop();

        string left = operandStack.top();
        operandStack.pop();

        string resultTemp = generateInstruction(op, left, right);
        operandStack.push(resultTemp);
    }

    void parseAndGenerate(string expression) {
        cout << "\n--- Generating Code for: " << expression << " ---" << endl;
        cout << "Generated Instructions:" << endl;

        string lhs = "";
        size_t pos = expression.find("=");

        if (pos != string::npos) {
            lhs = expression.substr(0, pos);
            expression = expression.substr(pos + 1);
        }

        regex pattern("(\\d+|[a-zA-Z_]\\w*|[-+*/^()])");
        sregex_iterator iter(expression.begin(), expression.end(), pattern);
        sregex_iterator end;

        for (; iter != end; ++iter) {
            string token = iter->str();

            if (regex_match(token, regex("\\w+"))) {
                operandStack.push(token);
            }
            else if (token == "(") {
                operatorStack.push(token);
            }
            else if (token == ")") {
                while (!operatorStack.empty() && operatorStack.top() != "(") {
                    processOperator();
                }
                if (!operatorStack.empty()) operatorStack.pop();
            }
            else if (PRECEDENCE.count(token)) {
                while (!operatorStack.empty() &&
                       PRECEDENCE.count(operatorStack.top()) &&
                       PRECEDENCE[operatorStack.top()] >= PRECEDENCE[token]) {
                    processOperator();
                }
                operatorStack.push(token);
            }
        }

        while (!operatorStack.empty()) {
            processOperator();
        }

        if (!lhs.empty() && !operandStack.empty()) {
            string finalResult = operandStack.top();
            operandStack.pop();
            cout << lhs << " = " << finalResult << endl;
        }

        cout << "---------------------------------------" << endl;

        tempCount = 0;
        while (!operatorStack.empty()) operatorStack.pop();
        while (!operandStack.empty()) operandStack.pop();
    }
};

int main() {
    CodeGenerator generator;
    string input;

    cout << "Compiler Design: Simple Code Generator" << endl;
    cout << "Enter expressions like: x = a + b * (c - d)" << endl;
    cout << "Type 'exit' to quit.\n" << endl;

    while (true) {
        cout << "Enter expression: ";
        getline(cin, input);

        if (input == "exit") break;

        try {
            generator.parseAndGenerate(input);
        }
        catch (...) {
            cout << "Error parsing expression." << endl;
        }
    }

    return 0;
}