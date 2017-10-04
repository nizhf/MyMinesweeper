#include "statisticdata.h"

StatisticData::StatisticData()
{
    for (int i = 0; i < 5; i++) {
        dataEasy.minTimeInMsec[i] = -1;
        dataNormal.minTimeInMsec[i] = -1;
        dataHard.minTimeInMsec[i] = -1;
    }
}

int StatisticData::getMinTimeInMsec(int index, Difficulty diff) const {
    try {
        switch (diff) {
        case Easy:
            return dataEasy.minTimeInMsec[index];
            break;
        case Normal:
            return dataNormal.minTimeInMsec[index];
            break;
        case Hard:
            return dataHard.minTimeInMsec[index];
            break;
        default:
            return 0;
            break;
        }
    }
    catch (...) {

    }
}

int StatisticData::getMinTimeDay(int index, Difficulty diff) const {
    try {
        switch (diff) {
        case Easy:
            return dataEasy.minTimeGameDay[index];
            break;
        case Normal:
            return dataNormal.minTimeGameDay[index];
            break;
        case Hard:
            return dataHard.minTimeGameDay[index];
            break;
        default:
            return 0;
            break;
        }
    }
    catch (...) {

    }
}

int StatisticData::getMinTimeMonth(int index, Difficulty diff) const {
    try {
        switch (diff) {
        case Easy:
            return dataEasy.minTimeGameMonth[index];
            break;
        case Normal:
            return dataNormal.minTimeGameMonth[index];
            break;
        case Hard:
            return dataHard.minTimeGameMonth[index];
            break;
        default:
            return 0;
            break;
        }
    }
    catch (...) {

    }
}

int StatisticData::getMinTimeYear(int index, Difficulty diff) const {
    try {
        switch (diff) {
        case Easy:
            return dataEasy.minTimeGameYear[index];
            break;
        case Normal:
            return dataNormal.minTimeGameYear[index];
            break;
        case Hard:
            return dataHard.minTimeGameYear[index];
            break;
        default:
            return 0;
            break;
        }
    }
    catch (...) {

    }
}

