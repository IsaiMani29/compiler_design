#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transition {
public:
    int from;
    int to;
    char symbol;

    Transition(int f, char s, int t) {
        from = f;
        symbol = s;
        to = t;
    }
};

class NFA {
public:
    int start;
    int accept;
    vector<Transition> transitions;

    NFA(int s, int a, vector<Transition> t) {
        start = s;
        accept = a;
        transitions = t;
    }
};

NFA reToNfa(string regex) {
    int state = 0;
    vector<Transition> transitions;

    int startState = state++;
    int currentState = startState;

    for (char symbol : regex) {
        int nextState = state++;
        transitions.push_back(Transition(currentState, symbol, nextState));
        currentState = nextState;
    }

    return NFA(0, currentState, transitions);
}

int main() {
    string regex;
    cout << "Enter Regular Expression: ";
    cin >> regex;

    NFA nfa = reToNfa(regex);

    cout << "\nNFA Representation\n";
    cout << "Start State: " << nfa.start << endl;
    cout << "Accept State: " << nfa.accept << endl;

    cout << "\nTransitions:\n";
    for (auto &t : nfa.transitions) {
        cout << t.from << " -- " << t.symbol << " --> " << t.to << endl;
    }

    return 0;
}