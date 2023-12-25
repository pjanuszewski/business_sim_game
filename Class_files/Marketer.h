#include "Employee.h"
#include <string>

class Marketer : public Employee
{
public:
    Marketer();
    int get_unique_quality() const;
    void print() const;
    static int get_number_of_marketers();
    constexpr static const double CMkt = 145;

private:
    int unique_quality;
    static int number_of_marketers;
};