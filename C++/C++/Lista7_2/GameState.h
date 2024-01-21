//
// Created by viktoria on 24.04.23.
//

#ifndef LISTA7_2_GAMESTATE_H
#define LISTA7_2_GAMESTATE_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <exception>
#include <algorithm>
#include <map>

namespace game_state {

    enum PlayerSymbol {
        NONE = -1,
        USER = 0,
        COMPUTER = 1,
        GameON = 2

    };
    class GameState {
    public:
        GameState(int size, int num_rounds);
        int* board;
        std::map<std::string, int>* LABELS;
        bool IsFull();
        bool GameOver();
        int WhoWon();
        void ChangeBoard(int who, int ind){
            board[ind] = who;
        }


    private:
        int SIZE;
        int NUM_ROUNDS;
        int CURRENT;
        int ROUND;
    };

} // game_state

#endif //LISTA7_2_GAMESTATE_H
