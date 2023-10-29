#pragma once

#include <image_manager.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>



// contains some data
class Document {
public:
    Document() = default;

    // get data from document
    std::vector<std::unique_ptr<iShape>> &get_data() { return m_data; }
    void add_shape(std::unique_ptr<iShape> &&shape) noexcept {
        m_data.emplace_back(std::move(shape));
    }

    void show() {
        for (auto &x : m_data) {
            std::cout << x->get_data() << " ";
        }
        std::cout << std::endl;
    }

    void erase(int index) {
        m_data.erase(m_data.begin() + index);
    }

    void save(const char *path) {
        std::cout << "Save to: " << path << std::endl;
    }

private:
    std::vector<std::unique_ptr<iShape>> m_data{};

};


