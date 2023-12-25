#include <string>
#include <variant>

class Employee
{
public:
    void set_name();
    std::string get_name() const;
    double get_salary() const;
    static int get_number_of_employees();

protected:
    static int number_of_employees;
    void set_salary(double salary_value);
    std::variant<int, double, bool, std::string> unique_quality;

private:
    std::string name;
    double salary;  
};