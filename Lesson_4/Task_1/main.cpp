#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <cstdio>

class Bank {
private:
    struct Account {
        double balance;
        double credit;
        double deposit;
        time_t last_updated;
    };

    std::map<int, Account> accounts;
    time_t current_date;

    double calculate_interest(double amount, double rate, time_t duration) {
        double years = duration / (365.0 * 24 * 60 * 60);
        return amount * rate * years;
    }

    void update_account(int account_id) {
        if (accounts.find(account_id) == accounts.end()) return;

        Account &acc = accounts[account_id];
        time_t duration = current_date - acc.last_updated;

        acc.deposit += calculate_interest(acc.deposit, 0.05, duration);

        acc.credit += calculate_interest(acc.credit, 0.1, duration);

        acc.last_updated = current_date;
    }

public:
    Bank() : current_date(std::time(nullptr)) {}

    void set_date(const std::string &date_str) {
        struct tm tm_date{};
        if (sscanf(date_str.c_str(), "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday) == 3) {
            tm_date.tm_year -= 1900;
            tm_date.tm_mon -= 1;
            current_date = mktime(&tm_date);

            for (auto &[id, acc] : accounts) {
                update_account(id);
            }
        } else {
            std::cerr << "Invalid date format. Use YYYY-MM-DD.\n";
        }
    }

    void create_account(int account_id) {
        accounts[account_id] = {0.0, 0.0, 0.0, current_date};
        std::cout << "Account " << account_id << " created.\n";
    }

    void delete_account(int account_id) {
        accounts.erase(account_id);
        std::cout << "Account " << account_id << " deleted.\n";
    }

    void deposit_money(int account_id, double amount) {
        if (accounts.find(account_id) != accounts.end()) {
            update_account(account_id);
            accounts[account_id].balance += amount;
            std::cout << "Deposited " << amount << " to account " << account_id << ".\n";
        } else {
            std::cerr << "Account " << account_id << " not found.\n";
        }
    }

    void withdraw_money(int account_id, double amount) {
        if (accounts.find(account_id) != accounts.end() && accounts[account_id].balance >= amount) {
            update_account(account_id);
            accounts[account_id].balance -= amount;
            std::cout << "Withdrew " << amount << " from account " << account_id << ".\n";
        } else {
            std::cerr << "Account " << account_id << " not found or insufficient funds.\n";
        }
    }

    void print_account(int account_id) {
        if (accounts.find(account_id) != accounts.end()) {
            update_account(account_id);
            const Account &acc = accounts[account_id];
            std::cout << "Account " << account_id << ":\n";
            std::cout << "  Balance: " << acc.balance << "\n";
            std::cout << "  Credit: " << acc.credit << "\n";
            std::cout << "  Deposit: " << acc.deposit << "\n";
        } else {
            std::cerr << "Account not found.\n";
        }
    }
};

int main() {
    Bank bank;
    int choice, account_id;
    double amount;
    std::string date;

    while (true) {
        std::cout << "\n Bank Menu \n";
        std::cout << "1. Create account\n";
        std::cout << "2. Delete account\n";
        std::cout << "3. Deposit money\n";
        std::cout << "4. Withdraw money\n";
        std::cout << "5. Set date\n";
        std::cout << "6. Print account\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        std::cout << "Enter account ID: ";
        std::cin >> account_id;

        switch (choice) {
        case 1:
            bank.create_account(account_id);
            break;
        case 2:
            bank.delete_account(account_id);
            break;
        case 3:
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            bank.deposit_money(account_id, amount);
            break;
        case 4:
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            bank.withdraw_money(account_id, amount);
            break;
        case 5:
            std::cout << "Enter new date (YYYY-MM-DD): ";
            std::cin >> date;
            bank.set_date(date);
            break;
        case 6:
            bank.print_account(account_id);
            break;
        case 0:
            return 0;
        default:
            std::cerr << "Invalid option. Try again.\n";
        }
    }
}
