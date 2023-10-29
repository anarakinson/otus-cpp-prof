#pragma once 


#include <document_manager.h>
#include <image_manager.h>

#include <iostream>
#include <memory>
#include <string>



// create and load documents
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

    void close_document() {
        if (m_current_document != nullptr) { delete m_current_document; }
    }


    void show_document() {
        if (m_current_document != nullptr) {
            m_current_document->show();
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }

    void add_shape(std::unique_ptr<iShape> &&shape) {
        if (m_current_document != nullptr) {
            m_current_document->add_shape(std::move(shape));
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }

    void erase(int index) {
        if (m_current_document != nullptr) {
            m_current_document->erase(index);
        } else {
            std::cout << "no documents are open" << std::endl;
        }
    }


    // Document *current_document() {
    //     if (m_current_document != nullptr) {
    //         return m_current_document;
    //     } 
    //     else {
    //         std::cout << "no documents are open" << std::endl;
    //         return nullptr;
    //     }
    // }


private:
    Document *m_current_document = nullptr;

};