//
// Created by Ivan Samsonov on 2019-05-27.
//

#include <gtest/gtest.h>
#include "euclid.hpp"

TEST(Euclid, GCDWithZero) {
    EXPECT_EQ(gcd(0, 5), 5);
    EXPECT_EQ(gcd(5, 0), 5);
    EXPECT_EQ(gcd(0, 0), 0);
}

TEST(Euclid, GCDWithEqualValues) {
    EXPECT_EQ(gcd(1, 1), 1);
    EXPECT_EQ(gcd(16, 16), 16);
}

TEST(Euclid, GCDWithСoprimeNumbers) {
    EXPECT_EQ(gcd(997, 991), 1);
    EXPECT_EQ(gcd(13, 1000000007), 1);
}

TEST(Euclid, GCDWithCompositeNumber) {
    EXPECT_EQ(gcd(839*32416190071, 32416187567*839), 839);
    EXPECT_EQ(gcd(100, 15), 5);
}

TEST(Euclid, LCMWithZero) {
    EXPECT_EQ(lcm(0, 5), 0);
    EXPECT_EQ(lcm(5, 0), 0);
}

TEST(Euclid, LCMWithEqualValues) {
    EXPECT_EQ(lcm(1, 1), 1);
    EXPECT_EQ(lcm(16, 16), 16);
}

TEST(Euclid, LCMWithСoprimeNumbers) {
    EXPECT_EQ(lcm(997, 991), 997*991);
    EXPECT_EQ(lcm(13, 1000000007), 13*1000000007);
}

TEST(Euclid, LCMWithCompositeNumber) {
    EXPECT_EQ(lcm(839*179426081LL, 121084687LL*839), 18227904969460661833LL);
    EXPECT_EQ(lcm(839*121084687LL, 179426081LL*839), 18227904969460661833LL);
}
