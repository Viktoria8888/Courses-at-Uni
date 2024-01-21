//
// Created by viktoria on 24.04.23.
//

#ifndef LISTA7_AI_H
#define LISTA7_AI_H
#include "TicTacToeGame.h"
namespace ai {
    using namespace user_interface;
    std::string MyMove(TicTacToeGame& game){
        int SIZE = MySize;
        game_state::GameState state = game.MyGame;
        if (!state.GameOver()){
            int CENTER = (SIZE*SIZE)/2;
            int ClosestToCenter = 10000000;
            int* MyBoard = game.MyBoard;
            std::vector<std::string>* l = state.LABELS;

            for (int i =0; i< SIZE*SIZE; ++i){
                if ((MyBoard[i] == -1) && (abs(CENTER - i))< (abs(CENTER - ClosestToCenter))){
                    ClosestToCenter = i;
                }
            }
            return (*l)[ClosestToCenter];}

        else{
            game.PrintingWinner();
            return std::string("Bye!");
        }
    }

}

#endif //LISTA7_AI_H
