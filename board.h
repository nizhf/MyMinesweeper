#ifndef BOARD_H
#define BOARD_H

#include <ctime>
#include <stdlib.h>

class Board
{
public:
    //construction functions
    /**
     * @brief create a new board with easy difficulty and standart settings for easy
     */
    Board();

    /**
     * @brief create a new board with costum defined size and count of mines
     * @param maxX
     * @param maxY
     * @param mineCountTotal
     */
    Board(int maxX, int maxY, int mineCountTotal);

    /**
     * @brief create a new board with selected difficulty and standard settings
     * @param difficulty
     */
    Board(int difficulty);

    ~Board();


    //Attributes
    void setMineCountTotal(int mineCount);
    int getMineCountTotal() const;

    void setMaxX(int maxX);
    int getMaxX() const;

    void setMaxY(int maxY);    
    int getMaxY() const;

    void setDifficulty(int difficulty);
    int getDifficulty() const;

    int getMineLeft() const;

    /**
     * @brief Only For Replays
     * @param grids
     */
    void setBoardGrid(int *grids, int difficulty);

    /**
     * @brief statusAt
     * @param x
     * @param y
     * @return 1 normal, 2 clicked, 3 flag, 4 flag false, 5 game over boom
     */
    int statusAt(int x, int y) const;

    /**
     * @brief mineCountAt
     * @param x
     * @param y
     * @return count of mines at (x,y)
     */
    int mineCountAt(int x, int y) const;

    /**
     * @brief valueAt
     * @param x
     * @param y
     * @return 0 none, 1-8 mines around, 9 mine
     */
    int valueAt(int x, int y) const;

    /**
     * @brief getGameStatus
     * @return 0 wait for start, 1 started, 2 win, 3 lose
     */
    int getGameStatus() const;



    //board operations
    /**
     * @brief reset the board to unclicked status. If startNoChange, then just close all grids, otherwise like initialize the board
     * @param startNoChange
     */
    void resetBoard(bool startNoChange);
    void initBoard();
    /**
     * @brief check if all grids with no mines are correctly digged
     * @return true - end, false - not end
     */
    bool isGameEnd();

    /**
     * @brief generate a board with count of mines according the settings at random positions, the 3x3 grids around (x, y) contain no mines
     * @param x
     * @param y
     */
    void generateBoard(int x, int y);

    /**
     * @brief start a new game with first clicked grid (x, y)
     * @param x
     * @param y
     */
    void startGame(int x, int y);

    /**
     * @brief set the game status to wait for start and reset the board
     * @param startNoChange
     */
    void newGame(bool startNoChange = false);

    /**
     * @brief set (x, y) to clicked. If it is a mine, game over, or if it is a blank grid, then dig all grids around (left click)
     * @param x
     * @param y
     */
    void dig(int x, int y);

    /**
     * @brief set a flag at (x, y), if possible (right click)
     * @param x
     * @param y
     */
    void setFlag(int x, int y);

    /**
     * @brief if flags equals mines, dig all grids around
     * @param x
     * @param y
     */
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