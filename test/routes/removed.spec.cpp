#include "removed.spec.hpp"
#include "../tree.spec.hpp"
#include <functional/generics/functor/foreach.tpp>
#include <functional>
#include <gtest/gtest.h>
#include <memory>

//      a(1)
//       ↓
//      b(2)
//    ↙     ↖︎
// c(✖)  →  d(4)
void RemovedTree::SetUp() {
    a = std::make_shared<Tree>();
    b = std::make_shared<Tree>();
    c = std::make_shared<Tree>();
    d = std::make_shared<Tree>();

    a->add_child(b);
    b->add_child(c);
    c->add_child(d);
    d->add_child(b);

    c->removed = true;
}

TEST_F(RemovedTree, DFS) {
    dfs({
        {a, {a, b}},
        {b, {b}   },
        {c, {}    },
        {d, {d, b}}
    });
}

TEST_F(RemovedTree, BFS) {
    bfs({
        {a, {a, b}},
        {b, {b}   },
        {c, {}    },
        {d, {d, b}}
    });
}

TEST_F(RemovedTree, Indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 1}}},
        {b, {{b, 0}}        },
        {c, {}              },
        {d, {{d, 0}, {b, 1}}}
    });
}

TEST_F(RemovedTree, Outdegrees) {
    outdegrees({
        {a, {{a, 1}, {b, 0}}},
        {b, {{b, 0}}        },
        {c, {}              },
        {d, {{d, 1}, {b, 0}}}
    });
}

TEST_F(RemovedTree, Size) {
    size({
        {a, 2},
        {b, 1},
        {c, 0},
        {d, 2}
    });
}

TEST_F(RemovedTree, SelfLoops) {
    self_loops({
        {a, false},
        {b, false},
        {c, false},
        {d, false}
    });
}

TEST_F(RemovedTree, ParallelLinks) {
    parallel_links({
        {a, false},
        {b, false},
        {c, false},
        {d, false}
    });
}

TEST_F(RemovedTree, Cyclic) {
    cyclic({
        {a, false},
        {b, false},
        {c, false},
        {d, false}
    });
}
