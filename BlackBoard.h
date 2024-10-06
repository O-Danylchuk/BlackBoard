#pragma once
#include "Figure.h"
#include <vector>
#include <memory>

class BlackBoard
{
public:
    BlackBoard(int height, int width);
    ~BlackBoard() = default;

    void display() const;
    void clearBoard();
    void listFigures();
    void addFigure(std::unique_ptr<Figure>& figure);
    void drawFigure(Figure::FigureType type, std::pair<int, int>& position, int firstVal, int secondVal);
    void undoLastFigure();
    void save(const std::string& filePath);
    void load(const std::string& filePath);
private:
    int m_height;
    int m_width;
    std::vector<std::vector<char>> m_board;
    std::vector<std::unique_ptr<Figure>> m_figures;
};
