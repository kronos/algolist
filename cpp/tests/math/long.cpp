//
// Created by Ivan Samsonov on 2019-06-08.
//

#include <gtest/gtest.h>
#include "math/long.hpp"

const std::string big_positive = "123456789012345123456789012345";
const std::string big_negative = "-123456789012345123456789012345";
const std::string small_negative = "-45123456789012345";
const std::string small_positive = "45123456789012345";

class LongTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->long0_ = new Long(big_positive);
        this->long1_ = new Long(big_negative);
        this->long2_ = new Long(small_negative);
        this->long3_ = new Long(small_positive);
    }

    void TearDown() override {
        delete long0_;
        delete long1_;
        delete long2_;
        delete long3_;
    }

    Long* long0_;
    Long* long1_;
    Long* long2_;
    Long* long3_;
};

TEST_F(LongTest, ToStringWorks) {
    EXPECT_EQ(big_positive, long0_->to_string());
    EXPECT_EQ(big_negative, long1_->to_string());
    EXPECT_EQ(small_negative, long2_->to_string());
    EXPECT_EQ(small_positive, long3_->to_string());
}

TEST_F(LongTest, PlusEqualWorksWithSameSignNumbers) {
    Long t = big_positive;
    t += small_positive;
    EXPECT_EQ("123456789012390246913578024690", t.to_string());

    t = big_negative;
    t += small_negative;
    EXPECT_EQ("-123456789012390246913578024690", t.to_string());
}

TEST_F(LongTest, PlusEqualWorksWithDifferentSignNumbers) {
    Long t = big_positive;
    t += big_negative;
    EXPECT_EQ("0", t.to_string());

    t = small_negative;
    t += small_positive;
    EXPECT_EQ("0", t.to_string());

    t = big_positive;
    t += small_negative;
    EXPECT_EQ("123456789012300000000000000000", t.to_string());

    t = small_positive;
    t += big_negative;
    EXPECT_EQ("-123456789012300000000000000000", t.to_string());
}
