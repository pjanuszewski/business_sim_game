#include "RandomNameGenerator.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <cstdlib>

class Employee
{
public:
    void set_name()
    {
        name = get_random_name();
    }
    std::string get_name() const
    {
        return name;
    }
    double get_salary() const
    {
        return salary;
    }
    static int get_number_of_employees()
    {
        return number_of_employees;
    }
    protected:
    static int number_of_employees;
    void set_salary(double salary_value)
    {
        salary = salary_value;
    }
    std::variant<int, double, bool, std::string> unique_quality;
private:
    std::string name;
    double salary;  
};

class Engineer : public Employee
{
public:
    Engineer()
    {
        set_name();
        set_salary(1000);
        number_of_engineers++;
        number_of_employees++;
    }
    void print() const
    {
        std::cout << "Name of engineer: " << get_name() << "\n";
        std::cout << "salary (PLN): " << get_salary() << "\n";
        std::cout << "Education: " << get_unique_quality() << "\n";
    }
    std::string get_unique_quality() const
    {
        return unique_quality;
    }
        std::string pickRandomString(const std::vector<std::string>& strings)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, strings.size() - 1);
        int index = dis(gen);
        return strings[index];
    }
    static int get_number_of_engineers()
    {
        return number_of_engineers;
    }
    constexpr static const double CI = 134;
private:
    std::vector<std::string> strings = {"Robotics", "Energy", "Aviation"};
    std::string unique_quality = pickRandomString(strings);
    static int number_of_engineers;
};

class Warehouse_worker : public Employee
{
public:
    Warehouse_worker()
    {
        set_name();
        set_salary(400);
        number_of_warehouse_workers++;
        number_of_employees++;
    }
    bool get_unique_quality() const
    {
        return unique_quality;
    }
    void print() const
    {
        std::cout << "Name of warehouse worker: " << get_name() << "\n";
        std::cout << "salary (PLN): " << get_salary() << "\n";
        std::cout << "Forklift license: " << get_unique_quality() << "\n";
    }
    static int get_number_of_warehouse_workers()
    {
        return number_of_warehouse_workers;
    }
    constexpr static const double CMag = 123;
private:
    bool generate_random_bool()
    {
        return rand() % 2 == 0;
    }
    bool unique_quality = generate_random_bool();
    static int number_of_warehouse_workers;
};

class Marketer : public Employee
{
public:
    Marketer()
    {
        set_name();
        set_salary(500);
        number_of_marketers++;
        number_of_employees++;
    }
    int get_unique_quality() const
    {
        return unique_quality;
    }
    void print() const
    {
        std::cout << "Name of Marketer: " << get_name() << "\n";
        std::cout << "salary (PLN): " << get_salary() << "\n";
        std::cout << "Instagram followers: " << get_unique_quality() << "\n";
    }
    static int get_number_of_marketers()
    {
        return number_of_marketers;
    }
    constexpr static const double CMkt = 145;
private:
    int unique_quality = rand() % 1001;
    static int number_of_marketers;
};

class Construction_worker: public Employee
{
public:
    Construction_worker()
    {
        set_name();
        set_salary(600);
        number_of_construction_workers++;
        number_of_employees++;
    }
    double get_unique_quality() const
    {
        return unique_quality;
    }
    void print() const
    {
        std::cout << "Name of construction worker: " << get_name() << "\n";
        std::cout << "salary (PLN): " << get_salary() << "\n";
        std::cout << "Shoe size: " << get_unique_quality() << "\n";
    }
    static int get_number_of_construction_workers()
    {
        return number_of_construction_workers;
    }
    constexpr static const double CR = 78;
private:
    double unique_quality = rand() % 20;
    static int number_of_construction_workers;
};

struct Employee_printer
{
    void operator()(const Engineer& Employee) { Employee.print();}
    void operator()(const Warehouse_worker& Employee) { Employee.print();}
    void operator()(const Marketer& Employee) { Employee.print();}
    void operator()(const Construction_worker& Employee) { Employee.print();}
};

