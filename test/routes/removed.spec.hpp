#ifndef TREES_TEST_ROUTES_REMOVED_SPEC_HPP
#define TREES_TEST_ROUTES_REMOVED_SPEC_HPP

#include "../setup/suites.spec.hpp"
#include <gtest/gtest.h>

class RemovedTree : public TestTree {
  protected:
    Vertex a, b, c, d;
    void   SetUp() override;
};

#endif
