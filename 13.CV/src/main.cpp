
#include <classifier.h>
#include <tf_classifier.hpp>
#include <utils.hpp>

#include <tensorflow/c/c_api.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>



int main(int argc, char** argv) {

    //-------------------------------
    //--- Parse arguments ---//
    // default values for task model
    std::string model_path = "models/saved_model";
    std::string data_path = "test_data/test.csv";

    if (argc != 3) {
        std::cerr << "\n\t[!] USAGE: fashion_mnist <data_path> <model_path>\n";
        std::cerr << "\t[*] Trying to use default values...\n\n";
        // return 1;
    }
    if (argc == 3) {
        data_path = argv[1];
        model_path = argv[2];
    }

    //-------------------------------
    //--- Build model ---//
    // default values for task model
    const size_t width = 28;
    const size_t height = 28;
    const size_t output_dim = 10;

    mnist::TfClassifier classifier{model_path, width, height};

    //-------------------------------
    //--- Load data ---//
    std::ifstream test_data{data_path};
    if (!test_data.is_open()) {
        std::cerr << "[!] ERROR: Can't open file\n\n";
        return 1;
    }

    //-------------------------------
    //--- predict ---//
    std::cout << "[*] Wait...\n";
    auto features = mnist::TfClassifier::features_t{};
    size_t counter = 0;
    double result = 0;
    while (true) {
        
        if (!Utils::read_csv_line(test_data, features)) { break; }
    
        size_t true_val = features[0];
        features.erase(features.begin());

        auto pred_val = classifier.predict(features);

        counter++;
        if (true_val == pred_val) {
            result += 1;
        }
        
    }

    std::cout << "[+] Accuracy: " << result / double(counter) << std::endl;

    return 0;

}



//
// int main(int argc, char** argv) {

//     //-------------------------------
//     //--- Parse arguments ---//
//     std::string model_path = "models/saved_model";
//     std::string data_path = "test_data/test.csv";

//     if (argc != 3) {
//         std::cerr << "\n\t[!] USAGE: fashion_mnist <data_path> <model_path>\n";
//         std::cerr << "\t[*] Trying to use default values...\n\n";
//         // return 1;
//     }
//     if (argc == 3) {
//         data_path = argv[1];
//         model_path = argv[2];
//     }

//     //-------------------------------
//     //--- Build model ---//
//     // default values for task model
//     const size_t width = 28;
//     const size_t height = 28;
//     const size_t output_dim = 10;
//     mnist::TfClassifier classifier{model_path, width, height};

//     //-------------------------------
//     //--- Load data ---//
//     std::vector<mnist::TfClassifier::features_t> csv_content;
//     if (!Utils::read_csv(data_path, csv_content)) {
//         std::cerr << "[!] ERROR: Cant read csv";
//         return 1;
//     }
//     std::cout << "Test file size: " << csv_content.size() << std::endl;
    
//     //-------------------------------
//     //--- predict ---//    
//     std::cout << "[*] Wait...\n";
//     size_t counter = 0;
//     double result = 0;
//     for (const auto &row : csv_content) {
            
//         size_t true_val = row[0];
//         auto features = mnist::TfClassifier::features_t{row.begin() + 1, row.end()};

//         auto pred_val = classifier.predict(features);

//         counter++;
//         if (true_val == pred_val) {
//             result += 1;
//         }
        
//     }

    // std::cout << "[+] Accuracy: " << result / double(counter) << std::endl;

//     return 0;

// }
