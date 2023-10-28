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
    void add_shape(std::unique_ptr<iShape> &&shape) {
        m_data.emplace_back(std::move(shape));
    }

private:
    std::vector<std::unique_ptr<iShape>> m_data{};

};


// create and load documents
class DocumentManager {
public:
    static std::unique_ptr<Document> new_document() {
        std::cout << "Create empty document" << std::endl;
        return std::unique_ptr<Document>{new Document{}};
    }

    static std::unique_ptr<Document> load_document(const char *path) {
        std::cout << "load from: " << path << std::endl;
        // loading ...
        std::unique_ptr<Document> doc{new Document{}};
        return doc;
    }

};