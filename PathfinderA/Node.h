#pragma once
#include "Location.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Node
{
    // current position
    int rPos;
    int cPos;

    // total distance already travelled to reach the node
    int GValue;

    // FValue = GValue + remaining distance estimate
    int FValue;  // smaller FValue gets priority

public:
    Node(const Location& loc, int g, int f)
    {
        rPos = loc.row; cPos = loc.col; GValue = g; FValue = f;
    }

    Location getLocation() const { return Location(rPos, cPos); }
    int getGValue() const { return GValue; }
    int getFValue() const { return FValue; }

    void calculateFValue(const Location& locDest)
    {
        FValue = GValue + getHValue(locDest) * 10;
    }


    void updateGValue(const int& i) // i: direction
    {
        GValue += (4 == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
    }

    // Estimation function for the remaining distance to the goal.
    const int& getHValue(const Location& locDest) const
    {
        static int rd, cd, d;
        rd = locDest.row - rPos;
        cd = locDest.col - cPos;

        // Euclidian Distance
        // d = static_cast<int>(sqrt((double)(rd*rd+cd*cd)));

        // Manhattan distance
        d = abs(rd) + abs(cd);

        // Chebyshev distance
        //d = max(abs(rd), abs(cd));

        return(d);
    }

    // Determine FValue (in the priority queue)
    friend bool operator<(const Node& a, const Node& b)
    {
        return a.getFValue() > b.getFValue();
    }
};