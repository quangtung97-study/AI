#ifndef AI_SEARCH_IMAGEPUZZLE_PROBLEM_HPP
#define AI_SEARCH_IMAGEPUZZLE_PROBLEM_HPP

#include "Node.hpp"
#include <memory>
#include <vector>
#include <algorithm>

namespace ai {
namespace search {
namespace imagepuzzle {

class Problem {
private:
    const State begin_, end_;

public:
    using NodeType = Node;
    using StateType = State;
    using ActionType = Action;

public:
    Problem(const State& begin, const State& end) 
        : begin_{begin}, end_{end} {}

    const State& initial_state() const { return begin_; }

    bool is_terminal(const Node *node) const {
        return node->state() == end_;
    }

    auto solution(const NodeType *node) const {
        std::vector<ActionType> actions;
        while (node->parent() != nullptr) {
            actions.push_back(node->action());
            node = node->parent();
        }
        std::reverse(actions.begin(), actions.end());
        return actions;
    }

    float h(const NodeType *node) const {
        if (node->heuristic_value() == std::numeric_limits<float>::max()) {
            auto& state = node->state();
            node->heuristic_value(state.manhattan_distance_to(end_));
            return node->heuristic_value();
        }
        return node->heuristic_value();
    }

    float g(const NodeType *node) const {
        return node->path_cost();
    }

}; // class Problem

} // namespace imagepuzzle
} // namespace search
} // namespace ai

#endif // AI_SEARCH_IMAGEPUZZLE_PROBLEM_HPP
