#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>


namespace Utils {

    inline bool read_csv_line(std::istream& stream, mnist::Classifier::features_t& features, char sep = ',') {
        std::string line;
        std::getline(stream, line);

        features.clear();
        std::istringstream linestream{line};
        std::string value;
        while (std::getline(linestream, value, sep)) {
            features.push_back(std::stof(value));
        }
        return stream.good();
    }


    inline bool read_csv(const std::string &name, std::vector<mnist::TfClassifier::features_t> &csv_content) {
        std::ifstream test_data{name};
        
        if (!test_data.is_open()) {
            std::cerr << "[!] ERROR: Can't open file\n\n";
            return false;
        }

        auto features = mnist::TfClassifier::features_t{};

        while (true) {
            if (!read_csv_line(test_data, features)) { break; }
            csv_content.push_back(features);
        }

        return true;

    }

} // namespace Utils

