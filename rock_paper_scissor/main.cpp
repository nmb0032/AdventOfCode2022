/**
 * Advent of code day 2
 * Rock paper scissors
 *
 * Rock paper scissors defined as enum values
 *
 * outcome of round 0 LOST, 3 DRAW, 6 WON
 *
 * Calculate function take opponent choice A, my choice Y return my points for round
 */

#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <fstream>
#include "game.h"

typedef std::vector<std::pair<Moves, Moves>> Game1;
typedef std::vector<std::pair<Moves, Outcomes>> Game2;

Outcomes calc_outcomes(const char &outcome)
{
    switch (outcome)
    {
    case 'X':
        return Outcomes::LOST;
        break;
    case 'Y':
        return Outcomes::DRAW;
        break;
    case 'Z':
        return Outcomes::WON;
        break;
    default:
        return (Outcomes)0;
    }
}

Moves calc_move(const char &move)
{
    switch (move)
    {
    case 'A':
        return Moves::ROCK;
        break;
    case 'B':
        return Moves::PAPER;
        break;
    case 'C':
        return Moves::SCISSORS;
        break;
    case 'X':
        return Moves::ROCK;
        break;
    case 'Y':
        return Moves::PAPER;
        break;
    case 'Z':
        return Moves::SCISSORS;
        break;
    default:
        return (Moves)0;
    }
}

Moves reverse_outcome(Moves move, Outcomes outcome)
{
    if (outcome == Outcomes::WON)
    {
        switch (move)
        {
        case Moves::SCISSORS:
            return Moves::ROCK;
        case Moves::PAPER:
            return Moves::SCISSORS;
        case Moves::ROCK:
            return Moves::PAPER;
        }
    }
    else if (outcome == Outcomes::LOST)
    {
        switch (move)
        {
        case Moves::SCISSORS:
            return Moves::PAPER;
        case Moves::ROCK:
            return Moves::SCISSORS;
        case Moves::PAPER:
            return Moves::ROCK;
        }
    }
    return move;
}

template <typename T, typename U>
T read_file(const std::string &path, std::function<U(char)> fcn)
{
    std::ifstream file(path);

    T result{};
    std::string line;
    while (std::getline(file, line))
    {
        result.push_back(std::make_pair(calc_move(line[0]), fcn(line[2])));
    }
    return result;
}

int calculate_1(const Moves &opponent_move, const Moves &my_move)
{
    if (opponent_move == my_move)
        return Outcomes::DRAW + my_move;

    if ((opponent_move == Moves::PAPER && my_move == Moves::SCISSORS) ||
        (opponent_move == Moves::ROCK && my_move == Moves::PAPER) ||
        (opponent_move == Moves::SCISSORS && my_move == Moves::ROCK))
        return Outcomes::WON + my_move;

    return Outcomes::LOST + my_move;
}

int calculate_2(const Moves &opponent_move, const Outcomes &outcomes)
{
    if (outcomes == Outcomes::LOST)
        return Outcomes::LOST + reverse_outcome(opponent_move, Outcomes::LOST);
    if (outcomes == Outcomes::DRAW)
        return Outcomes::DRAW + opponent_move;
    if (outcomes == Outcomes::WON)
        return Outcomes::WON + reverse_outcome(opponent_move, Outcomes::WON);
    return 0;
}

template <typename T, typename U>
int run(const T &input, std::function<int(Moves, U)> fcn)
{
    int total{0};
    for (auto game : input)
    {
        total += fcn(game.first, game.second);
    }
    return total;
}

int main(int, char **)
{
    Moves move{PAPER};
    int total_score = run<Game1, Moves>(read_file<Game1, Moves>("../data/game.txt", &calc_move), &calculate_1);
    std::cout << "TOTAL SCORE WITH FIRST CHARACTER OPPONENT MOVE AND SECOND YOUR MOVE: " << total_score << std::endl;
    total_score = run<Game2, Outcomes>(read_file<Game2, Outcomes>("../data/game.txt", &calc_outcomes), &calculate_2);
    std::cout << "TOTAL SCORE WITH FIRST CHARACTER OPPONENT MOVE AND SECOND OUTCOME:  " << total_score << std::endl;
}
