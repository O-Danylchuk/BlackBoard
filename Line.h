#pragma once
#include "Figure.h"
#include <iostream>

class Line : public Figure
{
private:
    std::pair<int, int> m_position;
    FigureType m_type;
    int m_length;
    int m_id;
public:
    Line(const std::pair<int, int>& position, int length);
    ~Line() override = default;
    std::pair<int, int> getPosition() const { return m_position; }
    int getLength() const { return m_length; }
    void move(int x, int y) override;
};