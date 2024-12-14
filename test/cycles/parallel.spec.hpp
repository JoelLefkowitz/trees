#ifndef TREES_TEST_TREES_CYCLES_PARALLEL_SPEC_HPP
#define TREES_TEST_TREES_CYCLES_PARALLEL_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class ParallelTree : public TestTree {
  protected:
    Vertex a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
