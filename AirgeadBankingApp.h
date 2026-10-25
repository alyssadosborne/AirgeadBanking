#ifndef AIRGEAD_BANKING_AIRGEAD_BANKING_APP_H_
#define AIRGEAD_BANKING_AIRGEAD_BANKING_APP_H_

#include <string>

// Controls the Airgead Banking user interface and investment calculations.
class AirgeadBankingApp {
public:
    // Initializes all investment values to safe starting values.
    AirgeadBankingApp();

    // Runs the application until the user chooses to exit.
    void run();

private:
    // Investment information entered by the user.
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterest;
    int m_numberOfYears;

    // Collects and stores all required investment information.
    void collectUserInput();

    // Returns a validated positive decimal value.
    double getPositiveDouble(const std::string& t_prompt) const;

    // Returns a validated positive whole-number value.
    int getPositiveInteger(const std::string& t_prompt) const;

    // Pauses the program until the user presses Enter.
    void waitForEnter() const;

    // Displays both required investment reports.
    void displayReports() const;

    // Calculates and displays one yearly investment report.
    void displayInvestmentReport(
        double t_monthlyDeposit,
        const std::string& t_title) const;

    // Formats a number as currency with two decimal places.
    std::string formatCurrency(double t_amount) const;

    // Asks whether the user wants to perform another calculation.
    char getRunAgainChoice() const;
};

#endif // AIRGEAD_BANKING_AIRGEAD_BANKING_APP_H_