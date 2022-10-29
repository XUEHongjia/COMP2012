#include <iostream>
using namespace std;
#define PI 3.1415926
class A
{
    public:
    void print() const { cout << " A's print " << endl; }
};

class B : public A
{
    public:
    virtual void print() const { cout << " B's print " << endl; }
};

class C : public B
{
    public:
    void print() const { cout << " C's print " << endl; }
};

static int x = 5;

int f() { return ++x; }

int main()
{
    cout << x << endl;
    cout << f() << endl;
    cout << f() << endl;
    C c;
    A& a = c;
    a.print();
    int x = 20;
    int y = 30;
    []( const int x, const int y ){ int c = x > y? x : y; cout << c << endl; }( x , y );
    int* p = new int[5];
    p[1] = 2;
    cout << p[1] << endl;
    delete[] p;
    return 0;
}