#ifndef TREES_TREE_HPP
#define TREES_TREE_HPP

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace trees {
    class Tree;

    using Vertex   = std::shared_ptr<Tree>;
    using Vertices = std::vector<Vertex>;
    using Degrees  = std::map<Vertex, size_t>;

    using Callback = std::function<void(Vertex, const Vertices &)>;
    using Search   = std::function<bool(Vertex, const Vertices &)>;

    class Tree : public std::enable_shared_from_this<Tree> {
      public:
        static void remove(const Vertices &vertices);
        static void restore(const Vertices &vertices);

        bool removed = false;

        Vertices children;

        explicit Tree(const Vertices &children = {});

        Tree(const Tree &)            = delete;
        Tree &operator=(const Tree &) = delete;

        ~Tree() = default;

        Vertex add_child(Vertex vertex);

        // Depth first search including itself.
        Vertices dfs();

        // Breadth first search including itself.
        Vertices bfs();

        // Depth first search of a condition with early return.
        bool search(const Search &condition);

        // Count the indegree of each vertex.
        Degrees indegrees();

        // Count the outdegree of each vertex.
        Degrees outdegrees();

        // Contains a specific vertex.
        bool contains(const Vertex &target);

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
