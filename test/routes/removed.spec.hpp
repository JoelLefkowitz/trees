#ifndef TREES_ROUTES_REMOVED_SPEC_HPP
#define TREES_ROUTES_REMOVED_SPEC_HPP

#include "../tree.spec.hpp"
#include <gtest/gtest.h>

class RemovedTree : public TestTree {
  protected:
    Vertex a, b, c, d;
    void   SetUp() override;
};

#endif
