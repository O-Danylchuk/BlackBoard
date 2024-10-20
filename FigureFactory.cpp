#include "FigureFactory.h"
#include <iostream>
#include "Figure.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Line.h"
#include <stdexcept>
#include <memory>
#include <utility>
#include <iostream>

std::unique_ptr<Figure> FigureFactory::createFigure(const Figure::FigureType type, const Figure::Color color, std::pair<int, int>& position, int firstVal, int secondVal) {
    std::unique_ptr<Figure> figure;

    switch (type) {
        case Figure::FigureType::Circle:
            figure = std::make_unique<Circle>(position, firstVal); 
            break;
        case Figure::FigureType::Square:
            figure = std::make_unique<Square>(position, firstVal); 
            break;
        case Figure::FigureType::Triangle:
            figure = std::make_unique<Triangle>(position, firstVal); 
            break;
        case Figure::FigureType::Line:
            figure = std::make_unique<Line>(position, firstVal); 
            break;
        default:
            throw std::invalid_argument("Unsupported shape type");
    }

    figure->setId(setID());
    figure->setType(type);
    figure->setColor(color);

    return figure;
}
