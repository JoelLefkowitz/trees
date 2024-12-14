#ifndef TREES_TEST_CYCLES_LOOPS_SPEC_HPP
#define TREES_TEST_CYCLES_LOOPS_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class LoopsTree : public TestTree {
  protected:
    Vertex a, b, c, d, e, f;
    void   SetUp() override;
};

#endif
