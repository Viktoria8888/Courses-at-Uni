//
// Created by viktoria on 24.04.23.
//

#ifndef LISTA7_TICTACTOEGAME_H
#define LISTA7_TICTACTOEGAME_H

#include "GameState.h"
namespace user_interface {
    using namespace game_state;
    int ROUNDS = 5;
    int MySize = 3;

    class TicTacToeGame {
    public:
        GameState MyGame;
        int* MyBoard = MyGame.board; // change at ai
        TicTacToeGame() : MyGame(MySize, ROUNDS) {};
        void DisplayBoard();
        void PrintingWinner();
    };
}


#endif //LISTA7_TICTACTOEGAME_H
