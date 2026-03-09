#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>
using namespace std;

void convert(map<char, map<int, set<int>>> &nfa, int start, set<int> nfaFinals) {
    
    map<set<int>, map<char, set<int>>> dfa;
    queue<set<int>> unmarkedStates;
    vector<set<int>> dfaStates;

    set<int> startSet = {start};
    unmarkedStates.push(startSet);
    dfaStates.push_back(startSet);

    while (!unmarkedStates.empty()) {
        set<int> current = unmarkedStates.front();
        unmarkedStates.pop();

        for (auto &symbolPair : nfa) {
            char symbol = symbolPair.first;
            set<int> nextState;

            for (int state : current) {
                if (nfa[symbol].count(state)) {
                    nextState.insert(
                        nfa[symbol][state].begin(),
                        nfa[symbol][state].end()
                    );
                }
            }

            if (!nextState.empty()) {
                dfa[current][symbol] = nextState;

                bool exists = false;
                for (auto &s : dfaStates) {
                    if (s == nextState) {
                        exists = true;
                        break;
                    }
                }

                if (!exists) {
                    dfaStates.push_back(nextState);
                    unmarkedStates.push(nextState);
                }
            }
        }
    }

    cout << "DFA States:\n";
    for (auto &state : dfaStates) {
        cout << "{ ";
        for (int s : state) cout << s << " ";
        cout << "}\n";
    }

    cout << "\nDFA Transitions:\n";
    for (auto &entry : dfa) {
        for (auto &trans : entry.second) {
            cout << "{ ";
            for (int s : entry.first) cout << s << " ";
            cout << "} --" << trans.first << "--> { ";

            for (int s : trans.second) cout << s << " ";
            cout << "}\n";
        }
    }

    cout << "\nDFA Final States:\n";
    for (auto &state : dfaStates) {
        for (int s : state) {
            if (nfaFinals.count(s)) {
                cout << "{ ";
                for (int x : state) cout << x << " ";
                cout << "}\n";
                break;
            }
        }
    }
}

int main() {

    map<char, map<int, set<int>>> nfa;

    nfa['a'][0] = {0,1};
    nfa['a'][1] = {2};

    nfa['b'][0] = {0};
    nfa['b'][1] = {1};
    nfa['b'][2] = {2};

    int startState = 0;
    set<int> nfaFinalStates = {2};

    convert(nfa, startState, nfaFinalStates);

    return 0;
}