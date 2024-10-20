#pragma once
#include "Figure.h"
#include <utility>

class Circle : public Figure
{
private:    
    int m_radius;
    int m_id;
    std::pair<int, int> m_position;
    FigureType m_type;
public:
    Circle(const std::pair<int, int> position, int radius);
    ~Circle() override { };
    void move(int x, int y) override;
    std::pair<int, int> getPosition() const { return m_position; }
    int getRadius() const { return m_radius; }
};