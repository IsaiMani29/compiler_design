compiler_design  
Compiler Design Programs in C++  
This repository contains C++ implementations of key compiler design concepts.  

📂 Topics Implemented  
Computation of LR(0)  
Elimination of Ambiguity  
Storage Allocation Strategies (Heap / Stack / Static)  
Directed Acyclic Graph (DAG) Construction  
Intermediate Code Generation – Quadruple, Triple, Indirect Triple  
Leading and Trailing Sets  
Left Recursion Removal and Left Factoring  
NFA to DFA Conversion  
Postfix and Prefix Intermediate Code Generation  
Predictive Parsing (LL(1) Parser)  
Regex to NFA Conversion  
Code Generation  
Code Optimization  
Single Responsibility Principle (SRP) Example  
Lexical Analyzer  
First and Follow Sets  
Parsing Table Construction  
Syntax Analysis  
Semantic Analysis  
Intermediate Code (General)  

🚀 How to Run  
All programs were compiled and executed using a C++ compiler (GCC / g++ / VS Code).  

📑 Inputs and Outputs  

Lexical Analyzer  
Input: if x = 5 + 3  

Output: Keyword: if Identifier: x Operator: = Number: 5 Operator: + Number: 3  

First and Follow Sets  
Input: S -> aB | b B -> c | dS  

Output: FIRST(S) = {a, b} FOLLOW(S) = {$} FIRST(B) = {c, d} FOLLOW(B) = {a, b}  

Left Recursion Removal  
Input: A -> A b | c  

Output: A -> c A' A' -> b A' | ε  

NFA to DFA Conversion  
Input: 2 a 1 -1 1 -1 0 1  

Output: DFA States: {q0, q1} Transitions: q0 --a--> q1 q1 --a--> q1 Final State: q1  

Parsing Table Construction  
Input: S -> aB | b B -> c | dS  

Output: M[S, a] = S -> aB M[S, b] = S -> b M[B, c] = B -> c M[B, d] = B -> dS  

Regex to NFA Conversion  
Input: a|b  

Output: States: {q0, q1, q2, q3} q0 --ε--> q1 q0 --ε--> q2 q1 --a--> q3 q2 --b--> q3 Final State: q3  

Intermediate Code Generation – Quadruple, Triple, Indirect Triple  
Input: (a+b)*c-d  

Output: Quadruples: (+, a, b, t1) (*, t1, c, t2) (-, t2, d, t3)  

Triples: 0: (+, a, b) 1: (*, (0), c) 2: (-, (1), d)  

Indirect Triples: Pointer 0 -> (+, a, b) Pointer 1 -> (*, (0), c) Pointer 2 -> (-, (1), d)  

Postfix and Prefix Intermediate Code  
Input: (a+b)*c-d  

Output: Postfix: ab+c*d- Prefix: - * +abc d  

Leading and Trailing Sets  
Input: Grammar with E -> T A  

Output: LEADING(E): {a, b, (} TRAILING(E): {a, b, )}  

Predictive Parsing (LL(1) Parser)  
Input: id + id * id $  

Output: Parsing successful  

DAG Construction  
Input: (a+b) - (a+b)  

Output: Node1: + Node2: a Node3: b Node4: - Reuse Node1 for both occurrences of (a+b)  

Code Generation  
Input: x = a + b * c  

Output: LOAD b MUL c ADD a STORE x  

Code Optimization  
Input: x = a * 2 + a * 2  

Output: Optimized: x = 2 * (a * 2)  

Single Responsibility Principle (SRP)  
Input: Student data  

Output: Student: Harshan, Grade: B  

Syntax Analysis  
Input: if (x+5) { y=3; }  

Output: Syntax tree constructed successfully  

Semantic Analysis  
Input: x = true + 5  

Output: Error: Type mismatch (boolean + int)  

LR(0) Computation  
Input: S -> E E -> E+T | T  

Output: I0: S -> .E I1: E -> .E+T | .T ...  

Elimination of Ambiguity  
Input: Grammar with dangling else  

Output: Ambiguity removed by associating ELSE with nearest IF  
