#ifndef TREES_ROUTES_DUAL_SPEC_HPP
#define TREES_ROUTES_DUAL_SPEC_HPP

#include "tree.spec.hpp"
#include <gtest/gtest.h>

class DualTree : public TestTree {
  protected:
    Vertex a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
