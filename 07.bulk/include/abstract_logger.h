#pragma once 

#include <string>
#include <vector>


class Bulk;

class Logger {
public:
    virtual ~Logger() = default;
    // print received lines (to output and to file) and clear inner vector 
    virtual void print_lines() = 0;

    void subscribe(Bulk *bulk) { m_owner = bulk; }

protected:
    Bulk *m_owner;
};
