#pragma once
#include "Figure.h"
#include <string>
#include <vector>
#include <memory>

class FigureFactory
{
public:
    std::unique_ptr<Figure> createFigure(const Figure::FigureType type, const Figure::Color color, std::pair<int, int>& position, int firstVal, int secondVal = 0);
    std::vector<std::string> getSupportedShapes() const {
        return { "Circle, (Coordinates, Radius)", "Square, (Coordinates, height)", "Triangle, (Coordinates, height)", "Line(Coordinates, lenght)" };
    }
    int setID() { return ++m_id_v; }
    void resetID() { m_id_v = 0; }
    ~FigureFactory() {}
private:
    std::vector<std::unique_ptr<Figure>> m_figures;
    int m_id_v = 0;
};