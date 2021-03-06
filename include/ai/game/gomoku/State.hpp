#ifndef AI_GAME_GOMOKU_STATE_HPP
#define AI_GAME_GOMOKU_STATE_HPP

#include <vector>
#include <memory>
#include <stack>
#include <array>
#include <unordered_map>
#include "Basic.hpp"
#include "InfiniteMatrix.hpp"

namespace ai {
namespace game {
namespace gomoku {

struct Action {
    int x, y;
};

bool operator == (Action action1, Action action2);

static const int allow_distance = 2;
static const unsigned int alphabeta_depth = 2;

class State {
private:
    InfiniteMatrix<Cell> cells_;
    InfiniteMatrix<unsigned char> allow_cells_;
    Cell current_player_;
    std::stack<Action> move_stack_;
    std::stack<bool> terminated_stack_;
    std::stack<float> hvalue_stack_;

public:
    State(Cell start_player = Cell::HUMAN);

    std::vector<Action> legal_actions() const;

    Cell operator() (int x, int y) const;

    void move(Action action);

    void unmove();

    float hvalue() const { return hvalue_stack_.top(); }

    bool is_terminal() const { return terminated_stack_.top(); }

    bool is_maximizing() const { return current_player() == Cell::AI; }

    Cell current_player() const { return current_player_; }

}; // class State

float alphabeta(State& state, unsigned int depth, float alpha, float beta);

Action AI_next_move(State& state);

} // namespace gomoku
} // namespace game
} // namespace ai

#endif // AI_GAME_GOMOKU_STATE_HPP
