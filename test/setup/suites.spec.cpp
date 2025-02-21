#include "suites.spec.hpp"
#include <cstddef>
#include <funky/generics/iterables.tpp>
#include <gtest/gtest.h>
#include <memory>

void TestTree::TearDown() {
}

void dfs(const std::vector<DFSTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->dfs(), test.expected);
        },
        cases
    );
}

void bfs(const std::vector<BFSTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->bfs(), test.expected);
        },
        cases
    );
}

void indegrees(const std::vector<IndegreesTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->indegrees(), test.expected);
        },
        cases
    );
}

void outdegrees(const std::vector<OutdegreesTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->outdegrees(), test.expected);
        },
        cases
    );
}

void size(const std::vector<SizeTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->size(), test.expected);
        },
        cases
    );
}

void self_loops(const std::vector<SelfLoopsTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->self_loops(), test.expected);
        },
        cases
    );
}

void parallel_links(const std::vector<ParallelLinksTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->parallel_links(), test.expected);
        },
        cases
    );
}

void cyclic(const std::vector<CyclicTestCase> &cases) {
    funky::foreach (
        [](const auto &test) {
            EXPECT_EQ(test.node->cyclic(), test.expected);
        },
        cases
    );
}
