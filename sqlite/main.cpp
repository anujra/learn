#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <unordered_map>
#include <chrono>
#include <iomanip>


#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>

static bool print_cols = true;



//static std::unordered_multimap<int, std::string> id_name;

static std::unordered_multimap<int, std::tuple<std::string, std::chrono::seconds, std::chrono::seconds>> g_superdb;

/*
static int callback1(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    if (print_cols) {
        for(i = 0; i < argc; i++)
            std::cout << azColName[i] << ", ";
        print_cols = false;
        std::cout << std::endl;
    }

//    std::cout << argv[0] << "\t" << argv[1] << "\t" << argv[2] << "\t" << argv[3] << "\t" << argv[4] << "\t" << argv[5] << std::endl;

    std::tm time_beg = {};
    std::tm time_end = {};
    std::stringstream is_beg(argv[4]);
    std::stringstream is_end(argv[4]);
    is_beg >> std::get_time(&time_beg, "%Y-%m-%d %H:%M:%S");
    is_end >> std::get_time(&time_end, "%Y-%m-%d %H:%M:%S");

    std::chrono::system_clock::time_point tp_beg = std::chrono::system_clock::from_time_t(std::mktime(&time_beg));
    std::chrono::seconds epoch_beg = std::chrono::duration_cast<std::chrono::seconds>(tp_beg.time_since_epoch());

    std::chrono::system_clock::time_point tp_end = std::chrono::system_clock::from_time_t(std::mktime(&time_beg));
    std::chrono::seconds epoch_end = std::chrono::duration_cast<std::chrono::seconds>(tp_end.time_since_epoch());

    g_superdb.emplace(atoi(argv[2]), std::make_tuple(argv[3], epoch_beg, epoch_end));

    return 0;
}
*/

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    if (print_cols) {
        for(i = 0; i < argc; i++)
            std::cout << azColName[i] << ", ";
        print_cols = false;
        std::cout << std::endl;
    }

//    std::cout << argv[0] << "\t" << argv[1] << "\t" << argv[2] << "\t" << argv[3] << "\t" << argv[4] << "\t" << argv[5] << std::endl;

    std::tm time_beg = {};
    std::tm time_end = {};
    std::stringstream is_beg(argv[4]);
    std::stringstream is_end(argv[4]);
    is_beg >> std::get_time(&time_beg, "%Y-%m-%d %H:%M:%S");
    is_end >> std::get_time(&time_end, "%Y-%m-%d %H:%M:%S");

    std::chrono::system_clock::time_point tp_beg = std::chrono::system_clock::from_time_t(std::mktime(&time_beg));
    std::chrono::seconds epoch_beg = std::chrono::duration_cast<std::chrono::seconds>(tp_beg.time_since_epoch());

    std::chrono::system_clock::time_point tp_end = std::chrono::system_clock::from_time_t(std::mktime(&time_beg));
    std::chrono::seconds epoch_end = std::chrono::duration_cast<std::chrono::seconds>(tp_end.time_since_epoch());

    g_superdb.emplace(atoi(argv[2]), std::make_tuple(argv[3], epoch_beg, epoch_end));

    // for(i = 0; i < argc; i++)
    //     std::cout << (argv[i] ? argv[i] : "NULL") << ", ";
    // std::cout << std::endl;
    return 0;
}


typedef std::unordered_multimap<int, std::tuple<std::string, std::chrono::seconds, std::chrono::seconds>>::iterator super_iter;

int main(int argc, char* argv[]) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* Open database */
    rc = sqlite3_open("/tmp/superdb.db", &db);

    if( rc ) {
        std::cerr << "Can't open database:" << sqlite3_errmsg(db) << std::endl;
        return(0);
    } else
        std::cout << "Opened database successfully" << std::endl;


    //std::string sql = {"SELECT * FROM SuperContracts sc WHERE sc.Exchange LIKE '%ICE%' AND sc.NativeSymbol LIKE 'BRN%' and sc.EndDate < '2024-04-01'  AND sc.EndDate > DATE('now') ORDER BY sc.StartDate"};
    std::string sql = {"SELECT Id, Exchange, NativeContractId, NativeSymbol, StartDate, EndDate, RecordDate FROM SuperContracts sc WHERE sc.Exchange LIKE 'CME' ORDER BY sc.StartDate"};

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    std::cout << g_superdb.size() << std::endl;
    int key = 716547;
    std::pair<super_iter, super_iter> range = g_superdb.equal_range(key);
    super_iter it = range.first;
    while (it != range.second) {
        std::cout << key << "\t" << std::get<0>(it->second) << "\t" << std::get<1>(it->second).count() << "\t" << std::get<2>(it->second).count() << std::endl;
        ++it;
    }

    key = 11980;
    range = g_superdb.equal_range(key);
    it = range.first;
    while (it != range.second) {
        std::cout << key << "\t" << std::get<0>(it->second) << "\t" << std::get<1>(it->second).count() << "\t" << std::get<2>(it->second).count() << std::endl;
        ++it;
    }

    // auto range = g_superdb.equal_range(key);
    // for_each(range.first, range.second, 
    //     [key](const auto& it) {
    //         std::cout << key << "\t" << std::get<0>(it.second) << "\t" << std::get<1>(it.second).count() << "\t" << std::get<2>(it.second).count() << std::endl;

    //     });

    // key = 11980;
    // range = g_superdb.equal_range(key);
    // for_each(range.first, range.second, 
    //     [key](const auto& it) {
    //         std::cout << key << "\t" << std::get<0>(it.second) << "\t" << std::get<1>(it.second).count() << "\t" << std::get<2>(it.second).count() << std::endl;

    //     });


    if( rc != SQLITE_OK ){
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
    } else 
            std::cout << "Success Query" << std::endl;

    sqlite3_close(db);
    return 0;
}