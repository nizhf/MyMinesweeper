#include "board.h"

Board::Board()
{
    setDifficulty(1);
    initBoard();
}

Board::Board(int maxX, int maxY, int mineCountTotal) : maxX(maxX), maxY(maxY), mineCountTotal(mineCountTotal) {
    this->difficulty = 4;
    initBoard();
}

Board::Board(int difficulty) {
    setDifficulty(difficulty);
    initBoard();
}

Board::~Board() {
    delete[] gridStatus;
}

void Board::initBoard() {
    gridStatus = new int*[maxX];
    for (int x = 0; x < maxX; x++) {
        gridStatus[x] = new int[maxY];
        for (int y = 0; y < maxY; y++) {
            gridStatus[x][y] = 10;
        }
    }
    mineLeft = mineCountTotal;
    gridLeft = maxX * maxY - mineCountTotal;
    gameStatus = 0;
    startNoChange = false;
}

void Board::resetBoard(bool startNoChange) {
    if (startNoChange) {
        for (int x = 0; x < maxX; x++) {
            for (int y = 0; y < maxY; y++) {
                int temp = gridStatus[x][y];
                gridStatus[x][y] = temp % 10 + 10;
            }
        }
        mineLeft = mineCountTotal;
        gridLeft = maxX * maxY - mineCountTotal;
    }
    else {
        for (int x = 0; x < maxX; x++) {
            for (int y = 0; y < maxY; y++) {
                gridStatus[x][y] = 10;
            }
        }
        mineLeft = mineCountTotal;
        gridLeft = maxX * maxY - mineCountTotal;
    }
}

void Board::setMineCountTotal(int mineCount) {
    this->mineCountTotal = mineCount;
}

int Board::getMineCountTotal() const {
    return this->mineCountTotal;
}

void Board::setMaxX(int maxX) {
    this->maxX = maxX;
}

int Board::getMaxX() const {
    return this->maxX;
}

void Board::setMaxY(int maxY) {
    this->maxY = maxY;
}

int Board::getMaxY() const {
    return this->maxY;
}

void Board::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
    switch (difficulty) {
    case 1:
        this->setMaxX(easyMode.maxX);
        this->setMaxY(easyMode.maxY);
        this->setMineCountTotal(easyMode.mineCountTotal);
        break;
    case 2:
        this->setMaxX(normalMode.maxX);
        this->setMaxY(normalMode.maxY);
        this->setMineCountTotal(normalMode.mineCountTotal);
        break;
    case 3:
        this->setMaxX(hardMode.maxX);
        this->setMaxY(hardMode.maxY);
        this->setMineCountTotal(hardMode.mineCountTotal);
        break;
    default:
        break;
    }
}

int Board::getDifficulty() const {
    return this->difficulty;
}

int Board::getMineLeft() const {
    return this->mineLeft;
}

int Board::statusAt(int x, int y) const {
    return this->gridStatus[x][y] / 10;
}

int Board::mineCountAt(int x, int y) const {
    return this->gridStatus[x][y] % 10;
}

int Board::valueAt(int x, int y) const {
    return this->gridStatus[x][y];
}

int Board::getGameStatus() const {
    return this->gameStatus;
}

void Board::newGame(bool startNoChange) {
    resetBoard(startNoChange);
    this->startNoChange = startNoChange;
    gameStatus = 0;
}

void Board::startGame(int x, int y) {
    gameStatus = 1;
    generateBoard(x, y);
    dig(x, y);
}

void Board::generateBoard(int x, int y) {
    //random generate mines
    srand((unsigned)time(NULL));
    bool *mineAlready = new bool[maxX * maxY]; //matrix to record wheather a grid has already a mine
    int mineCount = 0;
    int temp = 0;
    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            mineAlready[i * maxY + j] = false;
        }
    }
    //guarantee grids at the position first digged are not mines
//    if (difficulty == 1)
//        mineAlready[x * maxY + y] = true;
//    else {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY) {
                mineAlready[(x + i) * maxY + y + j] = true;
            }
        }
    }
//    }
    while (mineCount < mineCountTotal) {
        temp = rand() % (maxX * maxY);
        if (mineAlready[temp]) {
            continue;
        }
        int tempX = temp / maxY;
        int tempY = temp % maxY;
        //first digit: 1 normal, second digit: 9 mine
        gridStatus[tempX][tempY] = 19;
        mineAlready[temp] = true;
        mineCount++;
    }

    //generate the count of mines around a grid
    for (int x1 = 0; x1 < maxX; x1++) {
        for (int y1 = 0; y1 < maxY; y1++) {
            if (gridStatus[x1][y1] != 19) {
                int mineCountGrid = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (x1 + i >= 0 && x1 + i < maxX && y1 + j >= 0 && y1 + j < maxY) {
                            if (gridStatus[x1 + i][y1 + j] == 19) {
                                mineCountGrid++;
                            }
                        }
                    }
                }
                gridStatus[x1][y1] = 10 + mineCountGrid;
            }
        }
    }
    mineLeft = mineCountTotal;
    gridLeft = maxX * maxY - mineCountTotal;
    delete mineAlready;
}

