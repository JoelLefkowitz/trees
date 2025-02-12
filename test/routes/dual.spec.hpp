#ifndef TREES_TEST_TREES_ROUTES_DUAL_SPEC_HPP
#define TREES_TEST_TREES_ROUTES_DUAL_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class DualTree : public TestTree {
  protected:
    Vertex<int> a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
