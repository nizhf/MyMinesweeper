#ifndef BOARD_H
#define BOARD_H

#include <ctime>
#include <stdlib.h>

class Board
{
public:
    Board();
    Board(int maxX, int maxY, int mineCountTotal);
    Board(int difficulty);
    ~Board();

    void setMineCountTotal(int mineCount);
    int getMineCountTotal() const;
    void setMaxX(int maxX);
    int getMaxX() const;
    void setMaxY(int maxY);
    int getMaxY() const;
    void setDifficulty(int difficulty);
    int getDifficulty() const;
    int getMineLeft() const;
    int statusAt(int x, int y) const;
    int mineCountAt(int x, int y) const;
    int valueAt(int x, int y) const;
    int getGameStatus() const;

    void resetBoard(bool startNoChange);
    void initBoard();
    bool isGameEnd();
    void generateBoard(int x, int y);

    void startGame(int x, int y);
    void newGame(bool startNoChange = false);
    void dig(int x, int y);
    void setFlag(int x, int y);
    void doubleClick(int x, int y);

private:
    //properties
    int difficulty;
    int maxX, maxY;
    int mineCountTotal;
    //first digit: 1 normal, 2 clicked, 3 flag, 4 flag false, 5 game over boom
    //second digit: 0 none, 1-8 mines around, 9 mine
    int **gridStatus;
    //mines left (if all flags were mines)
    int mineLeft;
    //grids left (if all flags were mines)
    int gridLeft;
    //game status: 0 wait for start, 1 started, 2 win, 3 lose
    int gameStatus;
    //start no change: true - next game same board, false - new board
    bool startNoChange;


    struct setting {
        const int maxX;
        const int maxY;
        const int mineCountTotal;
    };
    setting easyMode = {9, 9, 10};
    setting normalMode = {16, 16, 40};
    setting hardMode = {30, 16, 99};

};

#endif // BOARD_H