void Board::dig(int x, int y) {
    if (gameStatus == 0 && !startNoChange) {
        startGame(x, y);
        return;
    }

    if (gameStatus == 2) return;
    if (gameStatus == 3) return;

    //first digit: 1 normal, 2 clicked, 3 flag, 4 flag false, 5 game over boom
    //second digit: 0 none, 1-8 mines around, 9 mine
    int temp = gridStatus[x][y];
    if (temp / 10 == 1) {
        //set this grid to clicked status
        gridStatus[x][y] = temp % 10 + 20;

        //game over
        if (temp % 10 == 9) {
            for (int x1 = 0; x1 < maxX; x1++) {
                for (int y1 = 0; y1 < maxY; y1++) {
                    int temp1 = gridStatus[x1][y1];
                    //all mines boom
                    if (temp1 % 10 == 9) {
                        if (temp1 / 10 == 1 || temp1 / 10 == 3) {
                            gridStatus[x1][y1] = temp1 % 10 + 50;
                        }
                    }
                    //show incorrect flags
                    else if (temp1 / 10 == 3) {
                        gridStatus[x1][y1] = temp1 % 10 + 40;
                    }
                }
            }
            gameStatus = 3;
            return;
        }

        gridLeft--;
        //check game win
        if (isGameEnd()) {
            gameStatus = 2;
            return;
        }

        gameStatus = 1;
        //no mines around: iterative dig all grids around
        if (temp % 10 == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY) {
                        dig(x + i, y + j);
                    }
                }
            }
            return;
        }



    }
}

void Board::setFlag(int x, int y) {
    if (gameStatus != 1) return;
    int temp = gridStatus[x][y];
    //set flag
    if (temp / 10 == 1) {
        gridStatus[x][y] = temp % 10 + 30;
        mineLeft--;
        return;
    }
    //remove flags
    if (temp / 10 == 3) {
        gridStatus[x][y] = temp % 10 + 10;
        mineLeft++;
        return;
    }
}

void Board::doubleClick(int x, int y) {
    //first digit: 1 normal, 2 clicked, 3 flag, 4 flag false, 5 game over boom
    //second digit: 0 none, 1-8 mines around, 9 mine
    if (gameStatus == 1) {
        int temp = gridStatus[x][y];
        if (temp / 10 == 2) {
            int mineMax = temp % 10;
            //count all flags around the grid
            int flagCount = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY) {
                        if (gridStatus[x + i][y + j] / 10 == 3) {
                            flagCount++;
                        }
                    }
                }
            }
            //if count of flags equals count of mines (all mines around detected), then dig all possible grids nearby
            if (mineMax == flagCount) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (gameStatus == 1 && x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY) {
                            dig(x + i, y + j);
                        }
                    }
                }
            }
        }
    }
}

bool Board::isGameEnd() {
    if (gridLeft == 0) {
        for (int x = 0; x < maxX; x++) {
            for (int y = 0; y < maxY; y++) {
                if (gridStatus[x][y] % 10 != 9 && gridStatus[x][y] / 10 != 2)
                    return false;
            }
        }
        return true;
    }
    return false;
}

void Board::setBoardGrid(int *grids, int difficulty) {
    this->setDifficulty(difficulty);
    initBoard();
    for (int i = 0; i < mineCountTotal; i++) {
        gridStatus[grids[i] % maxY][grids[i] / maxY] = 19;
    }
    //calculate count of mines
    for (int x1 = 0; x1 < maxX; x1++) {
        for (int y1 = 0; y1 < maxY; y1++) {
            if (gridStatus[x1][y1] != 19) {
                int mineCountGrid = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (x1 + i >= 0 && x1 + i < maxX && y1 + j >= 0 && y1 + j < maxY) {
                            if (gridStatus[x1 + i][y1 + j] == 19) {
                                mineCountGrid++;
                            }
                        }
                    }
                }
                gridStatus[x1][y1] = 10 + mineCountGrid;
            }
        }
    }
    mineLeft = mineCountTotal;
    gridLeft = maxX * maxY - mineCountTotal;
}

