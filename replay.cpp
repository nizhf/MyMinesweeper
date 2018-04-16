#include "replay.h"

Replay::Replay()
{
    output = "";
}

void Replay::addGame(int diff, Board *board) {
    this->difficulty = diff;
    for (int x = 0; x < board->getMaxX(); x++) {
        for (int y = 0; y < board->getMaxY(); y++) {
            if (board->valueAt(x, y) % 10 == 9) {
                minePosition.push_back(x * board->getMaxX() + y);
            }
        }
    }
}

std::string Replay::getString() const {
    return output;
}

int Replay::getCurrentIndex() const
{
    return currentIndex;
}

void Replay::setCurrentIndex(int value)
{
    if (value < (signed)moves.size())
        currentIndex = value;
}

int Replay::getCountMoves() const
{
    return moves.size();
}

struct move Replay::currentMove() {
    if (currentIndex >= 0 && currentIndex < (signed)moves.size()) {
        return moves[currentIndex];
    }
    return {-1, -1, -1};
}

struct move Replay::nextMove() {
    currentIndex++;
    if (currentIndex < (signed)moves.size()) {
        return moves[currentIndex];
    }
    currentIndex--;
    return {-1, -1, -1};
}

struct move Replay::lastMove() {
    currentIndex--;
    if (currentIndex >= 0) {
        return moves[currentIndex];
    }
    currentIndex++;
    return {-1, -1, -1};
}

std::vector<int> Replay::getMinePosition() const
{
    return minePosition;
}

int Replay::getDifficulty() const
{
    return difficulty;
}

void Replay::setDifficulty(int value)
{
    difficulty = value;
}

void Replay::clearStream() {
    minePosition.clear();
    moves.clear();
    difficulty = -1;
    currentIndex = -1;
    this->output.clear();
}

void Replay::addMove(int x, int y, int moveType) {
    move currentMove = {x, y, moveType};
    moves.push_back(currentMove);
}

bool Replay::save(std::string filename) {
    std::ofstream fileout;
    fileout.open(filename);

    char str[16];
    std::sprintf(str, "%04X", difficulty);
    output += str;

    for (auto iter = minePosition.begin(); iter != minePosition.end(); iter++) {
        std::sprintf(str, "%04X", *iter);
        output += str;
    }

    for (auto iter2 = moves.begin(); iter2 != moves.end(); iter2++) {
        std::sprintf(str, "%02X%02X%04X", iter2->x, iter2->y, iter2->moveType);
        output += str;
    }

    fileout << output;
    fileout.close();

    return true;
}

bool Replay::load(std::string filename) {
    clearStream();

    std::ifstream filein;
    filein.open(filename);

    std::string input;
    filein >> input;

    filein.close();

    int difficulty = std::stoi(input.substr(0, 3), 0, 16);
    int mineCount = 0;
    switch (difficulty) {
    case 1:
        mineCount = 10;
        break;
    case 2:
        mineCount = 50;
        break;
    case 3:
        mineCount = 99;
        break;
    default:
        break;
    }

    std::string strMine = input.substr(4, mineCount * 4 + 3);
    std::string strMove = input.substr(mineCount * 4 + 4, input.size() - 1);

    for (int i = 0; i < mineCount; i++) {
        int pos = std::stoi(strMine.substr(4 * i, 4 * i + 3), 0, 16);
        minePosition.push_back(pos);
    }

    int i_move = 0;
    while (i_move * 8 < (signed)strMove.size()) {
        int x = std::stoi(strMove.substr(8 * i_move, 8 * i_move + 1), 0, 16);
        int y = std::stoi(strMove.substr(8 * i_move + 2, 8 * i_move + 3), 0, 16);
        int moveType = std::stoi(strMove.substr(8 * i_move + 4, 8 * i_move + 7), 0, 16);
        struct move cMove = {x, y, moveType};
        moves.push_back(cMove);
    }

    return true;
}
