#ifndef TESTCLASS_H
#define TESTCLASS_H

class A { };
class B : virtual public A { };
class C : virtual public A { };

class D : public B, public C { };

#endif