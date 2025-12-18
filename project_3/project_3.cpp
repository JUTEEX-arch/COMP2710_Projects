//  How to compile code: g++ project_3.cpp
//  How to run code: ./a.out
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// I had big troubles actually  understanding and coding the functions that check if the input in a file is valid and I didn't have anough time
// to actually think about the logic (yes, 2 weeks is not enough), so I used chatGPT to help me with this.
// The following 2 functions below are basically checking if the  input is a legal number, checks if it is empty and if it has only 1 decimal point in it
bool isValidNumber(const std::string &s)
{
    if (s.empty())
        return false;

    size_t i = 0;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s.size() == 1)
            return false;
        i++;
    }

    bool hasDigit = false;
    bool hasDecimalPoint = false;

    for (; i < s.size(); i++)
    {
        if (std::isdigit(static_cast<unsigned char>(s[i])))
        {
            hasDigit = true;
        }
        else if (s[i] == '.')
        {
            if (hasDecimalPoint)
                return false;
            hasDecimalPoint = true;
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}
bool checkFileForValidNumbers(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file\n";
        return false;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line))
    {
        lineNumber++;
        if (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();

        if (!isValidNumber(line))
        {
            return false;
        }
    }

    return true;
}
// ChatGPT bullshit ends here, the rest of the code is mine

// methods for mean and meadian
double mean(const vector<double> &v)
{
    double sum = 0.0;
    for (size_t i = 0; i < v.size(); i++)
        sum += v[i];
    return sum / v.size();
}
double median(const vector<double> &v)
{
    if (v.empty())
        return 0.0;
    size_t n = v.size();
    if (n % 2 == 1)
        return v[n / 2]; //
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

// main
int main(int argc, char const *argv[])
{
    int num_files;
    std::cout << "Enter the number of files to read: ";
    std::cin >> num_files;
    // pushing values into a vector instead of array because we need a dynamic data structure
    vector<double> values;
    for (int i = 1; i <= num_files; i++)
    {
        string filename;

        while (true)
        {
            cout << "\nEnter the filename for file " << i << ": ";
            cin >> filename;

            if (checkFileForValidNumbers(filename))
            {
                ifstream inputFile(filename);
                string line;
                while (getline(inputFile, line))
                {
                    cout << line << endl;
                    values.push_back(stod(line));
                }
                inputFile.close();
                break;
            }
            else
            {
                cout << "Invalid File\n";
            }
        }
    }
    // sorting vector and calling mean and median functions (didn't have time to write mode function)
    std::sort(values.begin(), values.end());
    cout << "Sorted list" << endl;
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << values[i] << " ";
    }
    cout << " " << endl;

    cout << "Mean = " << mean(values) << endl;
    cout << "Median = " << median(values) << endl;
    return 0;
}
