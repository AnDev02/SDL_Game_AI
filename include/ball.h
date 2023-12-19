#ifndef BALL_H
#define BALL_H
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "./commonFn.h"
class ball {
public:
    int x, y, cost, value;
    bool isSelected;
    // Constructor
    ball(int _x, int _y, int _cost, int _value) : x(_x), y(_y), cost(_cost), value(_value), isSelected(false) {}
    ~ball();
    // Getter và setter (nếu cần)
    int getX() const { return x; }
    void setX(int _x) { x = _x; }

    int getY() const { return y; }
    void setY(int _y) { y = _y; }

    int getCost() const { return cost; }
    void setCost(int _cost) { cost = _cost; }

    int getValue() const { return value; }
    void setValue(int _value) { value = _value; }

    // Định nghĩa toán tử so sánh cho hàng đợi ưu tiên (min heap)
    bool operator>(const ball &other) const {
        return cost > other.cost;
    }
    bool operator==(const ball& other) const {
        return x == other.x && y == other.y && cost == other.cost && value == other.value;
    }
    void moveBall();
};


#endif