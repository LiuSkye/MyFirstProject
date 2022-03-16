/*
 * @Author: Skye
 * @Date: 2020-07-03 17:40:54
 * @LastEditTime: 2021-08-02 09:10:52
 * @Description: 单例
 * Skye:'Never stop!'
 */
#ifndef SINGLETON
#define SINGLETON

#include <string>

using namespace std;

class Singleton
{
private:
    Singleton(const string value) : value_(value) {}

    static Singleton *singleton_; //只是静态变量的声明
    string value_;

public:
    //Singleton shouldn't be cloneable.
    Singleton(Singleton &other) = delete;
    //Singleton shouldn't be assignable.
    Singleton& operator=(const Singleton &) = delete;

    //static methods should be defined outside the class
    static Singleton *GetSingleton(const string &value);

    inline void SomeBusinessLogic();

    string Value() const;
};

#endif