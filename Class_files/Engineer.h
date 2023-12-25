#include "Employee.h"
#include <string>
#include <vector>

class Engineer : public Employee
{
public:
    Engineer();
    void print() const;
    std::string get_unique_quality() const;
    std::string pickRandomString(const std::vector<std::string>& strings);
    static int get_number_of_engineers();
    constexpr static const double CI = 134;

private:
    std::vector<std::string> strings = {"Robotics", "Energy", "Aviation"};
    std::string unique_quality;
    static int number_of_engineers;
};