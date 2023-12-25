class Credit
{
public:
    double monthly_payment;
    Credit();
    Credit(const double& credit, const int& duration, const int& current_round);
    double payment(const Credit& credit);
    double get_round_of_loan_taking() const;
    int get_duration() const;

private:
    int current_round;
    int round_of_loan_taking;
    double credit{0};
    double interest_rate{0};
    int duration;
    double total_payment;
    double total_interest;
};