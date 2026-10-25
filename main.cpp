#include "AirgeadBankingApp.h"

#include <exception>
#include <iostream>

int main() {
    try {
        // Create the application object and begin the program.
        AirgeadBankingApp bankingApp;
        bankingApp.run();
    }
    catch (const std::exception& exception) {
        // Display an understandable message if an unexpected error occurs.
        std::cerr
            << "The program encountered an unexpected error: "
            << exception.what()
            << '\n';

        return 1;
    }
    catch (...) {
        // Exit gracefully if an unknown error occurs.
        std::cerr
            << "The program encountered an unknown error.\n";

        return 1;
    }

    return 0;
}