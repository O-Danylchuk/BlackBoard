#include "FigureFactory.h"
#include "Figure.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include <stdexcept>
#include <memory>
#include <utility>

void FigureFactory::createFigure(Figure& figure, Figure::FigureType type, std::pair<int, int>& position) {
    switch (type) {
        case Figure::FigureType::Circle:
            figure = Circle(position, 10);
            break;
        case Figure::FigureType::Square:
            figure = Square(position, 10, 10);
            break;
        case Figure::FigureType::Triangle:
            figure = Triangle(position, 10, 10);
            break;
        default:
            throw std::invalid_argument("Invalid figure type");
    }
}

