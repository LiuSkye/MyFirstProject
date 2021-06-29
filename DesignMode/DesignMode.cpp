#include <vector>
#include <iostream>
#include <thread>
#include <cmath>

#include <stdio.h>
 
#include "TestClass.h"
#include "SingletonMode.h"

void ThreadFoo() 
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetSingleton("Foo");
	std::cout << singleton->Value() << endl;
}

void ThreadBar() 
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetSingleton("Bar");
	std::cout << singleton->Value() << endl;
}

class My
{
	void f(void);
	virtual void g(void);

	int x;
};

struct AA{
	char a;
	short b;
	void *c;
};

struct BB{
	char a;
	short b;
	void *c;
};


int main()
{
	//单例在多线程程序中需要加锁
	// std::thread t1(ThreadBar);
	// std::thread t2(ThreadFoo);
	// t1.join();
	// t2.join();

	cout <<ceil(1.3333)<<endl;
	printf("%d,%d\n",sizeof(struct AA),sizeof(struct BB));
	cout <<sizeof(My)<<endl;

	
	system("pause");
	return 0;
}