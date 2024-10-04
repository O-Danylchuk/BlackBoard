#include <iostream>

class CLI 
{
public:
    void run();
    ~CLI() {}
private:
    std::string m_command;
};