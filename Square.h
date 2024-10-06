#pragma once
#include <utility>
#include "Figure.h"

class Square : public Figure
{
private:
    std::pair<int, int> m_position;
    FigureType m_type;
    int m_height;
    int m_width;
public:
    Square(const std::pair<int, int>& position, int height);
    ~Square() override = default;
    void move(int x, int y) override;
    std::pair<int, int> getPosition() const { return m_position; }
    int getHeight() const { return m_height; }
    int getWidth() const { return m_width; }
};