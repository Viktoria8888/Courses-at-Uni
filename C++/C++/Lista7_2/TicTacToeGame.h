//
// Created by viktoria on 24.04.23.
//

#ifndef LISTA7_2_TICTACTOEGAME_H
#define LISTA7_2_TICTACTOEGAME_H

#include "GameState.h"
namespace user_interface {
    using namespace game_state;
    extern int ROUNDS;
    extern int MySize;


    class TicTacToeGame {
    public:
        GameState MyGame;
        int* MyBoard = MyGame.board; // change at ai
        std::map<std::string, int>* MyLabels = MyGame.LABELS;
        TicTacToeGame() : MyGame(MySize, ROUNDS) {};
        //std::string letter_rows = alphabet.substr(0,MySize-1);
        void DisplayBoard();
        void PrintingWinner();
    };
}


#endif //LISTA7_2_TICTACTOEGAME_H
