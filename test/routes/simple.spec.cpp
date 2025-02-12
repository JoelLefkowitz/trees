#include "simple.spec.hpp"
#include "../setup/suites.spec.hpp"
#include <functional/generics/functor/foreach.tpp>
#include <functional>
#include <gtest/gtest.h>
#include <memory>

//      a(1)
//    ↙      ↘︎
// b(2)       d(4)
//  ↓        ↙    ↘
// c(3)   e(5)    f(6)
void SimpleTree::SetUp() {
    a = std::make_shared<Tree<int>>(1);
    b = std::make_shared<Tree<int>>(2);
    c = std::make_shared<Tree<int>>(3);
    d = std::make_shared<Tree<int>>(4);
    e = std::make_shared<Tree<int>>(5);
    f = std::make_shared<Tree<int>>(6);

    a->add_child(b);
    b->add_child(c);
    a->add_child(d);
    d->add_child(e);
    d->add_child(f);
}

TEST_F(SimpleTree, DFS) {
    dfs({
        {a, {a, b, c, d, e, f}},
        {b, {b, c}            },
        {c, {c}               },
        {d, {d, e, f}         },
        {e, {e}               },
        {f, {f}               },
    });
}

TEST_F(SimpleTree, BFS) {
    bfs({
        {a, {a, b, d, c, e, f}},
        {b, {b, c}            },
        {c, {c}               },
        {d, {d, e, f}         },
        {e, {e}               },
        {f, {f}               },
    });
}

TEST_F(SimpleTree, indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}}},
        {b, {{b, 0}, {c, 1}}                                },
        {c, {{c, 0}}                                        },
        {d, {{d, 0}, {e, 1}, {f, 1}}                        },
        {e, {{e, 0}}                                        },
        {f, {{f, 0}}                                        }
    });
}

TEST_F(SimpleTree, Outdegrees) {
    outdegrees({
        {a, {{a, 2}, {b, 1}, {c, 0}, {d, 2}, {e, 0}, {f, 0}}},
        {b, {{b, 1}, {c, 0}}                                },
        {c, {{c, 0}}                                        },
        {d, {{d, 2}, {e, 0}, {f, 0}}                        },
        {e, {{e, 0}}                                        },
        {f, {{f, 0}}                                        }
    });
}

TEST_F(SimpleTree, Size) {
    size({
        {a, 6},
        {b, 2},
        {c, 1},
        {d, 3},
        {e, 1},
        {f, 1}
    });
}

TEST_F(SimpleTree, SelfLoops) {
    self_loops({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(SimpleTree, ParallelLinks) {
    parallel_links({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(SimpleTree, Cyclic) {
    cyclic({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}
