#include "BlackBoard.h"
#include <iostream>
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"


BlackBoard::BlackBoard(int height, int width) : m_height(height), m_width(width), m_board(height, std::vector<char>(width, ' ')) {}

void BlackBoard::display() const {
    std::cout << "+";
    for (int i = 0; i < m_width; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    for (int i = 0; i < m_height; ++i) {
        std::cout << "|";
        for (int j = 0; j < m_width; ++j) {
            std::cout << m_board[i][j];
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+";
    for (int i = 0; i < m_width; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void BlackBoard::drawFigure(Figure::FigureType type, std::pair<int, int>& position, int firstVal, int secondVal) {
    if (type == Figure::FigureType::Circle) {
        int radius = firstVal;
        int centerX = position.first;
        int centerY = position.second;

        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    int drawX = centerX + x;
                    int drawY = centerY + y;
                    if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                        m_board[drawY][drawX] = 'O';
                    }
                }
            }
        }
    } else if (type == Figure::FigureType::Square) {
        int height = firstVal;
        int width = secondVal;
        int startX = position.first;
        int startY = position.second;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int drawX = startX + x;
                int drawY = startY + y;
                if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                    m_board[drawY][drawX] = 'X';
                }
            }
        }
    } else if (type == Figure::FigureType::Triangle) {
        int height = firstVal;
        int startX = position.first;
        int startY = position.second;
        for (int x = 1; x <= height; ++x) {
            for (int y = 0; y < x; ++y) {
                int drawX = startX + x;
                int drawY = startY + y;
                if (drawX >= 0 && drawX < m_width && drawY >= 0 && drawY < m_height) {
                    m_board[drawY][drawX] = 'X';
                }
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Invalid figure type" << std::endl;
    }
}

void BlackBoard::addFigure(std::unique_ptr<Figure>& figure){
    m_figures.push_back(std::move(figure));
}

void BlackBoard::clearBoard() {
    for (auto& row : m_board) {
        std::fill(row.begin(), row.end(), ' ');
    }
}

void BlackBoard::listFigures() {
    for (const auto& figure : m_figures) {
        switch (figure->type) {
            case Figure::FigureType::Circle: {
                Circle* circle = dynamic_cast<Circle*>(figure.get());
                if (circle) {
                    std::cout << "Circle: Position (" << circle->getPosition().first << ", " << circle->getPosition().second 
                              << "), Radius: " << circle->getRadius() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Square: {
                Square* square = dynamic_cast<Square*>(figure.get());
                if (square) {
                    std::cout << "Square: Position (" << square->getPosition().first << ", " << square->getPosition().second 
                              << "), Width: " << square->getWidth() << ", Height: " << square->getHeight() << std::endl;
                }
                break;
            }
            case Figure::FigureType::Triangle: {
                Triangle* triangle = dynamic_cast<Triangle*>(figure.get());
                if (triangle) {
                    std::cout << "Triangle: Position (" << triangle->getPosition().first << ", " << triangle->getPosition().second 
                              << ")" << ", Height: " << triangle->getHeight() << std::endl;
                }
                break;
            }
            default:
                break;
        }
    }
}