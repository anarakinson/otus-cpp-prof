
#include <sqlite3.h>

#include <iostream>



template <typename T>
struct deferred_action{
private:
    T action;

public:
    deferred_action(T &&_act) : action{std::move(_act)} {}
    ~deferred_action() { action(); }
};


//   auto print_results = [](void *, int columns, char **data, char **names) -> int{
//     for (int i = 0; i < columns; ++i)
//       std::cout << names[i] << " = " << (data[i] ? data[i] : "NULL") << std::endl;
//     std::cout << std::endl;
//     return 0;
//   };

int print_results(void *x, int columns, char **data, char **names) {

    for (int i = 0; i < columns; ++i) {
        std::cout << names[i] << " = " << (data[i] ? data[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;

}


int main(int argc, char** argv) {

    
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <SQL>" << std::endl;
        return EXIT_FAILURE;
    }


    // create handler
    const char *db_name = "db";
    sqlite3 *db = nullptr;

    // close database at the end in any case
    deferred_action sqlite_deleter(
        [db] () { sqlite3_close(db); }
    );

    // open database
    if (sqlite3_open(db_name, &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "[+] \"" << db_name << "\": database opened successfully!"<< std::endl;


    char *errmsg;
    int err = sqlite3_exec(db, argv[1], print_results, 0, &errmsg);

    if (err != SQLITE_OK) {
        std::cerr << "Can't execute query: " << errmsg << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "[+] \"" << db_name << "\": Success!"<< std::endl;

    return 0;

}

