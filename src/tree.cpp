#include "tree.hpp"
#include "../../functional/generics/functor/filter.tpp"
#include "../../functional/generics/functor/foreach.tpp"
#include "../../functional/generics/functor/map.tpp"
#include "../../functional/instances/booleans/booleans.tpp"
#include "../../functional/instances/vectors/elements.tpp"
#include "../../functional/instances/vectors/immutable.tpp"
#include <cstddef>
#include <deque>
#include <vector>

void trees::Tree::remove(const Vertices &vertices) {
    std::function<void(Vertex)> remove_child = [](auto child) {
        if (child) {
            child->removed = true;
        }
    };

    functional::foreach (remove_child, vertices);
}

void trees::Tree::restore(const Vertices &vertices) {
    std::function<void(Vertex)> include_child = [](auto child) {
        if (child) {
            child->removed = false;
        }
    };

    functional::foreach (include_child, vertices);
}

trees::Tree::Tree(const Vertices &children) : children(functional::unique(children)) {}

trees::Vertex trees::Tree::add_child(Vertex vertex) {
    children.push_back(vertex);
    return vertex;
}

trees::Vertices trees::Tree::dfs() {
    Vertices visited;

    std::deque<Vertex> next({this->shared_from_this()});

    while (!next.empty()) {
        auto vertex = next.front();
        next.pop_front();

        if (!vertex->removed && !functional::contains(visited, vertex)) {
            visited.push_back(vertex);

            for (auto i : functional::reverse(vertex->children)) {
                next.push_front(i);
            }
        }
    }

    return visited;
}

trees::Vertices trees::Tree::bfs() {
    Vertices visited;

    std::deque<Vertex> next({this->shared_from_this()});

    while (!next.empty()) {
        auto vertex = next.front();
        next.pop_front();

        if (!vertex->removed && !functional::contains(visited, vertex)) {
            visited.push_back(vertex);

            for (auto i : vertex->children) {
                next.push_back(i);
            }
        }
    }

    return visited;
}

bool trees::Tree::search(const Search &condition) {
    Vertices           visited;
    std::deque<Vertex> next({this->shared_from_this()});

    std::map<Vertex, Vertices> paths;

    while (!next.empty()) {
        auto vertex = next.front();
        auto path   = paths[vertex];

        next.pop_front();
        paths.erase(vertex);

        if (!vertex->removed && !functional::contains(visited, vertex)) {
            if (condition(vertex, path)) {
                return true;
            }

            visited.push_back(vertex);

            for (auto i : functional::reverse(vertex->children)) {
                next.push_front(i);
                paths[i] = visited;
            }
        }
    }

    return false;
}

trees::Degrees trees::Tree::indegrees() {
    Degrees map({
        {this->shared_from_this(), 0}
    });

    std::function<void(Vertex)> count = [&map](auto child) {
        if (!child->removed) {
            if (map.count(child) == 0) {
                map[child] = 0;
            }

            map[child] += 1;
        }
    };

    std::function<void(Vertex)> step = [&count](auto vertex) { functional::foreach (count, vertex->children); };

    if (removed) {
        return {};
    }

    functional::foreach (step, dfs());
    return map;
}

trees::Degrees trees::Tree::outdegrees() {
    Degrees map;

    std::function<bool(Vertex)> included = [](Vertex vertex) { return !vertex->removed; };

    std::function<void(Vertex)> step = [&map, &included](auto vertex) {
        map[vertex->shared_from_this()] = functional::filter(included, vertex->children).size();
    };

    functional::foreach (step, dfs());
    return map;
}

bool trees::Tree::contains(Vertex target) {
    return search([target](auto vertex, const auto &) { return vertex == target; });
}

size_t trees::Tree::size() { return dfs().size(); }

bool trees::Tree::singleton() const { return children.empty(); }

bool trees::Tree::self_loops() {
    return search([](auto vertex, const auto &) { return functional::contains(vertex->children, vertex); });
}

bool trees::Tree::parallel_links() {
    return search([](auto vertex, const auto &path) {
        return !path.empty() && functional::contains(vertex->children, path.back());
    });
}

bool trees::Tree::simple() { return !self_loops() && !parallel_links(); }

bool trees::Tree::cyclic() {
    return !removed && search([](auto vertex, const auto &path) {
        return functional::contains(vertex->children, vertex) || functional::overlaps(vertex->children, path);
    });
}

bool trees::Tree::multitree() {
    std::function<bool(const Vertex &, const size_t &)> multiple = [](const auto &, const auto &size) {
        return size > 1;
    };

    return functional::any(functional::map(multiple, indegrees()));
}
