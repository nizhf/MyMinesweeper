#ifndef STATISTICDATA_H
#define STATISTICDATA_H


class StatisticData
{
public:
    StatisticData();
    ~StatisticData();

    enum Difficulty {
        Easy,
        Normal,
        Hard
    };

    struct data {
        int win, lose;
        int minTimeInMsec[5];
        int minTimeGameDay[5];
        int minTimeGameMonth[5];
        int minTimeGameYear[5];
        int totalTimeInMsec;
        int maxWinningStreak, maxLosingStreak;
        int streakNow;
        bool streakWin;
        int gameNP;
    };

    int getMinTimeInMsec(int index, Difficulty diff) const;
    int getMinTimeDay(int index, Difficulty diff) const;
    int getMinTimeMonth(int index, Difficulty diff) const;
    int getMinTimeYear(int index, Difficulty diff) const;
    void addMinTimeGame(int timeInMsec, int day, int month, int year, Difficulty diff);

    int getWin(Difficulty diff) const;
    void setWin(int value, Difficulty diff);

    int getLose(Difficulty diff) const;
    void setLose(int value, Difficulty diff);

    int getTotalTimeInMsec(Difficulty diff) const;
    void setTotalTimeInMsec(int value, Difficulty diff);

    int getMaxWinningStreak(Difficulty diff) const;
    void setMaxWinningStreak(int value, Difficulty diff);

    int getMaxLosingStreak(Difficulty diff) const;
    void setMaxLosingStreak(int value, Difficulty diff);

    int getStreakNow(Difficulty diff) const;
    void setStreakNow(int value, Difficulty diff);

    bool getStreakWin(Difficulty diff) const;
    void setStreakWin(bool value, Difficulty diff);

    int getGameNP(Difficulty diff) const;
    void setGameNP(int value, Difficulty diff);

    void clear(Difficulty diff);


    int getTotalTimeInMsec() const;
    int getTotalWin() const;
    int getTotalLose() const;

private:
    data dataEasy, dataNormal, dataHard;
};

#endif // STATISTICDATA_H