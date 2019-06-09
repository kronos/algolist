//
// Created by Ivan Samsonov on 2019-06-08.
//

#include <gtest/gtest.h>
#include "math/long.hpp"

const std::string big_positive_str = "123456789012345123456789012345";
const std::string big_negative_str = "-123452897543210987654321543210987654321";
const std::string small_negative_str = "-1234567890123451";
const std::string small_positive_str = "12345123456789";

class LongTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->big_positive = new Long(big_positive_str);
        this->big_negative = new Long(big_negative_str);
        this->small_negative = new Long(small_negative_str);
        this->small_positive = new Long(small_positive_str);
    }

    void TearDown() override {
        delete big_positive;
        delete big_negative;
        delete small_negative;
        delete small_positive;
    }

    Long* big_positive;
    Long* big_negative;
    Long* small_negative;
    Long* small_positive;
};

TEST_F(LongTest, ToStringWorks) {
    EXPECT_EQ(big_positive_str, big_positive->to_string());
    EXPECT_EQ(big_negative_str, big_negative->to_string());
    EXPECT_EQ(small_negative_str, small_negative->to_string());
    EXPECT_EQ(small_positive_str, small_positive->to_string());
}

TEST_F(LongTest, PlusEqualWorksWithSameSignNumbers) {
    Long t = *big_positive;
    t += *small_positive;
    EXPECT_EQ("123456789012345135801912469134", t.to_string());

    t = *big_negative;
    t += *small_negative;
    EXPECT_EQ("-123452897543210987654322777778877777772", t.to_string());
}

TEST_F(LongTest, PlusEqualWorksWithDifferentSignNumbers) {
    Long t = *big_positive + (-*big_positive);
    EXPECT_EQ("0", t.to_string());

    t = *small_negative + *small_positive;
    EXPECT_EQ("-1222222766666662", t.to_string());
    t = *small_positive + *small_negative;
    EXPECT_EQ("-1222222766666662", t.to_string());

    t = *big_positive + *small_negative;
    EXPECT_EQ("123456789012343888888898888894", t.to_string());
    t = *small_negative + *big_positive;
    EXPECT_EQ("123456789012343888888898888894", t.to_string());

    t = *small_positive + *big_negative;
    EXPECT_EQ("-123452897543210987654321530865864197532", t.to_string());
    t = *big_negative + *small_positive;
    EXPECT_EQ("-123452897543210987654321530865864197532", t.to_string());

    t = *big_positive + *big_negative;
    EXPECT_EQ("-123452897419754198641976419754198641976", t.to_string());
    t = *big_negative + *big_positive;
    EXPECT_EQ("-123452897419754198641976419754198641976", t.to_string());
}

TEST(Long, Constructors) {
    EXPECT_EQ("0", Long().to_string());
    EXPECT_EQ("123", Long(123).to_string());
    EXPECT_EQ("-421", Long(Long(-421)).to_string());
    EXPECT_EQ("-1152921504606846976", Long(-1152921504606846976LL).to_string());
}

TEST(Long, Minus) {
    EXPECT_EQ("99999999999999999999999999", (Long("100000000000000000000000000") - Long(1)).to_string());
    EXPECT_EQ("1", (Long("100000000000000000000000000") - Long("99999999999999999999999999")).to_string());
    EXPECT_EQ("-1", (Long("99999999999999999999999999") - Long("100000000000000000000000000")).to_string());
}

TEST(Long, Plus) {
    EXPECT_EQ("1000000000000000000000000000", (Long("999999999999999999999999999") + Long(1)).to_string());
    EXPECT_EQ("999999999999999999999999999", (Long("1000000000000000000000000000") + Long(-1)).to_string());
    EXPECT_EQ("1", (Long("1000000000000000000000000000") + Long("-999999999999999999999999999")).to_string());
    EXPECT_EQ("-1", (Long("999999999999999999999999999") + Long("-1000000000000000000000000000")).to_string());
    EXPECT_EQ("1", (Long("-999999999999999999999999999") + Long("1000000000000000000000000000")).to_string());
    EXPECT_EQ("-1", (Long("-1000000000000000000000000000") + Long("999999999999999999999999999")).to_string());
}
