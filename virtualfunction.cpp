#include <iostream>

using namespace std;

struct Base;
struct Vtable;

using SpeakFn = void(Base::*)();

struct Vtable{
    SpeakFn speak;
};

struct Base{
    Vtable* __vptr;
    void speak(){
        (this->*(__vptr->speak))();
    }
    void Basespeak(){
        cout << "Base Speaking"  << endl;
    }
};

struct Derived : public Base{
    void DerivedSpeak(){
        cout << "Derived Speaking" << endl;
    }
};

Vtable BaseVtable = { &Base::Basespeak };

Vtable DerivedVtable = { static_cast<SpeakFn>(&Derived::DerivedSpeak) };

int main(){
    Base b;
    Derived d;

    d.__vptr = &DerivedVtable;
    b.__vptr = &BaseVtable;

    b.speak();
    d.speak();

};

