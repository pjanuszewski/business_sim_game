#include "RandomNameGenerator.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <cstdlib>

class Pracownik
{
public:
    void set_name()
    {
        this->name = get_random_name();
    }
    std::string get_name() const
    {
        return name;
    }
    double get_wynagrodzenie() const
    {
        return wynagrodzenie;
    }
    protected:
    void set_wynagrodzenie(double wynagrodzenie)
    {
        this->wynagrodzenie = wynagrodzenie;
    }
    std::variant<int, double, bool, std::string> cecha;
private:
    std::string name;
    double wynagrodzenie;
};

class Inżynier : public Pracownik
{
public:
    Inżynier()
    {
        set_name();
        set_wynagrodzenie(1000);
    }
    void print() const
    {
        std::cout << "Imię Inżyniera: " << get_name() << "\n";
        std::cout << "Wynagrodzenie (PLN): " << get_wynagrodzenie() << "\n";
        std::cout << "Wykształcenie: " << get_cecha() << "\n";
    }
    std::string get_cecha() const
    {
        return cecha;
    }
        std::string pickRandomString(const std::vector<std::string>& strings)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, strings.size() - 1);
        int index = dis(gen);
        return strings[index];
    }
    constexpr static const double CI = 134;
private:
    std::vector<std::string> strings = {"Robotyka", "Energetyka", "Lotnictwo"};
    std::string cecha = pickRandomString(strings); // wykształcenie
    
};

class Magazynier : public Pracownik
{
public:
    Magazynier()
    {
        set_name();
        set_wynagrodzenie(400);
    }
    bool get_cecha() const
    {
        return cecha;
    }
    void print() const
    {
        std::cout << "Imię Magazyniera: " << get_name() << "\n";
        std::cout << "Wynagrodzenie (PLN): " << get_wynagrodzenie() << "\n";
        std::cout << "Uprawnienia na wózek widłowy: " << get_cecha() << "\n";
    }
    constexpr static const double CMag = 123;
private:
    bool generate_random_bool()
    {
        return rand() % 2 == 0;
    }
    bool cecha = generate_random_bool(); // czy ma uprawnienia na wózek widłowy
protected:
    
};

class Marketer : public Pracownik
{
public:
    Marketer()
    {
        set_name();
        set_wynagrodzenie(500);
    }
    int get_cecha() const
    {
        return cecha;
    }
    void print() const
    {
        std::cout << "Imię Marketera: " << get_name() << "\n";
        std::cout << "Wynagrodzenie (PLN): " << get_wynagrodzenie() << "\n";
        std::cout << "Followersi na Instagramie: " << get_cecha() << "\n";
    }
    constexpr static const double CMkt = 145;
private:
    int cecha = rand() % 1001; // liczba od 0 do 1000 followersów na Instagramie
    
};

class Robotnik: public Pracownik
{
public:
    Robotnik()
    {
        set_name();
        set_wynagrodzenie(600);
    }
    double get_cecha() const
    {
        return cecha;
    }
    void print() const
    {
        std::cout << "Imię Robotnika: " << get_name() << "\n";
        std::cout << "Wynagrodzenie (PLN): " << get_wynagrodzenie() << "\n";
        std::cout << "Rozmiar buta: " << get_cecha() << "\n";
    }
    constexpr static const double CR = 78;
private:
    double cecha = rand() % 20; // rozmiar buta
    
};

struct Printer_pracowników
{
    void operator()(const Inżynier& pracownik) { pracownik.print();}
    void operator()(const Magazynier& pracownik) { pracownik.print();}
    void operator()(const Marketer& pracownik) { pracownik.print();}
    void operator()(const Robotnik& pracownik) { pracownik.print();}
};

class Credit
{
public:
    double monthly_payment;
    Credit() : credit{0}, duration{0}, obecna_tura{0} {}
    Credit(const double& credit, const int& duration, const int&obecna_tura) : credit{credit}, duration{duration}, obecna_tura{obecna_tura}
    {
        interest_rate = 0.00001*duration*credit;
        tura_wziecia_kredytu = obecna_tura;
    }
    double payment(const Credit& credit)
    {
        return credit.credit + credit.interest_rate;
    }
    double get_tura_wziecia_kredytu() const
    {
        return tura_wziecia_kredytu;
    }
    int get_duration() const
    {
        return duration;
    }
private:
    int obecna_tura;
    int tura_wziecia_kredytu;
    double credit{0};
    double interest_rate{0};
    int duration;
    double total_payment;
    double total_interest;
};

