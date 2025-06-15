/*
 * @Author: Skye
 * @Date: 2020-07-03 20:00:54
 * @LastEditTime: 2021-07-15 17:19:52
 * @Description:
 * Skye:'Never stop!'
 */
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include <stdio.h>

#include "SingletonMode.h"
#include "TestClass.h"
#include "UndoStack.h"

void ThreadFoo()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetSingleton("Foo");
    std::cout << singleton->Value() << endl;
}

void ThreadBar()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetSingleton("Bar");
    std::cout << singleton->Value() << endl;
}

class My {
    void f(void);
    virtual void g(void);

    int x;
};

struct AA {
    char a;
    short b;
    void* c;
};

struct BB {
    char a;
    short b;
    void* c;
};

int main()
{
    // 单例在多线程程序中需要加锁
    //  std::thread t1(ThreadBar);
    //  std::thread t2(ThreadFoo);
    //  t1.join();
    //  t2.join();

    cout << ceil(1.3333) << endl;
    printf("%d,%d\n", sizeof(struct AA), sizeof(struct BB));
    cout << sizeof(My) << endl;

    std::shared_ptr<ProjectNode> node(new ProjectNode);
    UndoRedoStack stk;

    for (int i = 0; i < 10; ++i) {
        node->AddData("A");
        stk.ActionAddNode(node);
        std::cout << node->_data << endl;
    }
    for (int i = 0; i < 11; ++i) {
        stk.Undo();
        std::cout << node->_data << endl;
    }
    for (int i = 0; i < 10; ++i) {
        stk.Redo();
        std::cout << node->_data << endl;
    }
    system("pause");
    return 0;
}