#pragma once

#include <iostream>
#include <memory>
#include <string>


// basic image class
class iShape {
public:
    virtual ~iShape() {}

    virtual std::string get_data() = 0;
    virtual void edit(const std::string &) = 0;

};


class Line : iShape {
public:
    std::string get_data() override {
        return m_data;
    }
    void edit(const std::string &data) override {
        m_data = data;
    }
private:
    std::string m_data = "Line";

};
