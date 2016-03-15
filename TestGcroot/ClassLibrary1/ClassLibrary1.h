// ClassLibrary1.h

#pragma once

#include <gcroot.h>

using namespace System;

namespace ClassLibrary1 {

    ref class Something {
    public:
        Something() {
        }
        ~Something() {
            this->!Something();
        }
        !Something() {
        }
    };

    ref class SharedSomething {
    public:
        SharedSomething() {
        }
        ~SharedSomething() {   // Dispose()
            this->!SharedSomething();
        }
        !SharedSomething() {   // Finalize()
        }
        static Something^ Get() {
            return _something;
        }
    private:
        static Something^ _something = gcnew Something();
    };

    class Class2 {
    public:
        Class2() {
            _something = SharedSomething::Get();
        }
        ~Class2() {
            // _something is dead!!!
        }
    private:
        gcroot<Something^> _something;
    };

    public ref class Class1 {
    public:
        Class1() {
            _class2 = new Class2();
        }
        ~Class1() {
        }
        !Class1() {
            delete _class2;
        }
    private:
        Class2* _class2;
    };

}
