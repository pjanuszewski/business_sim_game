#include "Engineer.h"
#include <iostream>
#include <random>

int Engineer::number_of_engineers = 0;

Engineer::Engineer()
{
    set_name();
    set_salary(1000);
    unique_quality = pickRandomString(strings);
    number_of_engineers++;
    number_of_employees++;
}

void Engineer::print() const
{
    std::cout << "Name of engineer: " << get_name() << "\n";
    std::cout << "salary (PLN): " << get_salary() << "\n";
    std::cout << "Education: " << get_unique_quality() << "\n";
}

std::string Engineer::get_unique_quality() const
{
    return unique_quality;
}

std::string Engineer::pickRandomString(const std::vector<std::string>& strings)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, strings.size() - 1);
    int index = dis(gen);
    return strings[index];
}

int Engineer::get_number_of_engineers()
{
    return number_of_engineers;
}