//
// Created by viktoria on 24.04.23.
//

#include "GameState.h"

namespace game_state {

    std::string alphabet("abcdefghijklmnopqrstuvwxyz");

    bool CheckRow(int row, const int *board, int size, int player) {
        for (int col = 0; col < size; col++) {
            if (board[row * size + col] != player) {
                return false;
            }
        }
        return true;
    }

    bool CheckColumn(int col, const int *board, int size, int player) {
        for (int row = 0; row < size; row++) {
            if (board[row * size + col] != player) {
                return false;
            }
        }
        return true;
    }

    bool CheckDiagonal(int direction, const int *board, int size, int player) {
        bool equal = true;
        for (int i = 0; i < size; i++) {
            int index = (direction == 1) ? (i * size + i) : ((i + 1) * size - (i + 1));
            if (board[index] != player) {
                equal = false;
                break;
            }
        }
        return equal;
    }


    GameState::GameState(int size, int num_rounds) : CURRENT(USER),
                                                     ROUND(0), NUM_ROUNDS(num_rounds) {
        if (SIZE < 3){
            throw std::invalid_argument("The size of the board is too small");
        }
        board = new int[SIZE * SIZE];
        for (int i = 0; i < SIZE * SIZE; i++) {
            board[i] = NONE;
        }

        // Creating labels
        LABELS = new std::vector<std::string>(SIZE * SIZE);
        std::string letter_rows = alphabet.substr(0,SIZE-1);
        for (int i = 0; i < SIZE*SIZE; i++) {
            LABELS->push_back(letter_rows[i] + std::to_string(i/2));
        }

    }

    bool GameState::IsFull() {
        for (int i = 0; i < SIZE * SIZE; i++) {
            if (board[i] == NONE) { return false; }
        }
        return true;
    }

    int8_t GameState::WhoWon() {

        for (int i = 0; i < SIZE; i++) {
            if (CheckRow(i, board, SIZE, USER) ||
                CheckColumn(i, board, SIZE, USER) ||
                CheckDiagonal(1, board, SIZE, USER) ||
                CheckDiagonal(-1, board, SIZE, USER)) {
                return USER;
            } else {
                if (CheckRow(i, board, SIZE, COMPUTER) ||
                    CheckColumn(i, board, SIZE, COMPUTER) ||
                    CheckDiagonal(1, board, SIZE, COMPUTER) ||
                    CheckDiagonal(-1, board, SIZE, COMPUTER)) { return COMPUTER; }

                else {
                    if (IsFull()) {
                        return NONE;
                    }
                }
            }


        }
        return GameON;

    }

    bool GameState::GameOver() {

        if (!IsFull() || WhoWon() == 2) {
            return false;
            }
        return true;
    }

}








