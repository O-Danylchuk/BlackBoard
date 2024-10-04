class BlackBoard
{
public:
    BlackBoard(int height, int width);
    ~BlackBoard();

    void display() const;
    void clearBoard();
private:
    int m_height;
    int m_width;
    char** m_board;
};
