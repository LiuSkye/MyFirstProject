#ifndef TEST_H
#define TEST_H

#include <iostream>
using namespace std;

//Alias Template 与 Template Template parameter
template <typename T>
using Vec = vector<T, allocator<T>>; //模板别名。无法用typedef(因为typedef不接受参数)或#define代替

template <typename T, template <typename U> class Container>
class XCIs
{
private:
    Container<T> c;
};

#endif