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

    void show_data() {
        for (auto &x : m_data) {
            std::cout << x->get_data() << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::unique_ptr<iShape>> m_data{};

};


// create and load documents
class DocumentManager {
public:
    static Document new_document() {
        std::cout << "Create empty document" << std::endl;
        return Document{};
    }

    static Document load_document(const char *path) {
        std::cout << "load from: " << path << std::endl;
        // loading ...
        Document doc{};
        // loaded
        return doc;
    }

};