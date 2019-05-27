//
// Created by Ivan Samsonov on 2019-05-27.
//

#include <gtest/gtest.h>
#include "disjoint_set.hpp"
#include "common.hpp"

const size_t disjointSetSize = 5;

class DisjointSetTest : public ::testing::Test {
protected:
    void SetUp() override {
        set0_ = new DisjointSet<int>(disjointSetSize);

        for (size_t idx = 0; idx < set0_->size(); idx++) {
            set0_->init(idx);
        }
    }

    void TearDown() override {
        delete set0_;
    }

    DisjointSet<int>* set0_;
};

TEST_F(DisjointSetTest, SizeWorks) {
    EXPECT_EQ(set0_->size(), disjointSetSize);
}

TEST_F(DisjointSetTest, ParentWorks) {
    EXPECT_EQ(set0_->parent(0), set0_->parent(0));
    EXPECT_NE(set0_->parent(0), set0_->parent(disjointSetSize-1));
}

TEST_F(DisjointSetTest, UniteWorks) {
    ASSERT_NE(set0_->parent(0), set0_->parent(disjointSetSize-1));
    set0_->unite(0, disjointSetSize-1);
    EXPECT_EQ(set0_->parent(0), set0_->parent(disjointSetSize-1));
}
