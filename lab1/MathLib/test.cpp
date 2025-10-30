#include <iostream>
using namespace std;
class samp {
    int i;
    public:
    samp(int num) { i = num; }
    int get_i() { return i; }
    void set_i(int num) { i = num; }
    friend int multy(samp o1, samp o2);
    friend int sqr_i(samp o);
};
int sqr_i(samp o) {
    o.i = 99;
    cout << o.i << endl;
    return o.i*o.i;
};

int multy(samp o1, samp o2) {
    return o1.i * o2.i;
};

int main() {
    samp a(10);
    cout << a.get_i() << endl;
    cout << sqr_i(a) << endl;
    cout << a.get_i() << endl;
    samp b(5);
    cout << multy(a, b) << endl;
    return 0;
}
