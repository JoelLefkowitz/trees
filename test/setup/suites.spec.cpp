#include "suites.spec.hpp"
#include <cstddef>
#include <functional/generics/functor/foreach.tpp>
#include <functional>
#include <gtest/gtest.h>
#include <memory>

void TestTree::TearDown() {}

void dfs(const std::vector<DFSTestCase> &cases) {
    functional::foreach (
        std::function<void(const DFSTestCase &)>([](const auto &test) { EXPECT_EQ(test.node->dfs(), test.expected); }),
        cases
    );
}

void bfs(const std::vector<BFSTestCase> &cases) {
    functional::foreach (
        std::function<void(const BFSTestCase &)>([](const auto &test) { EXPECT_EQ(test.node->bfs(), test.expected); }),
        cases
    );
}

void indegrees(const std::vector<IndegreesTestCase> &cases) {
    functional::foreach (
        std::function<void(const IndegreesTestCase &)>([](const auto &test) {
            EXPECT_EQ(test.node->indegrees(), test.expected);
        }),
        cases
    );
}

void outdegrees(const std::vector<OutdegreesTestCase> &cases) {
    functional::foreach (
        std::function<void(const OutdegreesTestCase &)>([](const auto &test) {
            EXPECT_EQ(test.node->outdegrees(), test.expected);
        }),
        cases
    );
}

void size(const std::vector<SizeTestCase> &cases) {
    functional::foreach (
        std::function<void(const SizeTestCase &)>([](const auto &test) { EXPECT_EQ(test.node->size(), test.expected); }
        ),
        cases
    );
}

void self_loops(const std::vector<SelfLoopsTestCase> &cases) {
    functional::foreach (
        std::function<void(const SelfLoopsTestCase &)>([](const auto &test) {
            EXPECT_EQ(test.node->self_loops(), test.expected);
        }),
        cases
    );
}

void parallel_links(const std::vector<ParallelLinksTestCase> &cases) {
    functional::foreach (
        std::function<void(const ParallelLinksTestCase &)>([](const auto &test) {
            EXPECT_EQ(test.node->parallel_links(), test.expected);
        }),
        cases
    );
}

void cyclic(const std::vector<CyclicTestCase> &cases) {
    functional::foreach (
        std::function<void(const CyclicTestCase &)>([](const auto &test) {
            EXPECT_EQ(test.node->cyclic(), test.expected);
        }),
        cases
    );
}
