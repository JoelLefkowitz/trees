#ifndef TREES_TREE_HPP
#define TREES_TREE_HPP

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace trees {
    template <typename T>
    class Tree;

    template <typename T>
    using Vertex = std::shared_ptr<Tree<T>>;

    template <typename T>
    using Vertices = std::vector<Vertex<T>>;

    template <typename T>
    using Degrees = std::map<Vertex<T>, size_t>;

    template <typename T>
    using Callback = std::function<void(Vertex<T>, const Vertices<T> &)>;

    template <typename T>
    using Search = std::function<bool(Vertex<T>, const Vertices<T> &)>;

    template <typename T>
    class Tree : public std::enable_shared_from_this<Tree<T>> {
      public:
        static void remove(const Vertices<T> &vertices);
        static void restore(const Vertices<T> &vertices);

        T content;

        bool removed = false;

        Vertices<T> children;

        explicit Tree(T content, const Vertices<T> &children = {});

        Tree(const Tree<T> &)               = delete;
        Tree<T> &operator=(const Tree<T> &) = delete;

        ~Tree() = default;

        Vertex<T> add_child(Vertex<T> vertex);

        // Depth first search including itself.
        Vertices<T> dfs();

        // Breadth first search including itself.
        Vertices<T> bfs();

        // Depth first search of a condition with early return.
        bool search(const Search<T> &condition);

        // Count the indegree of each vertex.
        Degrees<T> indegrees();

        // Count the outdegree of each vertex.
        Degrees<T> outdegrees();

        // Contains a specific vertex.
        bool contains(const Vertex<T> &target);

        // Number of vertices.
        size_t size();

        // No children.
        bool singleton() const;

        // No children other than itself.
        bool leaf() const;

        // For any vertex a. a ↻.
        bool self_loops();

        // For any pair of vertices a b. a ⇄ b.
        bool parallel_links();

        // No self-loops or parallel links.
        bool simple();

        // Contains a cycle, includes self-loops and parallel links.
        bool cyclic();

        // For any vertex a. indegree(a) > 1.
        bool multitree();
    };
}

#endif
