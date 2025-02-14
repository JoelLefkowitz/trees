#ifndef TREES_TEST_ROUTES_SIMPLE_SPEC_HPP
#define TREES_TEST_ROUTES_SIMPLE_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class SimpleTree : public TestTree {
  protected:
    Vertex<int> a, b, c, d, e, f;
    void SetUp() override;
};

#endif
