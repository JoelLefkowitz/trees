#include "loops.spec.hpp"
#include "../tree.spec.hpp"
#include <functional/generics/functor/foreach.tpp>
#include <functional>
#include <gtest/gtest.h>
#include <memory>

// a(1)
//  ↓
// b(2) ↺
//  ↓
// c(3)
void LoopsTree::SetUp() {
    a = std::make_shared<Tree>();
    b = std::make_shared<Tree>();
    c = std::make_shared<Tree>();

    a->add_child(b);
    b->add_child(b);
    b->add_child(c);
}

TEST_F(LoopsTree, DFS) {
    dfs({
        {a, {a, b, c}},

        {b, {b, c}   },
        {c, {c}      }
    });
}

TEST_F(LoopsTree, BFS) {
    bfs({
        {a, {a, b, c}},
        {b, {b, c}   },
        {c, {c}      }
    });
}

TEST_F(LoopsTree, Indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 2}, {c, 1}}},
        {b, {{b, 1}, {c, 1}}        },
        {c, {{c, 0}}                },
    });
}

TEST_F(LoopsTree, Outdegrees) {
    outdegrees({
        {a, {{a, 1}, {b, 2}, {c, 0}}},
        {b, {{b, 2}, {c, 0}}        },
        {c, {{c, 0}}                },
    });
}

TEST_F(LoopsTree, Size) {
    size({
        {a, 3},
        {b, 2},
        {c, 1}
    });
}

TEST_F(LoopsTree, SelfLoops) {
    self_loops({
        {a, true },
        {b, true },
        {c, false}
    });
}

TEST_F(LoopsTree, ParallelLinks) {
    parallel_links({
        {a, false},
        {b, false},
        {c, false}
    });
}

TEST_F(LoopsTree, Cyclic) {
    cyclic({
        {a, true },
        {b, true },
        {c, false}
    });
}
