#include <iostream>
#include "shared_ptr.hpp"

class Car
{
private:
    int m_x{};
};

int main()
{
    Shared_ptr<Car> obj;
    std::cout << obj.get_count();
    Shared_ptr<Car> obj1(new Car());
    std::cout << obj1.get_count();
}