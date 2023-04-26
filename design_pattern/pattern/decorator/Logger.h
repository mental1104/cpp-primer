#include <iostream>
#include <functional>
#include <utility>
#include <string>

using std::cout;
using std::endl;
using std::function;
using std::string;

struct Logger {
    function<void()> func;
    string name;

    Logger(const function<void()> &func, string name) : func{func}, name{std::move(name)} {}

    void operator()() const {
        cout << "Entering " << name << "\n";
        func();
        cout << "Exiting " << name << "\n";
    }
};

template<typename Func>
struct Logger2 {
    Func func;
    string name;

    Logger2(const Func &func, const string &name) : func{func}, name{name} {}

    void operator()() const {
        cout << "Entering " << name << "\n";
        func();
        cout << "Exiting " << name << "\n";
    }
};

template<typename Func>
auto make_logger2(Func func, const string &name) {
    return Logger2<Func>{func, name};
}

template<typename T>
struct Logger3{};

template<typename R, typename... Args>
struct Logger3<R(Args...)> {
    Logger3(function<R(Args...)> func, string name) : func{std::move(func)}, name{std::move(name)} {};

    R operator() (Args... args) {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << "\n";
        return result;
    }

    function<R(Args...)> func;
    string name;
};

template<typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string & name) {
    return Logger3<R(Args...)>(
            function<R(Args...)>(func), name);
}

