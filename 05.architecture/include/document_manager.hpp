#pragma once

#include <image_manager.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>



// class document. contains data, i.e. shapes
class Document {
public:
    Document() = default;

    // get data from document
    std::vector<std::unique_ptr<iShape>> &get_data() { return m_data; }

    // add shape to document
    void add_shape(std::unique_ptr<iShape> &&shape) noexcept {
        m_data.emplace_back(std::move(shape));
    }

    // show what's within document
    void show() {
        for (auto &x : m_data) {
            std::cout << x->get_data() << " ";
        }
        std::cout << std::endl;
    }

    // erase shape from document by index
    void erase(int index) {
        m_data.erase(m_data.begin() + index);
    }

    // save document to file
    void save(const char *path) {
        std::cout << "Save to: " << path << std::endl;
    }

private:
    std::vector<std::unique_ptr<iShape>> m_data{};

};


