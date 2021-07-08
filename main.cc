#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>
#include <thread>
#include <time.h>

int** random_state(int width, int height) {
    time_t timer;
    time(&timer);
    int** board;
    unsigned int currTime = timer;
    board = new int*[height];
    for(int i = 0; i < height; i++) {
        board[i] = new int[width];
        for(int j = 0; j < width; j++) {
            board[i][j] = rand_r(&currTime) % 2;
        }
    }

    return board;
}

int** dead_state(int width, int height) {
    int** board;
    board = new int*[height];
    for(int i = 0; i < height; i++) {
        board[i] = new int[width];
        for(int j = 0; j < width; j++) {
            board[i][j] = 0;
        }
    }

    return board;
}

void render(int** const board, int width, int height) {
    for(int i = 0; i < height; i++) {
        std::cout << "|";
        for(int j = 0; j < width; j++) {
            if(board[i][j] == 1) {
                std::cout << "<>";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << "|\n";
    }
}

int checkAliveRule(int sum) {
    if(sum == 0 || sum == 1) {
        return 0;
    }
    else if(sum == 2 || sum == 3) {
        return 1;
    }
    else if(sum > 3) {
        return 0;
    }
    else {
        return 0;
    }
}

int checkDeadRule(int sum) {
    if(sum == 3) {
        return 1;
    }
    else{
        return 0;
    }
}

void next_board_state(int** board, int width, int height) {
    int** tempBoard = new int*[height];
    for(int i = 0; i < height; i++) {
        tempBoard[i] = new int[width];
        for(int j = 0; j < width; j++) {
            //top left corner
            if(i == 0 && j == 0) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i][j+1];
                    sum += board[i+1][j];
                    sum += board[i+1][j+1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            } 

            //top edge
            else if(i == 0 && j > 0 && j < width - 1) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }
            
            //top right corner
            else if(i == 0 && j == width - 1) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            //right edge
            else if(i > 0 && i < height - 1 && j == width - 1) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            //bottom right corner
            else if(i == height - 1 && j == width - 1) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            //bottom edge
            else if(i == height - 1 && j > 0) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            //bottom left corner
            else if(i == height - 1 && j == 0) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            //left edge
            else if(i > 0 && j == 0) {
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }

            // middle stuff
            else{
                if(board[i][j] == 1){
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    tempBoard[i][j] = checkAliveRule(sum);
                }
                else{
                    int sum = 0;
                    sum += board[i-1][j];
                    sum += board[i-1][j+1];
                    sum += board[i][j+1];
                    sum += board[i+1][j+1];
                    sum += board[i+1][j];
                    sum += board[i+1][j-1];
                    sum += board[i][j-1];
                    sum += board[i-1][j-1];
                    tempBoard[i][j] = checkDeadRule(sum);
                }
            }
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            board[i][j] = tempBoard[i][j];
        }
    }
}

int main() {
    int boards[30][56] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    
    int height = 30;
    int width = 56;

    int** board = random_state(width, height);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            board[i][j] = boards[i][j];
        }
    }

    //board = dead_state(width,height);


    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        render(board, width, height);
        next_board_state(board, width, height);
    }

    return 0;
}