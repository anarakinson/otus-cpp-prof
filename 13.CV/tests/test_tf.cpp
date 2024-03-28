
#include <tf_classifier.hpp>
#include <utils.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <iostream>


using namespace mnist;

const size_t width = 28;
const size_t height = 28;
const size_t output_dim = 10;


TEST(TfClassifier, predict_class) {
    TfClassifier clf{"models/saved_model", width, height};

    auto features = TfClassifier::features_t{};

    std::ifstream test_data{"test_data/test_data_cnn.txt"};
    ASSERT_TRUE(test_data.is_open());
    for (;;) {
        if (!Utils::read_csv_line(test_data, features, ' ')) { break; }
    
        size_t y_true = features[0];
        features.erase(features.begin());

        auto y_pred = clf.predict(features);
        // std::cout << y_true << " == " << y_pred << "\n";
        ASSERT_EQ(y_true, y_pred);
    }
}




int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