class Company : public Pracownik, public Credit
{
public:
    Company() : prac(), kredyty(std::make_unique<Credit[]>(n_kredytów)), historia_przychodów(std::make_unique<double[]>(N)), stan_konta(100000.0)
    {
        
    }
    void drukuj_pracowników() const
    {
        for (int i = 0; i < n_pracowników; i++)
        {
            std::visit(Printer_pracowników{}, prac[i]);
        }
    }
    void wez_kredyt(double kwota, int duration, int obecna_tura)
    {
        kredyty[n_kredytów] = Credit(kwota, duration, obecna_tura);
        n_kredytów++;
    }
    void zatrudnij(std::string s)
    {
        if (s == "Inżynier")
        {
            prac.emplace_back(Inżynier());
            n_pracowników++;
        }
        else if (s == "Magazynier")
        {
            prac.emplace_back(Magazynier());
            n_pracowników++;
        }
        else if (s == "Marketer")
        {
            prac.emplace_back(Marketer());
            n_pracowników++;
        }
        else if (s == "Robotnik")
        {
            prac.emplace_back(Robotnik());
            n_pracowników++;
        }
    }
    void zaplac_wynagrodzenia()
    {
        wynagrodzenie_w_tej_turze = 0;
        for (int i = 0; i < n_pracowników; i++)
        {
            wynagrodzenie_w_tej_turze += std::visit([](auto&& arg) { return arg.get_wynagrodzenie(); }, prac[i]);
        }
        stan_konta -= wynagrodzenie_w_tej_turze;
    }
    double oplata_kredytu(const int& obecna_tura)
    {
        oplata = 0;
        for (int i = 0; i < n_kredytów; i++)
        {
            if (obecna_tura == kredyty[i].get_tura_wziecia_kredytu() + kredyty[i].get_duration())
            {
                oplata += kredyty[i].payment(kredyty[i]);
            }
        }
        return oplata;
    }
    double get_stan_konta() const
    {
        return stan_konta;
    }
    int get_n_Inżynierów() const
    {
        int n = 0;
        for (int i = 0; i < n_pracowników; i++)
        {
            if (std::holds_alternative<Inżynier>(prac[i]))
            {
                n++;
            }
        }
        return n;
    }
    int get_n_Magazynierów() const
    {
        int n = 0;
        for (int i = 0; i < n_pracowników; i++)
        {
            if (std::holds_alternative<Magazynier>(prac[i]))
            {
                n++;
            }
        }
        return n;
    }
    int get_n_Marketerów() const
    {
        int n = 0;
        for (int i = 0; i < n_pracowników; i++)
        {
            if (std::holds_alternative<Marketer>(prac[i]))
            {
                n++;
            }
        }
        return n;
    }
    int get_n_Robotników() const
    {
        int n = 0;
        for (int i = 0; i < n_pracowników; i++)
        {
            if (std::holds_alternative<Robotnik>(prac[i]))
            {
                n++;
            }
        }
        return n;
    }
    double get_pojemnosc_magazynu() const
    {   
        return Magazynier::CMag * get_n_Magazynierów();
    }
    double get_cena_produktu() const
    {
        return Inżynier::CI * get_n_Inżynierów();
    }
    double get_popyt() const
    {
        return Marketer::CMkt * get_n_Marketerów();
    }
    double get_teoretyczna_produkcja() const
    {
        return get_n_Robotników() * Inżynier::CI;
    }
    double get_faktyczna_produkcja() const
    {
        return std::min(get_pojemnosc_magazynu(), get_teoretyczna_produkcja());
    }
    double get_sprzedane_produkty() const
    {
        return std::min(get_popyt(), get_faktyczna_produkcja());
    }
    double get_przychód() const
    {
        return przychód;
    }    
    double get_dochód() const
    {
        return dochód;
    }
    double wartosc_spolki(const int& obecna_tura)
    {
        obecna_wartosc_spolki = 0;
        double sum = 0;
        if(obecna_tura < N)
        {
            std::cout << "Nie można obliczyć wartości spółki, gra trwa mniej niż 3 tury\n";
        }
        else
            for (int i = obecna_tura-N+1; i <= obecna_tura; i++)
            {
                sum += historia_przychodów[i];
            }
        return obecna_wartosc_spolki = sum/N;
    }
    double get_obecna_wartosc_spolki() const
    {
        return obecna_wartosc_spolki;
    }
    void finances(const int& obecna_tura)
    {
        przychód = 0;
        dochód = 0;
        przychód = get_sprzedane_produkty() * get_cena_produktu();
        historia_przychodów[obecna_tura] = przychód;
        dochód = get_przychód() - wynagrodzenie_w_tej_turze - oplata;
        stan_konta += dochód;
        wartosc_spolki(obecna_tura);
    }
    void stan_firmy()
    {
        std::cout << "\n" << "Stan konta: " << get_stan_konta() << "\n";
        std::cout << "Dochód: " << get_dochód() << "\n";
        std::cout << "Liczba pracowników: " << n_pracowników << "\n";
        std::cout << "Liczba Inżynierów: " << get_n_Inżynierów() << "\n";
        std::cout << "Liczba Magazynierów: " << get_n_Magazynierów() << "\n";
        std::cout << "Liczba Marketerów: " << get_n_Marketerów() << "\n";
        std::cout << "Liczba Robotników: " << get_n_Robotników() << "\n";
        std::cout << "Pojemność magazynu: " << get_pojemnosc_magazynu() << "\n";
        std::cout << "Cena produktu: " << get_cena_produktu() << "\n";
        std::cout << "Popyt: " << get_popyt() << "\n";
        std::cout << "Teoretyczna produkcja: " << get_teoretyczna_produkcja() << "\n";
        std::cout << "Faktyczna produkcja: " << get_faktyczna_produkcja() << "\n";
        std::cout << "Sprzedane produkty: " << get_sprzedane_produkty() << "\n";
        std::cout << "Przychód: " << get_przychód() << "\n";
        std::cout << "Wartość spółki: " << get_obecna_wartosc_spolki() << "\n";
    };
private:
    const int N = 3;
    int n_pracowników = 0;
    double dochód = 0;
    double wynagrodzenie_w_tej_turze = 0;
    double oplata = 0;
    double przychód = 0;
    double obecna_wartosc_spolki = 0;
    std::unique_ptr<double[]> historia_przychodów;
    double stan_konta;
    int n_kredytów = 0;
    std::unique_ptr<Credit[]> kredyty;
    std::vector<std::variant<Inżynier, Magazynier, Marketer, Robotnik>> prac;
};

