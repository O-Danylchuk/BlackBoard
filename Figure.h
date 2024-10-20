#pragma once
#include <utility>
#include <string>

class Figure
{
protected:
    std::pair<int, int> m_position;
    int m_id;

public:
    Figure() = default;

    Figure(const std::pair<int, int>& position);

    int getId() const {
        return m_id;
    }

    void setId(int id) {
        m_id = id;
    }

    virtual ~Figure() = default;

    virtual void move(int x, int y) = 0;

    enum class Color
    {
        Red,
        Green,
        Blue,
        Yellow,
        Magenta,
        Cyan,
        White
    };

    enum class FigureType 
    {
        Circle,
        Square,
        Triangle,
        Line
    };
    
    Color m_color;
    FigureType m_type;

    void setType(FigureType type) {
        m_type = type;
    }

    void setColor(Color color) {
        m_color = color;
    }

    std::string getColor() const {
        switch (m_color) {
            case Color::Red:
                return "red";
            case Color::Green:
                return "green";
            case Color::Blue:
                return "blue";
            case Color::Yellow:
                return "yellow";
            case Color::Magenta:
                return "magenta";
            case Color::Cyan:
                return "cyan";
            case Color::White:
                return "white";
            default:
                return "Invalid color";
        }
    }
};


