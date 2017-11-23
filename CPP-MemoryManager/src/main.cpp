#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include "MemMngr.h"

using namespace std;

class A {
public:
    A() { a = 1; }

    virtual   ~A() { ; } //cout << "~A()" << endl;}
    int a;
};

class B : public A {
public:
    B() { b = 2; }

    ~B() { ; } //cout << "~B()" << endl;}
    int b;
};

int main(void)
{
    int *pi1 = new int;
    int *pi2 = new int[100];
    char *pc1 = new char('a');
    char *pc2 = new char[100];
    A *pA1 = new A();
    A *pA2 = new A[100];
    B *pB1 = new B();
    B *pB2 = new B[100];
    string *pS1 = new string("a");
    string *pS2 = new string[100];
    vector<int> *pV1 = new vector<int>;
    vector<int> *pV2 = new vector<int>[100];
    delete pi1;
    delete[] pi2;
    delete pc1;
    delete[] pc2;
    delete pA1;
    delete[] pA2;
    delete pB1;
    delete[] pB2;
    delete pS1;
    delete[] pS2;
    delete pV1;
    delete[] pV2;
}
