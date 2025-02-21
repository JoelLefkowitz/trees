#include "cyclic.spec.hpp"
#include "../setup/suites.spec.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <map>
#include <memory>
#include <vector>

//      a(1)
//       ↓
//      b(2)
//    ↙     ↖︎
// c(3)  →  e(5)
//  ↓        ↓
// d(4)     f(6)
void CyclicTree::SetUp() {
    a = std::make_shared<Tree<int>>(1);
    b = std::make_shared<Tree<int>>(2);
    c = std::make_shared<Tree<int>>(3);
    d = std::make_shared<Tree<int>>(4);
    e = std::make_shared<Tree<int>>(5);
    f = std::make_shared<Tree<int>>(6);

    a->add_child(b);
    b->add_child(c);
    c->add_child(d);
    c->add_child(e);
    e->add_child(b);
    e->add_child(f);
}

TEST_F(CyclicTree, dfs) {
    dfs({
        {a, {a, b, c, d, e, f}},
        {b, {b, c, d, e, f}   },
        {c, {c, d, e, b, f}   },
        {d, {d}               },
        {e, {e, b, c, d, f}   },
        {f, {f}               }
    });
}

TEST_F(CyclicTree, BFS) {
    bfs({
        {a, {a, b, c, d, e, f}},
        {b, {b, c, d, e, f}   },
        {c, {c, d, e, b, f}   },
        {d, {d}               },
        {e, {e, b, f, c, d}   },
        {f, {f}               }
    });
}

TEST_F(CyclicTree, Indegrees) {
    indegrees({
        {a, {{a, 0}, {b, 2}, {c, 1}, {d, 1}, {e, 1}, {f, 1}}},
        {b, {{b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}}        },
        {c, {{c, 1}, {d, 1}, {e, 1}, {b, 1}, {f, 1}}        },
        {d, {{d, 0}}                                        },
        {e, {{e, 1}, {b, 1}, {c, 1}, {d, 1}, {f, 1}}        },
        {f, {{f, 0}}                                        }
    });
}

TEST_F(CyclicTree, Outdegrees) {
    outdegrees({
        {a, {{a, 1}, {b, 1}, {c, 2}, {d, 0}, {e, 2}, {f, 0}}},
        {b, {{b, 1}, {c, 2}, {d, 0}, {e, 2}, {f, 0}}        },
        {c, {{c, 2}, {d, 0}, {e, 2}, {b, 1}, {f, 0}}        },
        {d, {{d, 0}}                                        },
        {e, {{e, 2}, {b, 1}, {c, 2}, {d, 0}, {f, 0}}        },
        {f, {{f, 0}}                                        }
    });
}

TEST_F(CyclicTree, Size) {
    size({
        {a, 6},
        {b, 5},
        {c, 5},
        {d, 1},
        {e, 5},
        {f, 1}
    });
}

TEST_F(CyclicTree, SelfLoops) {
    self_loops({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(CyclicTree, ParallelLinks) {
    parallel_links({
        {a, false},
        {b, false},
        {c, false},
        {d, false},
        {e, false},
        {f, false}
    });
}

TEST_F(CyclicTree, Cyclic) {
    cyclic({
        {a, true },
        {b, true },
        {c, true },
        {d, false},
        {e, true },
        {f, false}
    });
}