void StatisticData::addMinTimeGame(int timeInMsec, int day, int month, int year, Difficulty diff) {
    try {
        switch (diff) {
        case Easy:
            for (int i = 0; i < 5; i++) {
                if (timeInMsec <= dataEasy.minTimeInMsec[i] || dataEasy.minTimeInMsec[i] == -1) {
                    for (int j = 3; j >= i; j--) {
                        dataEasy.minTimeInMsec[j + 1] = dataEasy.minTimeInMsec[j];
                        dataEasy.minTimeGameDay[j + 1] = dataEasy.minTimeGameDay[j];
                        dataEasy.minTimeGameMonth[j + 1] = dataEasy.minTimeGameMonth[j];
                        dataEasy.minTimeGameYear[j + 1] = dataEasy.minTimeGameYear[j];
                    }
                    dataEasy.minTimeInMsec[i] = timeInMsec;
                    dataEasy.minTimeGameDay[i] = day;
                    dataEasy.minTimeGameMonth[i] = month;
                    dataEasy.minTimeGameYear[i] = year;
                    break;
                }
            }
            break;
        case Normal:
            for (int i = 0; i < 5; i++) {
                if (timeInMsec <= dataNormal.minTimeInMsec[i] || dataNormal.minTimeInMsec[i] == -1) {
                    for (int j = 3; j >= i; j--) {
                        dataNormal.minTimeInMsec[j + 1] = dataNormal.minTimeInMsec[j];
                        dataNormal.minTimeGameDay[j + 1] = dataNormal.minTimeGameDay[j];
                        dataNormal.minTimeGameMonth[j + 1] = dataNormal.minTimeGameMonth[j];
                        dataNormal.minTimeGameYear[j + 1] = dataNormal.minTimeGameYear[j];
                    }
                    dataNormal.minTimeInMsec[i] = timeInMsec;
                    dataNormal.minTimeGameDay[i] = day;
                    dataNormal.minTimeGameMonth[i] = month;
                    dataNormal.minTimeGameYear[i] = year;
                    break;
                }
            }
            break;
        case Hard:
            for (int i = 0; i < 5; i++) {
                if (timeInMsec <= dataHard.minTimeInMsec[i] || dataHard.minTimeInMsec[i] == -1) {
                    for (int j = 3; j >= i; j--) {
                        dataHard.minTimeInMsec[j + 1] = dataHard.minTimeInMsec[j];
                        dataHard.minTimeGameDay[j + 1] = dataHard.minTimeGameDay[j];
                        dataHard.minTimeGameMonth[j + 1] = dataHard.minTimeGameMonth[j];
                        dataHard.minTimeGameYear[j + 1] = dataHard.minTimeGameYear[j];
                    }
                    dataHard.minTimeInMsec[i] = timeInMsec;
                    dataHard.minTimeGameDay[i] = day;
                    dataHard.minTimeGameMonth[i] = month;
                    dataHard.minTimeGameYear[i] = year;
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
    catch (...) {

    }
}

int StatisticData::getTotalTimeInMsec() const
{
    return dataEasy.totalTimeInMsec + dataNormal.totalTimeInMsec + dataHard.totalTimeInMsec;
}

int StatisticData::getTotalWin() const
{
    return dataEasy.win + dataNormal.win + dataHard.win;
}

int StatisticData::getTotalLose() const
{
    return dataEasy.lose + dataNormal.lose + dataHard.lose;
}

int StatisticData::getWin(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.win;
        break;
    case Normal:
        return dataNormal.win;
        break;
    case Hard:
        return dataHard.win;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setWin(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.win = value;
        break;
    case Normal:
        dataNormal.win = value;
        break;
    case Hard:
        dataHard.win = value;
        break;
    default:
        break;
    }
}

int StatisticData::getLose(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.lose;
        break;
    case Normal:
        return dataNormal.lose;
        break;
    case Hard:
        return dataHard.lose;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setLose(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.lose = value;
        break;
    case Normal:
        dataNormal.lose = value;
        break;
    case Hard:
        dataHard.lose = value;
        break;
    default:
        break;
    }
}

int StatisticData::getTotalTimeInMsec(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.totalTimeInMsec;
        break;
    case Normal:
        return dataNormal.totalTimeInMsec;
        break;
    case Hard:
        return dataHard.totalTimeInMsec;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setTotalTimeInMsec(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.totalTimeInMsec = value;
        break;
    case Normal:
        dataNormal.totalTimeInMsec = value;
        break;
    case Hard:
        dataHard.totalTimeInMsec = value;
        break;
    default:
        break;
    }
}

int StatisticData::getMaxWinningStreak(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.maxWinningStreak;
        break;
    case Normal:
        return dataNormal.maxWinningStreak;
        break;
    case Hard:
        return dataHard.maxWinningStreak;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setMaxWinningStreak(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.maxWinningStreak = value;
        break;
    case Normal:
        dataNormal.maxWinningStreak = value;
        break;
    case Hard:
        dataHard.maxWinningStreak = value;
        break;
    default:
        break;
    }
}

int StatisticData::getMaxLosingStreak(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.maxLosingStreak;
        break;
    case Normal:
        return dataNormal.maxLosingStreak;
        break;
    case Hard:
        return dataHard.maxLosingStreak;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setMaxLosingStreak(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.maxLosingStreak = value;
        break;
    case Normal:
        dataNormal.maxLosingStreak = value;
        break;
    case Hard:
        dataHard.maxLosingStreak = value;
        break;
    default:
        break;
    }
}

int StatisticData::getStreakNow(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.streakNow;
        break;
    case Normal:
        return dataNormal.streakNow;
        break;
    case Hard:
        return dataHard.streakNow;
        break;
    default:
        return 0;
        break;
    }
}

void StatisticData::setStreakNow(int value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.streakNow = value;
        break;
    case Normal:
        dataNormal.streakNow = value;
        break;
    case Hard:
        dataHard.streakNow = value;
        break;
    default:
        break;
    }
}

bool StatisticData::getStreakWin(Difficulty diff) const
{
    switch (diff) {
    case Easy:
        return dataEasy.streakWin;
        break;
    case Normal:
        return dataNormal.streakWin;
        break;
    case Hard:
        return dataHard.streakWin;
        break;
    default:
        return false;
        break;
    }
}

void StatisticData::setStreakWin(bool value, Difficulty diff)
{
    switch (diff) {
    case Easy:
        dataEasy.streakWin = value;
        break;
    case Normal:
        dataNormal.streakWin = value;
        break;
    case Hard:
        dataHard.streakWin = value;
        break;
    default:
        break;
    }
}

int StatisticData::getGameNP(Difficulty diff) const {
    switch (diff) {
    case Easy:
        return dataEasy.gameNP;
        break;
    case Normal:
        return dataNormal.gameNP;
        break;
    case Hard:
        return dataHard.gameNP;
        break;
    default:
        return false;
        break;
    }
}

void StatisticData::setGameNP(int value, Difficulty diff) {
    switch (diff) {
    case Easy:
        dataEasy.gameNP = value;
        break;
    case Normal:
        dataNormal.gameNP = value;
        break;
    case Hard:
        dataHard.gameNP = value;
        break;
    default:
        break;
    }
}

void StatisticData::clear(Difficulty diff) {
    switch (diff) {
    case Easy:
        dataEasy.win = 0;
        dataEasy.lose = 0;
        dataEasy.totalTimeInMsec = 0;
        dataEasy.maxWinningStreak = 0;
        dataEasy.maxLosingStreak = 0;
        dataEasy.streakNow = 0;
        dataEasy.streakWin = false;
        dataEasy.gameNP = 0;
        for (int i = 0; i < 5; i++) {
            dataEasy.minTimeInMsec[i] = -1;
            dataEasy.minTimeGameYear[i] = -1;
            dataEasy.minTimeGameMonth[i] = -1;
            dataEasy.minTimeGameDay[i] = -1;
        }
        break;
    case Normal:
        dataNormal.win = 0;
        dataNormal.lose = 0;
        dataNormal.totalTimeInMsec = 0;
        dataNormal.maxWinningStreak = 0;
        dataNormal.maxLosingStreak = 0;
        dataNormal.streakNow = 0;
        dataNormal.streakWin = false;
        dataNormal.gameNP = 0;
        for (int i = 0; i < 5; i++) {
            dataNormal.minTimeInMsec[i] = -1;
            dataNormal.minTimeGameYear[i] = -1;
            dataNormal.minTimeGameMonth[i] = -1;
            dataNormal.minTimeGameDay[i] = -1;
        }
        break;
    case Hard:
        dataHard.win = 0;
        dataHard.lose = 0;
        dataHard.totalTimeInMsec = 0;
        dataHard.maxWinningStreak = 0;
        dataHard.maxLosingStreak = 0;
        dataHard.streakNow = 0;
        dataHard.streakWin = false;
        dataHard.gameNP = 0;
        for (int i = 0; i < 5; i++) {
            dataHard.minTimeInMsec[i] = -1;
            dataHard.minTimeGameYear[i] = -1;
            dataHard.minTimeGameMonth[i] = -1;
            dataHard.minTimeGameDay[i] = -1;
        }
        break;
    default:
        break;
    }
}
