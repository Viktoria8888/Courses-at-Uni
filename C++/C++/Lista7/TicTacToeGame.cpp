//
// Created by viktoria on 24.04.23.
//

#include "TicTacToeGame.h"

namespace user_interface {
    void TicTacToeGame::DisplayBoard() {
        // Display the horizontal lines
        std::cout << " ";
        for (int i = 0; i < MySize; i++) {
            std::cout << "___ ";
        }
        std::cout << std::endl;

        // Display the cells
        for (int i = 0; i < MySize; i++) {
            std::cout << "|";
            for (int j = 0; j < MySize; j++) {
                std::cout << " " << MyBoard[i * MySize + j] << " |";
            }
            std::cout << std::endl;

            // Display the horizontal lines
            std::cout << " ";
            for (int j = 0; j < MySize; j++) {
                std::cout << "___ ";
            }
            std::cout << std::endl;
        }
    }



    void TicTacToeGame::PrintingWinner() {
        if (MyGame.IsFull()) {
            std::cout << "The Game is OVER!" << std::endl;
            int8_t res = MyGame.WhoWon();
            switch (res) {
                case 0:
                    std::cout << "YOU won! :(" << std::endl;
                    break;
                case 1:
                    std::cout << "ME won! :)" << std::endl;
                    break;
                default:
                    std::cout << "DRAW! :(" << std::endl;
                    break;

            }

        }
    }
}

int main(){
    using namespace user_interface;
    TicTacToeGame game = TicTacToeGame();
    game.DisplayBoard();

}