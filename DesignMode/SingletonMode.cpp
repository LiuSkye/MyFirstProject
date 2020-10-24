
#include <vector>
#include <iostream>
#include <thread>

#include "SingletonMode.h"

Singleton* Singleton::singleton_ = nullptr;  //这才是静态变量的定义

//static methods should be defined outside the class
Singleton* Singleton::GetSingleton(const string& value)
{
	if (singleton_ == nullptr) {
		singleton_ = new Singleton(value);
	}
	return singleton_;
}

void Singleton::SomeBusinessLogic() {
	//nothing to do...
}

string Singleton::Value() const
{
	return value_;
}


