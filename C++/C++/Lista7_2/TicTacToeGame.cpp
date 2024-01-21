//
// Created by viktoria on 24.04.23.
//

#include "TicTacToeGame.h"
namespace ai {

    std::string MyMove(user_interface::TicTacToeGame &game) {
        int SIZE = user_interface::MySize;
        game_state::GameState state = game.MyGame;
        if (!state.GameOver()) {
            int CENTER = (SIZE * SIZE) / 2;
            int ClosestToCenter = 10000000;
            int *MyBoard = game.MyBoard;
            std::map<std::string, int> *l = state.LABELS;

            for (int i = 0; i < SIZE * SIZE; ++i) {
                if ((MyBoard[i] == -1) && (abs(CENTER - i)) < (abs(CENTER - ClosestToCenter))) {
                    ClosestToCenter = i;
                }
            }
            int index = ClosestToCenter;
            auto it = l->begin();
            std::advance(it, index);
            if (it != l->end()) { // check if iterator is still within the range of the map
                return it->first;
            } else {
                throw std::out_of_range("Index out of range");
            }


        }

    }
}

namespace user_interface {
    int ROUNDS = 6;
    int MySize = 5;


    void TicTacToeGame::DisplayBoard() {
        // Display the horizontal lines
        std::vector<std::string> figures = {" ", "X", "O"};
        std::string alphabet("abcdefghijklmnopqrstuvwxyz");
        std::string my_str = alphabet.substr(0, MySize);

        // Display the numbers on top
        std::cout << "  ";
        for (int i = 0; i < MySize; i++) {
            std::cout << "  " << i << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < MySize; i++) {
            std::cout << my_str[i] << " "; // Display the letter on the left

            for (int j = 0; j < MySize; j++) {
                int ind = MyBoard[i * MySize + j];
                switch (ind) {
                    case 0:
                        std::cout << "| " << figures[1] << " ";
                        break;
                    case 1:
                        std::cout << "| " << figures[2] << " ";
                        break;
                    default:
                        std::cout << "| " << figures[0] << " ";
                        break;
                }
            }
            std::cout << "|" << std::endl;

            // Display the horizontal lines
            std::cout << "  ";
            for (int j = 0; j < MySize; j++) {
                std::cout << "___ ";
            }
            std::cout << std::endl;
        }
    }


    void TicTacToeGame::PrintingWinner() {
        if (MyGame.GameOver()) {
            std::cout << "The Game is OVER!" << std::endl;
            int res = MyGame.WhoWon();
            switch (res) {
                case 0:
                    std::cout << "YOU won! :(" << std::endl;
                    break;

                case 1:
                    std::cout << "I won! :)" << std::endl;
                    break;

                default:
                    std::cout << "DRAW! :(" << std::endl;
                    break;

            }

        }
    }
}

int main() {

    using namespace user_interface;
    TicTacToeGame game = TicTacToeGame();
    std::cout << "||||| T I C K -- T A C -- T O E -- G A M E |||||" << std::endl;
    std::cout << "YOU - 1 [X] | ME - [O]" << std::endl;
    //
    game.DisplayBoard();
    int counter = 0;
    while ((!(game.MyGame.GameOver())) && (counter < ROUNDS)){
        std::cout << "Your move: input field, e.g a1: ";
        std::string user_move;
        std::cin >> user_move;
        int ind = game.MyLabels->at(user_move);

        if (game.MyBoard[ind] == -1) {
            game.MyGame.ChangeBoard(0, ind);
            game.DisplayBoard();
            std::string my_move = ai::MyMove(game);
            int my_ind = game.MyLabels->at(my_move);
            game.MyGame.ChangeBoard(1, my_ind);
            std::cout << "My move is: " << my_move << std::endl;
            game.DisplayBoard();
            counter++;}
        else{
            throw std::invalid_argument("The field is already used!");
        }


    }

    game.PrintingWinner();



}