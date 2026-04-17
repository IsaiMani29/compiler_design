#include <bits/stdc++.h>
using namespace std;

class StackFrame {
public:
    string functionName;
    map<string, int> localVariables;

    StackFrame(string functionName) {
        this->functionName = functionName;
    }

    void addVariable(string name, int value) {
        localVariables[name] = value;
    }

    string toString() const {
        string result = "Function: " + functionName + ", Locals: {";
        for (auto it : localVariables) {
            result += it.first + "=" + to_string(it.second) + ", ";
        }
        if (!localVariables.empty()) result.pop_back(), result.pop_back(); // remove ", "
        result += "}";
        return result;
    }
};

stack<StackFrame> callStack;

void printStack(stack<StackFrame> s) {
    vector<StackFrame> temp;

    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }

    reverse(temp.begin(), temp.end());

    cout << "[ ";
    for (auto &frame : temp) {
        cout << frame.toString() << " ";
    }
    cout << "]\n";
}

void callFunction(string name) {
    StackFrame frame(name);
    callStack.push(frame);
    cout << "Entered " << name << " -> Stack: ";
    printStack(callStack);
}

void addLocal(string var, int value) {
    StackFrame &current = callStack.top();  // reference (important!)
    current.addVariable(var, value);
    cout << "Added local " << var << "=" << value << " -> Stack: ";
    printStack(callStack);
}

void returnFunction() {
    StackFrame frame = callStack.top();
    callStack.pop();
    cout << "Returned from " << frame.functionName << " -> Stack: ";
    printStack(callStack);
}

int main() {
    callFunction("main");
    addLocal("x", 10);
    callFunction("foo");
    addLocal("y", 20);
    returnFunction();
    addLocal("z", 30);
    returnFunction();

    return 0;
}