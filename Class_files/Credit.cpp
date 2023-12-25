#include "Credit.h"

Credit::Credit() : credit{0}, duration{0}, current_round{0} {}

Credit::Credit(const double& credit, const int& duration, const int& current_round) : credit{credit}, duration{duration}, current_round{current_round}
{
    interest_rate = 0.00001 * duration * credit;
    round_of_loan_taking = current_round;
}

double Credit::payment(const Credit& credit)
{
    return credit.credit + credit.interest_rate;
}

double Credit::get_round_of_loan_taking() const
{
    return round_of_loan_taking;
}

int Credit::get_duration() const
{
    return duration;
}