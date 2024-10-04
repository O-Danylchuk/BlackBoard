#pragma once

class Figure
{
protected:
    std::pair<int, int> position;

public:
    Figure(const std::pair<int, int>& position) : position(position) {}

    virtual ~Figure() = default;

    virtual void draw() = 0;

    virtual void move(int x, int y)
    {
        position.first = x;
        position.second = y;
    }

    enum class FigureType 
    {
        Circle,
        Square,
        Triangle
    };
};
