#include <iostream>
#include <fstream>
#include <string>
#include "SelfOrganizingList.h"

using namespace Sol;

void log(std::ofstream& file, const std::string& text) {
    std::cout << text << std::endl;
    file << text << std::endl;
}

int main() {
    std::ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "ERROR: Could not open log.txt" << std::endl;
        return 1;
    }

    int total = 0;
    int passed = 0;

    log(logFile, "--- SelfOrganizingList test report ---");
    log(logFile, "Checking main operations and some error cases");
    log(logFile, "--------------------------------------");
    log(logFile, "");

    // Test 1 - insert with strings
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Smells Like Teen Spirit";
        list += "Gangnam Style";
        list += "Blinding Lights";

        log(logFile, "After insert: " + list.toString());

        if (list.toString().find("size=3") != std::string::npos) {
            log(logFile, "[TEST 1] PASSED: operator+= works with strings");
            ++passed;
        } else {
            log(logFile, "[TEST 1] FAILED: wrong size after insert");
        }
    } catch (...) {
        log(logFile, "[TEST 1] FAILED: unexpected exception");
    }
    log(logFile, "");

    // Test 2 - duplicate insert
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Gangnam Style";
        log(logFile, "Before duplicate insert: " + list.toString());

        list += "Gangnam Style";
        log(logFile, "[TEST 2] FAILED: duplicate was inserted");
    } catch (const DuplicateElementException&) {
        log(logFile, "[TEST 2] PASSED: duplicate insert throws custom exception");
        ++passed;
    } catch (...) {
        log(logFile, "[TEST 2] FAILED: wrong exception type");
    }
    log(logFile, "");

    // Test 3 - search and move-to-front
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Smells Like Teen Spirit";
        list += "Gangnam Style";
        list += "Blinding Lights";

        log(logFile, "Before search: " + list.toString());
        int pos = list["Smells Like Teen Spirit"];
        log(logFile, "After search: " + list.toString());

        std::string state = list.toString();
        bool movedToFront = state.find("Smells Like Teen Spirit") < state.find("Blinding Lights");

        if (pos == 2 && movedToFront) {
            log(logFile, "[TEST 3] PASSED: operator[] finds element and applies Move-to-Front");
            ++passed;
        } else {
            log(logFile, "[TEST 3] FAILED: operator[] did not work correctly");
        }
    } catch (...) {
        log(logFile, "[TEST 3] FAILED: search threw unexpected exception");
    }
    log(logFile, "");

    // Test 4 - search for missing element
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Blinding Lights";
        log(logFile, "Current list: " + list.toString());

        list["Unknown Song"];
        log(logFile, "[TEST 4] FAILED: missing element did not throw exception");
    } catch (const std::invalid_argument&) {
        log(logFile, "[TEST 4] PASSED: missing element search throws exception");
        ++passed;
    } catch (...) {
        log(logFile, "[TEST 4] FAILED: wrong exception type");
    }
    log(logFile, "");

    // Test 5 - remove element
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Smells Like Teen Spirit";
        list += "Gangnam Style";

        log(logFile, "Before remove: " + list.toString());
        list -= "Gangnam Style";
        log(logFile, "After remove: " + list.toString());

        std::string result = list.toString();
        bool removed = result.find("Gangnam Style") == std::string::npos;
        bool correctSize = result.find("size=1") != std::string::npos;

        if (removed && correctSize) {
            log(logFile, "[TEST 5] PASSED: operator-= removes element");
            ++passed;
        } else {
            log(logFile, "[TEST 5] FAILED: remove did not work correctly");
        }
    } catch (...) {
        log(logFile, "[TEST 5] FAILED: remove threw unexpected exception");
    }
    log(logFile, "");

    // Test 6 - update element
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Gangnam Style";

        log(logFile, "Before update: " + list.toString());
        list *= {"Gangnam Style", "Gangnam Style (Remix)"};
        log(logFile, "After update: " + list.toString());

        std::string result = list.toString();
        bool updated = result.find("Gangnam Style (Remix)") != std::string::npos;
        bool sameSize = result.find("size=1") != std::string::npos;

        if (updated && sameSize) {
            log(logFile, "[TEST 6] PASSED: operator*= updates element");
            ++passed;
        } else {
            log(logFile, "[TEST 6] FAILED: update did not work");
        }
    } catch (...) {
        log(logFile, "[TEST 6] FAILED: update threw unexpected exception");
    }
    log(logFile, "");

    // Test 7 - comparison operators
    ++total;
    try {
        SelfOrganizingList<int> a;
        SelfOrganizingList<int> b;

        a += 1;
        b += 1;
        b += 2;

        log(logFile, "List a: " + a.toString());
        log(logFile, "List b: " + b.toString());
        log(logFile, "List a size: " + std::to_string(a.size()));
        log(logFile, "List b element at index 0: " + std::to_string(b.at(0)));

        if ((a != b) && (a < b) && (b > a)) {
            log(logFile, "[TEST 7] PASSED: comparison operators work");
            ++passed;
        } else {
            log(logFile, "[TEST 7] FAILED: comparison operators returned wrong result");
        }
    } catch (...) {
        log(logFile, "[TEST 7] FAILED: comparison test threw exception");
    }
    log(logFile, "");

    // Test 8 - clear with !
    ++total;
    try {
        SelfOrganizingList<char> list;
        list += 'A';
        list += 'B';

        log(logFile, "Before clear: " + list.toString());
        !list;
        log(logFile, "After clear: " + list.toString());

        if (list.toString().find("size=0") != std::string::npos) {
            log(logFile, "[TEST 8] PASSED: operator! clears the list");
            ++passed;
        } else {
            log(logFile, "[TEST 8] FAILED: clear did not work");
        }
    } catch (...) {
        log(logFile, "[TEST 8] FAILED: clear threw unexpected exception");
    }
    log(logFile, "");

    // Test 9 - copy constructor
    ++total;
    try {
        SelfOrganizingList<std::string> list;
        list += "Song A";
        list += "Song B";

        log(logFile, "Original before copy: " + list.toString());
        SelfOrganizingList<std::string> copy = list;
        log(logFile, "Copy after constructor: " + copy.toString());

        if (copy == list) {
            log(logFile, "[TEST 9] PASSED: copy constructor works");
            ++passed;
        } else {
            log(logFile, "[TEST 9] FAILED: copy constructor failed");
        }
    } catch (...) {
        log(logFile, "[TEST 9] FAILED: copy constructor threw exception");
    }
    log(logFile, "");

    // Test 10 - assignment operator
    ++total;
    try {
        SelfOrganizingList<std::string> list1;
        list1 += "Song A";
        list1 += "Song B";

        SelfOrganizingList<std::string> list2;
        list2 += "Temporary";

        log(logFile, "Before assignment, list1: " + list1.toString());
        log(logFile, "Before assignment, list2: " + list2.toString());

        list2 = list1;
        log(logFile, "After assignment, list2: " + list2.toString());

        if (list2 == list1) {
            log(logFile, "[TEST 10] PASSED: assignment operator works");
            ++passed;
        } else {
            log(logFile, "[TEST 10] FAILED: assignment operator failed");
        }
    } catch (...) {
        log(logFile, "[TEST 10] FAILED: assignment operator threw exception");
    }
    log(logFile, "");

    // Test 11 - int type
    ++total;
    try {
        SelfOrganizingList<int> list;
        list += 10;
        list += 20;
        list += 30;

        log(logFile, "Int list before search: " + list.toString());
        int pos = list[20];
        log(logFile, "Int list after search: " + list.toString());

        if (pos == 1) {
            log(logFile, "[TEST 11] PASSED: template works with int type");
            ++passed;
        } else {
            log(logFile, "[TEST 11] FAILED: int test gave wrong result");
        }
    } catch (...) {
        log(logFile, "[TEST 11] FAILED: int test threw exception");
    }
    log(logFile, "");

    // Test 12 - empty list search
    ++total;
    try {
        SelfOrganizingList<int> emptyList;
        log(logFile, "Empty list state: " + emptyList.toString());

        emptyList[5];
        log(logFile, "[TEST 12] FAILED: empty list search did not throw");
    } catch (const std::invalid_argument&) {
        log(logFile, "[TEST 12] PASSED: empty list search throws exception");
        ++passed;
    } catch (...) {
        log(logFile, "[TEST 12] FAILED: wrong exception type");
    }
    log(logFile, "");

    // Extra scenario
    log(logFile, "--------------------------------------");
    log(logFile, "Extra sequence test:");
    log(logFile, "");

    try {
        SelfOrganizingList<std::string> seq;
        seq += "Song 1";
        seq += "Song 2";
        seq += "Song 3";
        log(logFile, "Initial sequence: " + seq.toString());

        seq["Song 1"];
        log(logFile, "After searching Song 1: " + seq.toString());

        seq *= {"Song 1", "Song 1 (Edited)"};
        log(logFile, "After update: " + seq.toString());

        seq -= "Song 2";
        log(logFile, "After removing Song 2: " + seq.toString());
    } catch (...) {
        log(logFile, "Extra sequence test threw exception");
    }

    log(logFile, "");
    log(logFile, "--------------------------------------");
    log(logFile, "Final results:");
    log(logFile, "Total tests: " + std::to_string(total));
    log(logFile, "Passed: " + std::to_string(passed));
    log(logFile, "Failed: " + std::to_string(total - passed));
    log(logFile, "--------------------------------------");
    log(logFile, "");

    logFile.close();
    std::cout << "\nTests finished. See log.txt for full report." << std::endl;
    return 0;
}