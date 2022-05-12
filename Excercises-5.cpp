// Implementing excercises 5-1 to 5-4.

#include <cstdio>
#include <stdexcept>

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    ConsoleLogger(const char* logger_name) 
    : logger_name { logger_name } {}

    void log_transfer(long from, long to, double amount) override {
        printf("[%s] %ld -> %ld: %f\n", logger_name, from, to, amount);
    }
    const char* logger_name;
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    printf("[file] %ld,%ld,%f\n", from, to, amount);
  }
};

struct Account {
    long account_id = 0;
    long balance = 0;
};

struct AccountDB {
    virtual ~AccountDB() = default;
    virtual void set_amount(long account_id, long amount) = 0;
    virtual long get_amount(long account_id) = 0;
};

struct InMemoryAccountDB : AccountDB {
    InMemoryAccountDB() 
    : max_accounts{ 100 }
    , account_array{ new Account[max_accounts] } {}

    ~InMemoryAccountDB() {
        delete [] account_array;
    }

    void create_account(long account_id) {
        // Accounts must not have a zero id since we 
        // use that to indicate a free location for a new account.
        if(account_id == 0) throw std::runtime_error("Account ID must not be 0");

        // Search the array space 
        for(auto idx = 0; idx < max_accounts; idx++) {
            auto& account = account_array[idx];

            // Return if account already exists.
            if(account.account_id == account_id) return;

            // Found an empty slot.
            if(account.account_id == 0) {
                // Initialise new account
                account.account_id = account_id;
                account.balance = 0; 
                return;
            }
        }
        throw std::runtime_error("Allocated database space exceded");
    }

    void set_amount(long account_id, long amount) {
        for(auto idx = 0; idx < max_accounts; idx++) {
            auto& account = account_array[idx];
            if(account.account_id == account_id) {
                account.balance = amount;
                return;
            }
        }
        throw std::runtime_error("Account not found");
        
    }

    long get_amount(long account_id) {
        for(auto idx = 0; idx < max_accounts; idx++) {
            auto& account = account_array[idx];
            if(account.account_id == account_id) {
                return account.balance;
            }
        }
        throw std::runtime_error("Account not found");
    }

    // Print a summary of database
    void print_db() {
        auto free_slots = 0L;

        for(auto idx = 0; idx < max_accounts; idx++) {
            auto& account = account_array[idx];
            if(account.account_id != 0) {
                printf("Account ID: %ld, Balance $%ld\n", account.account_id, account.balance);
            } else {
                free_slots++;
            }
        }
        printf("Free slots: %ld\n", free_slots);
    }

    private:
        int max_accounts; 
        Account * account_array; 
};

struct Bank {
  void set_logger(Logger* new_logger) {
    logger = new_logger;
  }

  void set_account_db(AccountDB* db) {
      account_db = db;
  }

  void make_transfer(long from, long to, double amount) {
    if(logger)
      logger->log_transfer(from, to, amount);
    
    if(account_db) {
        // Starting balances
        auto from_starting = account_db->get_amount(from);
        auto to_starting =   account_db->get_amount(to);

        // New balances
        auto from_new = from_starting - amount;
        auto to_new = to_starting + amount;

        account_db->set_amount(from, from_new);
        account_db->set_amount(to, to_new);
        
    } else {
        printf("No account database set");
    }
  }

  private:
    Logger* logger{};
    AccountDB* account_db{};
};



int main() {
    printf("Testing InMemoryAccountDB\n");

    InMemoryAccountDB db;
    db.create_account(1000);
    db.create_account(2000);
    db.create_account(3000);

    db.set_amount(1000, 50);
    db.set_amount(2000, -50);
    db.set_amount(3000, 500);
    
    printf("Amount in account 2000 is %ld\n", db.get_amount(2000));
    db.print_db();

    printf("Testing Bank");
    ConsoleLogger console_logger("a logger");
    Bank bank;
    bank.set_logger(&console_logger);
    bank.set_account_db(&db);

    bank.make_transfer(3000, 2000, 50);
    db.print_db();
    return 0;
}
