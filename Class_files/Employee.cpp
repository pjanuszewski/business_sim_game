#include "Employee.h"
#include "RandomNameGenerator.hpp"

void Employee::set_name()
{
    name = get_random_name();
}

std::string Employee::get_name() const
{
    return name;
}

double Employee::get_salary() const
{
    return salary;
}

int Employee::get_number_of_employees()
{
    return number_of_employees;
}

void Employee::set_salary(double salary_value)
{
    salary = salary_value;
}