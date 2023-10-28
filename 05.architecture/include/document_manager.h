#pragma once

#include <document.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>



// contains some data
class Document {
public:
    Document() = default;
    Document(const std::string &data) : m_data{data} {}

    // get metadata from document
    std::string get_metadata() { return m_metadata; }

    // get data from document
    std::string get_data() { return m_data; }

    // document editing
    void edit(std::string data) { m_metadata = data; }

private:
    std::string m_metadata = std::string("Document data");
    std::vector<IShape> m_data{};

};


// create and load documents
class DocumentManager {
public:
    static std::unique_ptr<Document> new_document() {
        std::cout << "Create empty document" << std::endl;
        return std::unique_ptr<Document>{new Document{}};
    }

    static std::unique_ptr<Document> new_document(const std::string &data) {
        std::cout << "Create document with data" << std::endl;
        return std::unique_ptr<Document>{new Document{data}};
    }

    static std::unique_ptr<Document> load_document(const char *path) {
        std::cout << "load from: " << path << std::endl;
        // loading ...
        std::unique_ptr<Document> doc{new Document{"Some data created earlier..."}};
        return doc;
    }

};