#include "dual.spec.hpp"
#include "../../functional/generics/functor/foreach.tpp"
#include "tree.spec.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <memory>

//     a(1)
//      ↓
//     b(2)
//    ↙    ↘
// c(3)    f(6)
//    ↘    ↙
//     d(4)
//      ↓
//     e(5)
void DualTree::SetUp() {
    a = std::make_shared<Tree>();
    b = std::make_shared<Tree>();
    c = std::make_shared<Tree>();
    d = std::make_shared<Tree>();
    e = std::make_shared<Tree>();
    f = std::make_shared<Tree>();

    a->add_child(b);
    b->add_child(c);
    c->add_child(d);
    d->add_child(e);
    b->add_child(f);
    f->add_child(d);
}

TEST_F(DualTree, DFS) {
    dfs({
        {a, {a, b, c, d, e, f}},
        {b, {b, c, d, e, f}   },
        {c, {c, d, e}         },
        {d, {d, e}            },
        {e, {e}               },
        {f, {f, d, e}         }
    });
}

TEST_F(DualTree, BFS) {
    bfs({
        {a, {a, b, c, f, d, e}},
        {b, {b, c, f, d, e}   },
        {c, {c, d, e}         },
        {d, {d, e}            },
        {e, {e}               },
        {f, {f, d, e}         }
    });
}

TEST_F(DualTree, Indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 1}, {c, 1}, {d, 2}, {e, 1}, {f, 1}}},
        {b, {{b, 0}, {c, 1}, {d, 2}, {e, 1}, {f, 1}}        },
        {c, {{c, 0}, {d, 1}, {e, 1}}                        },
        {d, {{d, 0}, {e, 1}}                                },
        {e, {{e, 0}}                                        },
        {f, {{f, 0}, {d, 1}, {e, 1}}                        }
    });
}

TEST_F(DualTree, Outdegrees) {
    outdegrees({
        {a, {{a, 1}, {b, 2}, {c, 1}, {d, 1}, {e, 0}, {f, 1}}},
        {b, {{b, 2}, {c, 1}, {d, 1}, {e, 0}, {f, 1}}        },
        {c, {{c, 1}, {d, 1}, {e, 0}}                        },
        {d, {{d, 1}, {e, 0}}                                },
        {e, {{e, 0}}                                        },
        {f, {{f, 1}, {d, 1}, {e, 0}}                        }
    });
}

TEST_F(DualTree, Size) {
    size({
        {a, 6},
        {b, 5},
        {c, 3},
        {d, 2},
        {e, 1},
        {f, 3}
    });
}

TEST_F(DualTree, SelfLoops) {
    self_loops({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(DualTree, ParallelLinks) {
    parallel_links({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(DualTree, Cyclic) {
    cyclic({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}
