//Vasin Daniil
//project1_dzv0026_Vasin_Daniil.cpp
// How to compile code: g++ project1_dzv0026_Vasin_Daniil.cpp
// How to run code: ./a.out

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double loan_amt, interest, mnth_pymnt;
    int month_count = 0;
    double ttl_intrst = 0;
    cout << "Loan Amount: ";
    cin >> loan_amt;
//Asked Chingis(my friend form this class) on how to check if the input is a valid number or not
    if (std::cin.fail()){
        cout << "Error: Not a number" << endl;
    }
    cout << "Interest Rate (% per year): ";
    cin >> interest;
    if (std::cin.fail()){
        cout << "Error: Not a number" << endl;
    }
    cout << "Monthly Payments: ";
    cin >> mnth_pymnt;
    if (std::cin.fail()){
        cout << "Error: Not a number" << endl;
    }
    double monthly_intrst = interest / 12;
//Asked chatgpt how to format output in CPP
    cout << "***********************************************************" << endl;
    cout << "     Amortization Table" << endl;
    cout << "***********************************************************" << endl;
    cout << left << setw(8) << "Month"<< setw(12) << "Balance"<< setw(10) << "Payment"<< setw(10) 
    << "Interest" << setw(10) << "Rate" <<  setw(10) << "Principal" << endl;
//Special Case for "wierd" inputs, should give an error
    if (loan_amt < 0 || interest < 0 || mnth_pymnt < 0) {
        cout << "Error: Invalid negative input" << endl;
        return 1;
    }
    cout << left << fixed << setprecision(2) << setw(8) << month_count << "$" << setw(12) << loan_amt << setw(10) << "N/A" << setw(10) 
    << "N/A" << setw(10) << "N/A" << setw(10) << "N/A" << setw(10) << endl;

    while (loan_amt > 0) {
        double curr_interest = (loan_amt / 100) * monthly_intrst;
        double curr_payment = mnth_pymnt - curr_interest;
        double principal = mnth_pymnt - curr_interest;
        ttl_intrst = ttl_intrst + curr_interest;
//Special Case for small payment
        if (mnth_pymnt < curr_interest) {
            cout << "Error: Payment too small" << endl;
            break;
        }
//asked chatgpt again how to make an output, set amount of decimal digits
//looked up how to make loops and if-else statements on "stack overflow"
        if (loan_amt >= curr_payment) {
            loan_amt -= curr_payment;
            month_count++;
            cout << left << setw(8) << month_count << "$"
                 << setw(12) << fixed << setprecision(2) << loan_amt
                 << setw(10) << mnth_pymnt << setw(10) << monthly_intrst
                 << setw(10) << curr_interest << setw(10) << principal << endl;
        } else {
            mnth_pymnt = loan_amt + curr_interest;
            month_count++;
            loan_amt = 0;
            cout << left << setw(8) << month_count << "$"
                 << setw(12) << fixed << setprecision(2) << loan_amt
                 << setw(10) << mnth_pymnt << setw(10) << monthly_intrst
                 << setw(10) << curr_interest << setw(10) << principal << endl;
        }
    }
        cout << "***********************************************************" << endl;
        cout << endl;
        cout << endl;
        cout << "It takes " << month_count << " months to pay off the loan." << endl;
        cout << "Total interest paid is: $" << ttl_intrst << endl;
    
    return 0;
}
