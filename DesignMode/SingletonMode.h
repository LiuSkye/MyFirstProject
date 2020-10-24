#ifndef SINGLETON
#define SINGLETON

#include <string>

using namespace std;

class Singleton
{
private:
	Singleton(const string value):value_(value){}

	static Singleton* singleton_;   //只是静态变量的声明
	string value_;
	

public:
	//Singleton shouldn't be cloneable.
	Singleton(Singleton& other) = delete;
	//Singleton shouldn't be assignable.
	void operator=(const Singleton&) = delete;

	//static methods should be defined outside the class
	static Singleton* GetSingleton(const string& value);

	inline void SomeBusinessLogic();

	string Value() const;
};

#endif