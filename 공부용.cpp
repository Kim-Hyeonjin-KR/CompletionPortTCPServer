#include <iostream>
using namespace std;

class AAA {
public:
    int a;
public:
    AAA() {
        a = 10;
        cout << "������AAA" << endl;
    }
    ~AAA() {
        cout << "�Ҹ���AAA" << endl;
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
        cout << "������BBB" << endl;
    }
    ~BBB() {
        cout << "�Ҹ���BBB" << endl;
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
        cout << "������CCC" << endl;
    }
    ~CCC() {
        cout << "�Ҹ���CCC" << endl;
    }
    void output() {
        cout << "c = " << c << endl;
    }
};