#ifndef TREES_TEST_SETUP_SUITES_SPEC_HPP
#define TREES_TEST_SETUP_SUITES_SPEC_HPP

#include <cstddef>
#include <functional>
#include <gtest/gtest.h>
#include <map>
#include <memory>

// cppclean-disable-next-line
#include "../../src/tree.tpp"

using namespace trees;

struct TestCase {
    Vertex<int> node;
};

struct DFSTestCase : TestCase {
    Vertices<int> expected = {};
};

struct BFSTestCase : TestCase {
    Vertices<int> expected = {};
};

struct IndegreesTestCase : TestCase {
    Degrees<int> expected = {};
};

struct OutdegreesTestCase : TestCase {
    Degrees<int> expected = {};
};

struct SizeTestCase : TestCase {
    size_t expected = 0;
};

struct SelfLoopsTestCase : TestCase {
    bool expected = false;
};

struct ParallelLinksTestCase : TestCase {
    bool expected = false;
};

struct CyclicTestCase : TestCase {
    bool expected = false;
};

class TestTree : public testing::Test {
  protected:
    void TearDown() override;
};

void dfs(const std::vector<DFSTestCase> &cases);

void bfs(const std::vector<BFSTestCase> &cases);

void indegrees(const std::vector<IndegreesTestCase> &cases);

void outdegrees(const std::vector<OutdegreesTestCase> &cases);

void size(const std::vector<SizeTestCase> &cases);

void self_loops(const std::vector<SelfLoopsTestCase> &cases);

void parallel_links(const std::vector<ParallelLinksTestCase> &cases);

void cyclic(const std::vector<CyclicTestCase> &cases);

#endif
