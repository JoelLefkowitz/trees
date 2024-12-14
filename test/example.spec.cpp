#include "../src/tree.hpp"
#include <functional/generics/functor/map.tpp>
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using namespace trees;

class Component {
  public:
    int x;

    explicit Component(int x) : x(x) {};

    Component(const Component &)            = delete;
    Component &operator=(const Component &) = delete;

    ~Component() = default;
};

//      a(1)
//       ↓
//      b(2)
//    ↙     ↘
// c(3)  ←  d(4)   ⇄   e(5)
//  ↓        ↑       ↙     ↘
// f(6)  →  g(7)  h(8)    i(9) ↺
TEST(ExampleTree, Examples) {
    auto a = std::make_shared<Tree>();
    auto b = std::make_shared<Tree>();
    auto c = std::make_shared<Tree>();
    auto d = std::make_shared<Tree>();
    auto e = std::make_shared<Tree>();
    auto f = std::make_shared<Tree>();
    auto g = std::make_shared<Tree>();
    auto h = std::make_shared<Tree>();
    auto i = std::make_shared<Tree>();

    a->add_child(b);
    b->add_child(c);
    b->add_child(d);
    c->add_child(f);
    d->add_child(c);
    d->add_child(e);
    e->add_child(d);
    e->add_child(h);
    e->add_child(i);
    f->add_child(g);
    g->add_child(d);
    i->add_child(i);

    EXPECT_EQ(a->bfs(), std::vector<std::shared_ptr<Tree>>({a, b, c, d, f, e, g, h, i}));
    EXPECT_EQ(a->dfs(), std::vector<std::shared_ptr<Tree>>({a, b, c, f, g, d, e, h, i}));

    // TODO: Switch to generics for mapping the dfs and running a->search(...)
    // std::function<int(std::shared_ptr<Component>)> mapper = [](auto component) { return component->x; };
    // std::vector<std::shared_ptr<Component>> vec = (a->dfs());
    // std::vector<int> mapped = functional::map(mapper, vec);
    // EXPECT_EQ(functional::map(mapper, a->dfs()), mapped);

    EXPECT_TRUE(a->contains(g));
    
    EXPECT_EQ(a->size(), 9);
    EXPECT_EQ(b->size(), 8);
    
    EXPECT_TRUE(h->leaf());
    EXPECT_TRUE(h->singleton());
    
    EXPECT_TRUE(i->leaf());
    EXPECT_FALSE(i->singleton());

    EXPECT_TRUE(a->self_loops());
    EXPECT_TRUE(a->parallel_links());
    EXPECT_TRUE(a->cyclic());
    EXPECT_TRUE(a->multitree());
}
