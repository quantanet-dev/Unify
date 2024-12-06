#include <iostream>
#include <string>

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Paused! Press Enter to continue...";

    std::string line;
    std::getline(std::cin, line);
    return 0;
}