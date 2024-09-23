
struct Point
{
    int x;
    int y;
};

class Figure
{
private:
    Point position;
public:
    virtual void draw() = 0;
    virtual void move(int x, int y) = 0;  

    Figure(Point position);
};

