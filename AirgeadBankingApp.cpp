#include "AirgeadBankingApp.h"

#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {
    // Constants used by the monthly compound-interest calculation.
    constexpr int MONTHS_PER_YEAR = 12;
    constexpr double PERCENT_CONVERSION = 100.0;
}

// Initializes the application's investment values.
AirgeadBankingApp::AirgeadBankingApp()
    : m_initialInvestment(0.0),
    m_monthlyDeposit(0.0),
    m_annualInterest(0.0),
    m_numberOfYears(0) {
}

// Runs the application and allows the user to test multiple investment plans.
void AirgeadBankingApp::run() {
    bool runAgain = true;

    while (runAgain) {
        collectUserInput();
        waitForEnter();
        displayReports();

        runAgain = (getRunAgainChoice() == 'Y');

        if (runAgain) {
            std::cout << "\n\n";
        }
    }

    std::cout << "\nThank you for using the Airgead Banking Investment Calculator.\n";
}

// Displays the required input screen and stores validated user values.
void AirgeadBankingApp::collectUserInput() {
    std::cout << "***************************************\n";
    std::cout << "************* Data Input **************\n";
    std::cout << "***************************************\n";

    m_initialInvestment =
        getPositiveDouble("Initial Investment Amount: $");

    m_monthlyDeposit =
        getPositiveDouble("Monthly Deposit: $");

    m_annualInterest =
        getPositiveDouble("Annual Interest (%): ");

    m_numberOfYears =
        getPositiveInteger("Number of Years: ");

    // Display the accepted information so the user can review it.
    std::cout << "\nInvestment Information\n";
    std::cout << "---------------------------------------\n";
    std::cout << "Initial Investment: "
        << formatCurrency(m_initialInvestment) << '\n';

    std::cout << "Monthly Deposit:     "
        << formatCurrency(m_monthlyDeposit) << '\n';

    std::cout << "Annual Interest:     "
        << std::fixed << std::setprecision(2)
        << m_annualInterest << "%\n";

    std::cout << "Number of Years:     "
        << m_numberOfYears << '\n';
}

// Repeatedly prompts until the user enters one positive decimal number.
double AirgeadBankingApp::getPositiveDouble(
    const std::string& t_prompt) const {

    while (true) {
        std::cout << t_prompt;

        std::string userInput;
        std::getline(std::cin, userInput);

        std::istringstream inputStream(userInput);

        double value = 0.0;
        char extraCharacter = '\0';

        // Accept the input only if it contains one finite positive number.
        if ((inputStream >> value) &&
            !(inputStream >> extraCharacter) &&
            std::isfinite(value) &&
            value > 0.0) {

            return value;
        }

        std::cout
            << "Invalid input. Please enter a positive number greater than zero.\n";
    }
}

// Repeatedly prompts until the user enters one positive whole number.
int AirgeadBankingApp::getPositiveInteger(
    const std::string& t_prompt) const {

    while (true) {
        std::cout << t_prompt;

        std::string userInput;
        std::getline(std::cin, userInput);

        std::istringstream inputStream(userInput);

        int value = 0;
        char extraCharacter = '\0';

        // Reject decimals, letters, zero, and negative numbers.
        if ((inputStream >> value) &&
            !(inputStream >> extraCharacter) &&
            value > 0) {

            return value;
        }

        std::cout
            << "Invalid input. Please enter a positive whole number.\n";
    }
}

// Gives the user a chance to review the accepted data.
void AirgeadBankingApp::waitForEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::string unusedInput;
    std::getline(std::cin, unusedInput);
}

// Displays the required report without deposits and the report with deposits.
void AirgeadBankingApp::displayReports() const {
    displayInvestmentReport(
        0.0,
        "Balance and Interest Without Additional Monthly Deposits");

    displayInvestmentReport(
        m_monthlyDeposit,
        "Balance and Interest With Additional Monthly Deposits");
}

// Calculates monthly compound interest and displays yearly totals.
void AirgeadBankingApp::displayInvestmentReport(
    double t_monthlyDeposit,
    const std::string& t_title) const {

    std::cout << "\n\n" << t_title << '\n';
    std::cout << std::string(76, '=') << '\n';

    std::cout << std::left
        << std::setw(10) << "Year"
        << std::right
        << std::setw(28) << "Year End Balance"
        << std::setw(38) << "Year End Earned Interest"
        << '\n';

    std::cout << std::string(76, '-') << '\n';

    double currentBalance = m_initialInvestment;

    // Process each complete year of the investment.
    for (int year = 1; year <= m_numberOfYears; ++year) {
        double yearlyInterest = 0.0;

        // Compound the investment once per month.
        for (int month = 1; month <= MONTHS_PER_YEAR; ++month) {
            const double totalAmount =
                currentBalance + t_monthlyDeposit;

            const double monthlyInterest =
                totalAmount *
                ((m_annualInterest / PERCENT_CONVERSION) /
                    MONTHS_PER_YEAR);

            // Add the month's interest to the current year's total.
            yearlyInterest += monthlyInterest;

            // The closing balance becomes next month's opening balance.
            currentBalance = totalAmount + monthlyInterest;
        }

        std::cout << std::left
            << std::setw(10) << year
            << std::right
            << std::setw(28) << formatCurrency(currentBalance)
            << std::setw(38) << formatCurrency(yearlyInterest)
            << '\n';
    }
}

// Converts a decimal value into a dollar amount with two decimal places.
std::string AirgeadBankingApp::formatCurrency(
    double t_amount) const {

    std::ostringstream outputStream;

    outputStream << '$'
        << std::fixed
        << std::setprecision(2)
        << t_amount;

    return outputStream.str();
}

// Validates the user's choice to continue or exit.
char AirgeadBankingApp::getRunAgainChoice() const {
    while (true) {
        std::cout
            << "\nWould you like to test another investment plan? (Y/N): ";

        std::string userInput;
        std::getline(std::cin, userInput);

        std::istringstream inputStream(userInput);

        char userChoice = '\0';
        char extraCharacter = '\0';

        // Accept exactly one character, ignoring surrounding spaces.
        if ((inputStream >> userChoice) &&
            !(inputStream >> extraCharacter)) {

            userChoice = static_cast<char>(
                std::toupper(
                    static_cast<unsigned char>(userChoice)));

            if (userChoice == 'Y' || userChoice == 'N') {
                return userChoice;
            }
        }

        std::cout << "Invalid choice. Please enter Y or N.\n";
    }
}