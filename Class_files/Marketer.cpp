#include "Marketer.h"
#include <iostream>
#include <cstdlib>

int Marketer::number_of_marketers = 0;

Marketer::Marketer()
{
    set_name();
    set_salary(500);
    unique_quality = rand() % 1001;
    number_of_marketers++;
    number_of_employees++;
}

int Marketer::get_unique_quality() const
{
    return unique_quality;
}

void Marketer::print() const
{
    std::cout << "Name of Marketer: " << get_name() << "\n";
    std::cout << "salary (PLN): " << get_salary() << "\n";
    std::cout << "Instagram followers: " << get_unique_quality() << "\n";
}

int Marketer::get_number_of_marketers()
{
    return number_of_marketers;
}