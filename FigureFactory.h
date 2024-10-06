#pragma once
#include "Figure.h"
#include <string>
#include <vector>
#include <memory>

class FigureFactory
{
public:
    std::unique_ptr<Figure> createFigure(Figure::FigureType type, std::pair<int, int>& position, int firstVal, int secondVal = 0);
    std::vector<std::string> getSupportedShapes() const {
        return { "Circle, (Coordinates, Radius)", "Square, (Coordinates, height)", "Triangle, (Coordinates, height, base)" };
    }
    ~FigureFactory() {}
private:
    std::vector<std::unique_ptr<Figure>> m_figures;
};