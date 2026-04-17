#include <bits/stdc++.h>
using namespace std;

// Class responsible only for handling student data
class Student {
private:
    string name;
    int marks;

public:
    Student(string name, int marks) {
        this->name = name;
        this->marks = marks;
    }

    string getName() const { return name; }
    int getMarks() const { return marks; }
};

// Class responsible only for calculating grades
class GradeCalculator {
public:
    string calculateGrade(const Student& student) {
        int marks = student.getMarks();

        if (marks >= 90) return "A";
        else if (marks >= 75) return "B";
        else if (marks >= 50) return "C";
        else return "D";
    }
};

// Class responsible only for displaying results
class ResultPrinter {
public:
    void printResult(const Student& student, const string& grade) {
        cout << "Student: " << student.getName()
             << ", Grade: " << grade << endl;
    }
};

int main() {
    Student s("Harshan", 85);
    GradeCalculator gc;
    ResultPrinter rp;

    string grade = gc.calculateGrade(s);
    rp.printResult(s, grade);

    return 0;
}