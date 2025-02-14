#ifndef TREES_TEST_CYCLES_CYCLIC_SPEC_HPP
#define TREES_TEST_CYCLES_CYCLIC_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class CyclicTree : public TestTree {
  protected:
    Vertex<int> a, b, c, d, e, f;
    void SetUp() override;
};

#endif