class Credit
{
public:
    double monthly_payment;
    Credit() : credit{0}, duration{0}, current_round{0} {}
    Credit(const double& credit, const int& duration, const int&current_round) : credit{credit}, duration{duration}, current_round{current_round}
    {
        interest_rate = 0.00001*duration*credit;
        round_of_loan_taking = current_round;
    }
    double payment(const Credit& credit)
    {
        return credit.credit + credit.interest_rate;
    }
    double get_round_of_loan_taking() const
    {
        return round_of_loan_taking;
    }
    int get_duration() const
    {
        return duration;
    }
private:
    int current_round;
    int round_of_loan_taking;
    double credit{0};
    double interest_rate{0};
    int duration;
    double total_payment;
    double total_interest;
};

class Company : public Employee, public Credit
{
public:
    Company() : workers_vector(), loans(std::make_unique<Credit[]>(number_of_loans)), income_history(std::make_unique<double[]>(N)), state_of_account(100000.0)
    {
        
    }
    void print_employees() const
    {
        for (int i = 0; i < get_number_of_employees(); i++)
        {
            std::visit(Employee_printer{}, workers_vector[i]);
        }
    }
    void take_loan(double ammount, int duration, int current_round)
    {
        loans[number_of_loans] = Credit(ammount, duration, current_round);
        number_of_loans++;
    }
    void hire(std::string s)
    {
        if (s == "Engineer")
        {
            workers_vector.emplace_back(Engineer());
        }
        else if (s == "Warehouse_worker")
        {
            workers_vector.emplace_back(Warehouse_worker());
        }
        else if (s == "Marketer")
        {
            workers_vector.emplace_back(Marketer());
        }
        else if (s == "Construction_worker")
        {
            workers_vector.emplace_back(Construction_worker());
        }
    }
    void pay_salary()
    {
        current_round_salary = 0;
        for (int i = 0; i < Employee::get_number_of_employees(); i++)
        {
            current_round_salary += std::visit([](auto&& arg) { return arg.get_salary(); }, workers_vector[i]);
        }
        state_of_account -= current_round_salary;
    }
    double loan_payment(const int& current_round)
    {
        payment = 0;
        for (int i = 0; i < number_of_loans; i++)
        {
            if (current_round == loans[i].get_round_of_loan_taking() + loans[i].get_duration())
            {
                payment += loans[i].payment(loans[i]);
            }
        }
        return payment;
    }
    double get_state_of_account() const
    {
        return state_of_account;
    }
    double get_magazine_capacity() const
    {   
        return Warehouse_worker::CMag * Warehouse_worker::get_number_of_warehouse_workers();
    }
    double get_product_price() const
    {
        return Engineer::CI * Engineer::get_number_of_engineers();
    }
    double get_demand() const
    {
        return Marketer::CMkt * Marketer::get_number_of_marketers();
    }
    double get_theoretical_output() const
    {
        return Construction_worker::get_number_of_construction_workers() * Engineer::CI;
    }
    double get_real_output() const
    {
        return std::min(get_magazine_capacity(), get_theoretical_output());
    }
    double get_sold_products() const
    {
        return std::min(get_demand(), get_real_output());
    }
    double get_income() const
    {
        return income;
    }    
    double get_revenue() const
    {
        return revenue;
    }
    double company_value(const int& current_round)
    {
        current_company_value = 0;
        double sum = 0;
        if(current_round < N)
        {
            std::cout << "The value of the company cannot be calculated, the game lasts less than 3 turns\n";
        }
        else
            for (int i = current_round-N+1; i <= current_round; i++)
            {
                sum += income_history[i];
            }
        return current_company_value = sum/N;
    }
    double get_current_company_value() const
    {
        return current_company_value;
    }
    void finances(const int& current_round)
    {
        income = 0;
        revenue = 0;
        income = get_sold_products() * get_product_price();
        income_history[current_round] = income;
        revenue = get_income() - current_round_salary - payment;
        state_of_account += revenue;
        company_value(current_round);
        if (state_of_account < 0)
        {
            std::cout << "You are bankrupt\n GAME OVER\n";
            exit(0);
        }
    }
    void state_of_the_company()
    {
        std::cout << "\n" << "Account state: " << get_state_of_account() << "\n";
        std::cout << "Revenue: " << get_revenue() << "\n";
        std::cout << "Number of employees: " << Employee::get_number_of_employees() << "\n";
        std::cout << "Number of Engineers: " << Engineer::get_number_of_engineers() << "\n";
        std::cout << "Number of Warehouse Workers: " << Warehouse_worker::get_number_of_warehouse_workers() << "\n";
        std::cout << "Number of Marketers: " << Marketer::get_number_of_marketers() << "\n";
        std::cout << "Number of Construction Workers: " << Construction_worker::get_number_of_construction_workers() << "\n";
        std::cout << "Warehouse capacity: " << get_magazine_capacity() << "\n";
        std::cout << "Product price: " << get_product_price() << "\n";
        std::cout << "Demand: " << get_demand() << "\n";
        std::cout << "Theoretical production: " << get_theoretical_output() << "\n";
        std::cout << "Actual production: " << get_real_output() << "\n";
        std::cout << "Sold products: " << get_sold_products() << "\n";
        std::cout << "Income: " << get_income() << "\n";
        std::cout << "Company value: " << get_current_company_value() << "\n";
    };
private:
    const int N = 3;
    double revenue = 0;
    double current_round_salary = 0;
    double payment = 0;
    double income = 0;
    double current_company_value = 0;
    std::unique_ptr<double[]> income_history;
    double state_of_account;
    int number_of_loans = 0;
    std::unique_ptr<Credit[]> loans;
    std::vector<std::variant<Engineer, Warehouse_worker, Marketer, Construction_worker>> workers_vector;
};

