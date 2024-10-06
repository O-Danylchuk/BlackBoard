#pragma once
#include <utility>

class Figure
{
protected:
    std::pair<int, int> m_position;

public:
    Figure() = default;

    Figure(const std::pair<int, int>& position);

    virtual ~Figure() = default;

    virtual void move(int x, int y) = 0;

    enum class FigureType 
    {
        Circle,
        Square,
        Triangle,
        Line
    };
    
    FigureType type;
};
