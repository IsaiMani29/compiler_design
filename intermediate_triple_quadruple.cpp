#include <bits/stdc++.h>
using namespace std;

class Quadruple {
public:
    string op, arg1, arg2, result;

    Quadruple(string op, string arg1, string arg2, string result) {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->result = result;
    }

    string toString() const {
        return "(" + op + ", " + arg1 + ", " + arg2 + ", " + result + ")";
    }
};

class Triple {
public:
    string op, arg1, arg2;

    Triple(string op, string arg1, string arg2) {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

    string toString() const {
        return "(" + op + ", " + arg1 + ", " + arg2 + ")";
    }
};

class IndirectTriple {
public:
    vector<int> pointers;
    vector<Triple> triples;

    IndirectTriple(vector<Triple> triples) {
        this->triples = triples;
        for (int i = 0; i < triples.size(); i++) {
            pointers.push_back(i);
        }
    }

    void print() {
        for (int i = 0; i < pointers.size(); i++) {
            cout << "Pointer " << i << " -> "
                 << triples[pointers[i]].toString() << endl;
        }
    }
};

int main() {
    vector<Quadruple> quads;
    quads.push_back(Quadruple("+", "a", "b", "t1"));
    quads.push_back(Quadruple("*", "t1", "c", "t2"));
    quads.push_back(Quadruple("-", "t2", "d", "t3"));

    cout << "Quadruples:\n";
    for (auto &q : quads) {
        cout << q.toString() << endl;
    }

    vector<Triple> triples;
    triples.push_back(Triple("+", "a", "b"));
    triples.push_back(Triple("*", "(0)", "c"));
    triples.push_back(Triple("-", "(1)", "d"));

    cout << "\nTriples:\n";
    for (int i = 0; i < triples.size(); i++) {
        cout << i << ": " << triples[i].toString() << endl;
    }

    IndirectTriple indirect(triples);

    cout << "\nIndirect Triples:\n";
    indirect.print();

    return 0;
}