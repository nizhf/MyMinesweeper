#ifndef REPLAY_H
#define REPLAY_H

#include <stdlib.h>
#include <fstream>
#include <vector>
#include "board.h"

struct move {
    int x;
    int y;
    int moveType;
};

class Replay
{
public:
    Replay();

    bool save(std::string filename);
    bool load(std::string filename);
    void addMove(int x, int y, int moveType);
    void addGame(int diff, Board *board);
    void clearStream();
    std::string getString() const;

    int getCurrentIndex() const;
    void setCurrentIndex(int value);

    int getDifficulty() const;
    void setDifficulty(int value);

    std::vector<int> getMinePosition() const;

    int getCountMoves() const;
    struct move currentMove();
    struct move nextMove();
    struct move lastMove();

private:
    std::string output;
    std::vector<move> moves;
    std::vector<int> minePosition;
    int difficulty;
    int currentIndex;

};

#endif // REPLAY_H