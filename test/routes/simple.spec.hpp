#ifndef TREES_ROUTES_SIMPLE_SPEC_HPP
#define TREES_ROUTES_SIMPLE_SPEC_HPP

#include "../tree.spec.hpp"
#include <gtest/gtest.h>

class SimpleTree : public TestTree {
  protected:
    Vertex a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
