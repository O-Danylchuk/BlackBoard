#include "Figure.h"
#include <utility>
#include <iostream>


class Triangle : public Figure
{
private:
    std::pair<int, int> m_position;
    int m_height;
    int m_base;
public:
    Triangle(const std::pair<int, int>& position, int height, int base);
    ~Triangle() override = default;
    void move(int x, int y) override;
    std::pair<int, int> getPosition() const { return m_position; }
    int getHeight() const { return m_height; }
    int getBase() const { return m_base; }
};