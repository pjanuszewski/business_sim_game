#include "Employee.h"
#include <string>

class Construction_worker : public Employee
{
public:
    Construction_worker();
    double get_unique_quality() const;
    void print() const;
    static int get_number_of_construction_workers();
    constexpr static const double CR = 78;

private:
    double unique_quality;
    static int number_of_construction_workers;
};