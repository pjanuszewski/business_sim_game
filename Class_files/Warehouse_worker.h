#include "Employee.h"
#include <string>

class Warehouse_worker : public Employee
{
public:
    Warehouse_worker();
    bool get_unique_quality() const;
    void print() const;
    static int get_number_of_warehouse_workers();
    constexpr static const double CMag = 123;

private:
    bool generate_random_bool();
    bool unique_quality;
    static int number_of_warehouse_workers;
};