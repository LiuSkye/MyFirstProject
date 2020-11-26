#ifndef TEST_H
#define TEST_H

#include <iostream>
using namespace std;

void f(int i)
{
    cout<<"void f(int i)"<<endl;
}

void f(void *p)
{
    cout<<"void f(void *p)"<<endl;
}

template<typename T>
using Vec=vector<T,allocator<T>>;

template<typename T,template<typename U> class Container>
class XCIs{
private:
    Container<T> c;
};




#endif