class Game : public Company
{
public:
    Game() : round{0}
    {
        company = std::make_unique<Company>();
        company->hire("Engineer");
        company->hire("Warehouse_worker");
        company->hire("Marketer");
        company->hire("Construction_worker");
        company->hire("Forklift_driver");
        company->state_of_the_company();
        std::cout << "\n" << "Round: " << round << "\n";
    }
    void player_action()
    {
        std::cout << "\n"<< "Possible actions:\n";
        std::cout << "1. Hire employee\n";
        std::cout << "2. Take loan\n";
        std::cout << "3. Print employees\n";
        std::cout << "4. Print company state\n";
        std::cout << "5. Next round\n";
        std::cout << "6. End game\n";
        std::cout << "Choose action: " << "\n";
        std::cin >> action;
        if (action == 1)
        {
            std::cout << "\n" << "Choose employee to hire:\n";
            std::cout << "1. Engineer\n";
            std::cout << "2. Warehouse_worker\n";
            std::cout << "3. Marketer\n";
            std::cout << "4. Construction_worker\n";
            std::cout << "Choose employee: " << "\n";
            std::cin >> action;
            if (action == 1)
            {
                company->hire("Engineer");
            }
            else if (action == 2)
            {
                company->hire("Warehouse_worker");
            }
            else if (action == 3)
            {
                company->hire("Marketer");
            }
            else if (action == 4)
            {
                company->hire("Construction_worker");
            }
        }
        else if (action == 2)
        {
            double amount;
            int duration;
            std::cout << "Enter loan amount: ";
            std::cin >> amount;
            std::cout << "Enter loan duration: ";
            std::cin >> duration;
            company->take_loan(amount, duration, round);
        }
        else if (action == 3)
        {
            company->print_employees();
        }
        else if (action == 4)
        {
            company->state_of_the_company();
        }
        else if (action == 5)
        {
            this->increase_round();
            company->pay_salary();
            company->loan_payment(round);
            company->finances(round);
            company->state_of_the_company();
            std::cout << "\n" << "round: " << round << "\n";
            void player_action();
        }
        else if (action == 6)
        {
            state = false;
        }
        else
        {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the line
            std::cout << "Invalid action. Please choose again.\n";
        }
    };
    bool get_stan()
    {
        return state;
    };
    void increase_round()
    {
        round++;
    };
    int get_round()
    {
        return round;
    };
private:
    int action;
    int round;
    bool state = true;
    std::unique_ptr<Company> company;
};

int Engineer::number_of_engineers = 0;
int Warehouse_worker::number_of_warehouse_workers = 0;
int Marketer::number_of_marketers = 0;
int Construction_worker::number_of_construction_workers = 0;
int Employee::number_of_employees = 0;

int main()
{
    Game game_1;
    while (game_1.get_stan() == true)
    {
        game_1.player_action();
    }
    std::cout << "GAME OVER\n";
    return 0;
}
