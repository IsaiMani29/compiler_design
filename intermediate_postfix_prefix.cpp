#include <bits/stdc++.h>
using namespace std;

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return -1;
}

string infixToPostfix(string expr) {
    string result = "";
    stack<char> st;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop(); // remove '('
        }
        else {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

string infixToPrefix(string expr) {
    reverse(expr.begin(), expr.end());

    // swap brackets
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }

    string postfix = infixToPostfix(expr);
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

int main() {
    string expr = "(a+b)*c-d";

    string postfix = infixToPostfix(expr);
    string prefix = infixToPrefix(expr);

    cout << "Infix: " << expr << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    return 0;
}