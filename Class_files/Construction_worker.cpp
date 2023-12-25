#include "Construction_worker.h"
#include <iostream>
#include <cstdlib>

// Initialize static member
int Construction_worker::number_of_construction_workers = 0;

Construction_worker::Construction_worker()
{
    set_name();
    set_salary(600);
    unique_quality = rand() % 20;
    number_of_construction_workers++;
    number_of_employees++;
}

double Construction_worker::get_unique_quality() const
{
    return unique_quality;
}

void Construction_worker::print() const
{
    std::cout << "Name of construction worker: " << get_name() << "\n";
    std::cout << "salary (PLN): " << get_salary() << "\n";
    std::cout << "Shoe size: " << get_unique_quality() << "\n";
}

int Construction_worker::get_number_of_construction_workers()
{
    return number_of_construction_workers;
}