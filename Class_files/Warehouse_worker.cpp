#include "Warehouse_worker.h"
#include <iostream>
#include <cstdlib>

// Initialize static member
int Warehouse_worker::number_of_warehouse_workers = 0;

Warehouse_worker::Warehouse_worker()
{
    set_name();
    set_salary(400);
    unique_quality = generate_random_bool();
    number_of_warehouse_workers++;
    number_of_employees++;
}

bool Warehouse_worker::get_unique_quality() const
{
    return unique_quality;
}

void Warehouse_worker::print() const
{
    std::cout << "Name of warehouse worker: " << get_name() << "\n";
    std::cout << "salary (PLN): " << get_salary() << "\n";
    std::cout << "Forklift license: " << (get_unique_quality() ? "Yes" : "No") << "\n";
}

int Warehouse_worker::get_number_of_warehouse_workers()
{
    return number_of_warehouse_workers;
}

bool Warehouse_worker::generate_random_bool()
{
    return rand() % 2 == 0;
}