class Game : public Company
{
public:
    Game() : tura{0}
    {
        firma = std::make_unique<Company>();
        firma->zatrudnij("Inżynier");
        firma->zatrudnij("Magazynier");
        firma->zatrudnij("Marketer");
        firma->zatrudnij("Robotnik");
        firma->stan_firmy();
        std::cout << "\n" << "Tura: " << tura << "\n";
    }
    void akcja_gracza()
    {
        std::cout << "\n"<< "Możliwe akcje:\n";
        std::cout << "1. Zatrudnij pracownika\n";
        std::cout << "2. Weź kredyt\n";
        std::cout << "3. Wydrukuj pracowników\n";
        std::cout << "4. Wydrukuj stan firmy\n";
        std::cout << "5. Kolejna tura\n";
        std::cout << "6. Zakończ grę\n";
        std::cout << "Wybierz akcję: " << "\n";
        std::cin >> akcja;
        if (akcja == 1)
        {
            std::cout << "\n" << "Wybierz pracownika do zatrudnienia:\n";
            std::cout << "1. Inżynier\n";
            std::cout << "2. Magazynier\n";
            std::cout << "3. Marketer\n";
            std::cout << "4. Robotnik\n";
            std::cout << "Wybierz pracownika: " << "\n";
            std::cin >> akcja;
            if (akcja == 1)
            {
                firma->zatrudnij("Inżynier");
            }
            else if (akcja == 2)
            {
                firma->zatrudnij("Magazynier");
            }
            else if (akcja == 3)
            {
                firma->zatrudnij("Marketer");
            }
            else if (akcja == 4)
            {
                firma->zatrudnij("Robotnik");
            }
        }
        else if (akcja == 2)
        {
            double kwota;
            int duration;
            std::cout << "Podaj kwotę kredytu: ";
            std::cin >> kwota;
            std::cout << "Podaj czas trwania kredytu: ";
            std::cin >> duration;
            firma->wez_kredyt(kwota, duration, tura);
        }
        else if (akcja == 3)
        {
            firma->drukuj_pracowników();
        }
        else if (akcja == 4)
        {
            firma->stan_firmy();
        }
        else if (akcja == 5)
        {
            this->increase_tura();
            firma->zaplac_wynagrodzenia();
            firma->oplata_kredytu(tura);
            firma->finances(tura);
            firma->stan_firmy();
            std::cout << "\n" << "Tura: " << tura << "\n";
            void akcja_gracza();
        }
        else if (akcja == 6)
        {
            stan = false;
        }
    };
    bool get_stan()
    {
        return stan;
    };
    void increase_tura()
    {
        tura++;
    };
    int get_tura()
    {
        return tura;
    };
private:
    int akcja;
    int tura;
    bool stan = true;
    std::unique_ptr<Company> firma;
};

int main()
{
    Game game_1;
    while (game_1.get_stan() == true)
    {
        game_1.akcja_gracza();
    }
    return 0;
}