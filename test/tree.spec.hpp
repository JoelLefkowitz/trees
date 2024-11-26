#ifndef TREES_TREE_SPEC_HPP
#define TREES_TREE_SPEC_HPP

#include <cstddef>
#include <functional>
#include <gtest/gtest.h>
#include <map>
#include <memory>

// cppclean-disable-next-line
#include "../src/tree.hpp"

using namespace trees;

struct TestCase {
    Vertex node;
};

struct DFSTestCase : TestCase {
    Vertices expected = {};
};

struct BFSTestCase : TestCase {
    Vertices expected = {};
};

struct IndegreesTestCase : TestCase {
    Degrees expected = {};
};

struct OutdegreesTestCase : TestCase {
    Degrees expected = {};
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
