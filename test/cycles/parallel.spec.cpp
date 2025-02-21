#include "parallel.spec.hpp"
#include "../setup/suites.spec.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <memory>

// a(1)
//  ↓
// b(2) ⇄ d(4)
//  ↓      ↓
// c(3)   e(5)
void ParallelTree::SetUp() {
    a = std::make_shared<Tree<int>>(1);
    b = std::make_shared<Tree<int>>(2);
    c = std::make_shared<Tree<int>>(3);
    d = std::make_shared<Tree<int>>(4);
    e = std::make_shared<Tree<int>>(5);

    a->add_child(b);
    b->add_child(c);
    b->add_child(d);
    d->add_child(b);
    d->add_child(e);
}

TEST_F(ParallelTree, DFS) {
    dfs({
        {a, {a, b, c, d, e}},
        {b, {b, c, d, e}   },
        {c, {c}            },
        {d, {d, b, c, e}   },
        {e, {e}            }
    });
}

TEST_F(ParallelTree, BFS) {
    bfs({
        {a, {a, b, c, d, e}},
        {b, {b, c, d, e}   },
        {c, {c}            },
        {d, {d, b, e, c}   },
        {e, {e}            }
    });
}

TEST_F(ParallelTree, Indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 2}, {c, 1}, {d, 1}, {e, 1}}},
        {b, {{b, 1}, {c, 1}, {d, 1}, {e, 1}}        },
        {c, {{c, 0}}                                },
        {d, {{d, 1}, {b, 1}, {c, 1}, {e, 1}}        },
        {e, {{e, 0}}                                }
    });
}

TEST_F(ParallelTree, Outdegrees) {
    outdegrees({
        {a, {{a, 1}, {b, 2}, {c, 0}, {d, 2}, {e, 0}}},
        {b, {{b, 2}, {c, 0}, {d, 2}, {e, 0}}        },
        {c, {{c, 0}}                                },
        {d, {{d, 2}, {b, 2}, {c, 0}, {e, 0}}        },
        {e, {{e, 0}}                                }
    });
}

TEST_F(ParallelTree, Size) {
    size({
        {a, 5},
        {b, 4},
        {c, 1},
        {d, 4},
        {e, 1}
    });
}

TEST_F(ParallelTree, SelfLoops) {
    self_loops({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false}
    });
}

TEST_F(ParallelTree, ParallelLinks) {
    parallel_links({
        {a, true },
 // {b, true },
        {c, false},
        {d, true },
        {e, false}
    });
}

TEST_F(ParallelTree, Cyclic) {
    cyclic({
        {a, true },
        {b, true },
        {c, false},
        {d, true },
        {e, false}
    });
}
