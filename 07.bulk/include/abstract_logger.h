#pragma once 

#include <string>
#include <vector>


class Bulk;

class iLogger {
public:
    virtual ~iLogger() = default;
    // print received lines (to output or to file)
    virtual void print_lines() = 0;
    // attach logger to some bulk exemplar
    void subscribe(Bulk *bulk) { m_owner = bulk; }

protected:
    Bulk *m_owner;
};
