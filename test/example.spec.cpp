#include "../src/tree.tpp"
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
// c(3)  ←  d(4)    ⇄    e(5)
//  ↓        ↑        ↙   ↓   ↘
// f(6)  →  g(7)  h(8)  i(✖)  j(10) ↺
TEST(ExampleTree, Examples) {

    // TODO: Add move semantics 
    auto a = std::make_shared<Tree<Component>>(Component(1));
    auto b = std::make_shared<Tree<Component>>(Component(2));
    auto c = std::make_shared<Tree<Component>>(Component(3));
    auto d = std::make_shared<Tree<Component>>(Component(4));
    auto e = std::make_shared<Tree<Component>>(Component(5));
    auto f = std::make_shared<Tree<Component>>(Component(6));
    auto g = std::make_shared<Tree<Component>>(Component(7));
    auto h = std::make_shared<Tree<Component>>(Component(8));
    auto i = std::make_shared<Tree<Component>>(Component(9));
    auto j = std::make_shared<Tree<Component>>(Component(10));

    a->add_child(b);
    b->add_child(c);
    b->add_child(d);
    c->add_child(f);
    d->add_child(c);
    d->add_child(e);
    e->add_child(d);
    e->add_child(h);
    e->add_child(i);
    e->add_child(j);
    f->add_child(g);
    g->add_child(d);
    j->add_child(j);

    e->remove({i});

    EXPECT_EQ(a->bfs(), std::vector<std::shared_ptr<Tree<Component>>>({a, b, c, d, f, e, g, h, j}));
    EXPECT_EQ(a->dfs(), std::vector<std::shared_ptr<Tree<Component>>>({a, b, c, f, g, d, e, h, j}));

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

    EXPECT_TRUE(j->leaf());
    EXPECT_FALSE(j->singleton());

    EXPECT_TRUE(a->self_loops());
    EXPECT_TRUE(a->parallel_links());
    EXPECT_TRUE(a->cyclic());
    EXPECT_TRUE(a->multitree());
}
