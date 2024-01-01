// xcrun make test

#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <thread>
#include <future>
#include <unistd.h>

#include <iostream>
//#include <numeric>
//#include <chrono>
//#include <algorithm>
//#include <functional>


using namespace std;
using std::unique_ptr;
int main(void)
{
    cout << "Main \n";
    int* a = NULL;
    int*b = a;
    int c = 112;
    a = &c;
    cout<<"a ="<<*a<<endl;
    cout<<"b ="<<*b<<endl;
    return 1;
}
