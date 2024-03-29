#ifndef ex13_18_h
#define ex13_18_h

#include<string>

class Employee{
public:
    Employee();
    Employee(const std::string& name);

    const int id() const { return id_; }
private:
    std::string name_;
    int id_;
    static int s_increment;
};

#endif