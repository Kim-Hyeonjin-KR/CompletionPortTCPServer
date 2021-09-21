#include <iostream>
using namespace std;

class AAA {
public:
    int a;
public:
    AAA() {
        a = 10;
        cout << "持失切AAA" << endl;
    }
    ~AAA() {
        cout << "社瑚切AAA" << endl;
    }
    void output() {
        cout << "a = " << a << endl;
    }
};

class BBB : public AAA {
public:
    int b;
public:
    BBB() {
        b = 20;
        cout << "持失切BBB" << endl;
    }
    ~BBB() {
        cout << "社瑚切BBB" << endl;
    }
    void output() {
        cout << "b = " << b << endl;
    }
};
class CCC : public AAA, public BBB {
public:
    int c;
public:
    CCC() {
        c = 30;
        cout << "持失切CCC" << endl;
    }
    ~CCC() {
        cout << "社瑚切CCC" << endl;
    }
    void output() {
        cout << "c = " << c << endl;
    }
};