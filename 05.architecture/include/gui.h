#pragma once 


#include <document_manager.h>
#include <image_manager.h>

#include <iostream>
#include <memory>
#include <string>



// class for work with documents
// can add shapes, save and load documents,
// show data of document
class GUI {
public:

    GUI() {
        std::cout << "show window" << std::endl;
    }
    ~GUI() {
        std::cout << "close window" << std::endl;
        close_document();
    }

    // create new document and work with it
    void new_document() {
        std::cout << "Create empty document" << std::endl;
        // std::unique_ptr<Document> doc{new Document{}};   // ???
        // m_current_document = doc.get();
        if (m_current_document != nullptr) {
            std::cout << "Close previous document!" << std::endl;
        }
        else {
            Document *doc = new Document{};
            m_current_document = doc;
        }
    }

    // load document and work with it
    void load_document(const char *path) {
        if (m_current_document != nullptr) {
            std::cout << "Close previous document!" << std::endl;
        }
        else {
            std::cout << "load from: " << path << std::endl;
            // loading ...
            Document *doc = new Document{};
            // loaded
            m_current_document = doc;
        }
    }

    // close current document
    void close_document() {
        if (m_current_document != nullptr) { delete m_current_document; }
        else {
            std::cout << "no documents are open" << std::endl;
        }
    }

    // save current document
    void save_document(const char *path) {
        if (m_current_document != nullptr) {
            m_current_document->save(path);
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }


    // show current document
    void show_document() {
        if (m_current_document != nullptr) {
            m_current_document->show();
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }

    // add shape to current document
    template <typename T>
    void add_shape(T &&shape) {
        if (m_current_document != nullptr) {
            auto unishape = std::make_unique<T>(shape);
            m_current_document->add_shape(std::move(unishape));
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }
    template <typename T>
    void add_shape(std::unique_ptr<T> &&shape) {
        if (m_current_document != nullptr) {
            m_current_document->add_shape(std::move(shape));
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }

    // erase shape from current document 
    void erase(int index) {
        if (m_current_document != nullptr) {
            m_current_document->erase(index);
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }


private:
    Document *m_current_document = nullptr;

};
