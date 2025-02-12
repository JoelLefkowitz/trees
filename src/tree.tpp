#ifndef TREES_TREE_TPP
#define TREES_TREE_TPP

#include "tree.hpp"
#include <cstddef>
#include <deque>
#include <functional/generics/functor/filter.tpp>
#include <functional/generics/functor/foreach.tpp>
#include <functional/generics/functor/map.tpp>
#include <functional/implementations/booleans/booleans.tpp>
#include <functional/implementations/vectors/elements.tpp>
#include <functional/implementations/vectors/immutable.tpp>
#include <vector>

template <typename T>
void trees::Tree<T>::remove(const Vertices<T> &vertices) {
    std::function<void(Vertex<T>)> remove_child = [](auto child) {
        if (child) {
            child->removed = true;
        }
    };

    functional::foreach (remove_child, vertices);
}

template <typename T>
void trees::Tree<T>::restore(const Vertices<T> &vertices) {
    std::function<void(Vertex<T>)> include_child = [](auto child) {
        if (child) {
            child->removed = false;
        }
    };

    functional::foreach (include_child, vertices);
}

template <typename T>
trees::Tree<T>::Tree(T content, const Vertices<T> &children)
    : content(content)
    , children(functional::unique(children)) {}

template <typename T>
trees::Vertex<T> trees::Tree<T>::add_child(Vertex<T> vertex) {
    children.push_back(vertex);
    return vertex;
}

template <typename T>
trees::Vertices<T> trees::Tree<T>::dfs() {
    Vertices<T> visited;

    std::deque<Vertex<T>> next({this->shared_from_this()});

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

template <typename T>
trees::Vertices<T> trees::Tree<T>::bfs() {
    Vertices<T> visited;

    std::deque<Vertex<T>> next({this->shared_from_this()});

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

template <typename T>
bool trees::Tree<T>::search(const Search<T> &condition) {
    Vertices<T>           visited;
    std::deque<Vertex<T>> next({this->shared_from_this()});

    std::map<Vertex<T>, Vertices<T>> paths;

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

template <typename T>
trees::Degrees<T> trees::Tree<T>::indegrees() {
    Degrees<T> map({
        {this->shared_from_this(), 0}
    });

    std::function<void(Vertex<T>)> count = [&map](auto child) {
        if (!child->removed) {
            if (map.count(child) == 0) {
                map[child] = 0;
            }

            map[child] += 1;
        }
    };

    std::function<void(Vertex<T>)> step = [&count](auto vertex) { functional::foreach (count, vertex->children); };

    if (removed) {
        return {};
    }

    functional::foreach (step, dfs());
    return map;
}

template <typename T>
trees::Degrees<T> trees::Tree<T>::outdegrees() {
    Degrees<T> map;

    std::function<bool(const Vertex<T> &)> included = [](const Vertex<T> &vertex) { return !vertex->removed; };

    std::function<void(Vertex<T>)> step = [&map, &included](auto vertex) {
        map[vertex->shared_from_this()] = functional::filter(included, vertex->children).size();
    };

    functional::foreach (step, dfs());
    return map;
}

template <typename T>
bool trees::Tree<T>::contains(const Vertex<T> &target) {
    return search([target](auto vertex, const auto &) { return vertex == target; });
}

template <typename T>
size_t trees::Tree<T>::size() {
    return dfs().size();
}

template <typename T>
bool trees::Tree<T>::singleton() const {
    return children.empty();
}

template <typename T>
bool trees::Tree<T>::leaf() const {
    return children.empty() || (children.size() == 1 && children.at(0) == this->shared_from_this());
}

template <typename T>
bool trees::Tree<T>::self_loops() {
    return search([](auto vertex, const auto &) { return functional::contains(vertex->children, vertex); });
}

template <typename T>
bool trees::Tree<T>::parallel_links() {
    return search([](auto vertex, const auto &path) {
        return !path.empty() && functional::contains(vertex->children, path.back());
    });
}

template <typename T>
bool trees::Tree<T>::simple() {
    return !self_loops() && !parallel_links();
}

template <typename T>
bool trees::Tree<T>::cyclic() {
    return !removed && search([](auto vertex, const auto &path) {
        return functional::contains(vertex->children, vertex) || functional::overlaps(vertex->children, path);
    });
}

template <typename T>
bool trees::Tree<T>::multitree() {
    std::function<bool(const Vertex<T> &, const size_t &)> multiple = [](const auto &, const auto &size) {
        return size > 1;
    };

    return functional::any(functional::map(multiple, indegrees()));
}

#endif
