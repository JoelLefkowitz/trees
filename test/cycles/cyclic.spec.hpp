#ifndef TREES_CYCLES_CYCLIC_SPEC_HPP
#define TREES_CYCLES_CYCLIC_SPEC_HPP

#include "../tree.spec.hpp"
#include <gtest/gtest.h>

class CyclicTree : public TestTree {
  protected:
    Vertex a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
