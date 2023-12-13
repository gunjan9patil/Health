#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class BMICalculator
{
public:
    virtual double calculateBMI(double weight, double height) = 0;
    virtual void interpretBMI(double bmi) = 0;
    virtual double calculateBFI(double bmi, double age, char gender) = 0;
    virtual double calculateWaistToHeightRatio(double waist, double height) = 0;
    virtual double calculateBAI(double hipCircumference, double height) = 0;
};

class StandardBMICalculator : public BMICalculator
{
public:
    double calculateBMI(double weight, double height) override
    {
        return weight / ((height / 100.0) * (height / 100.0));
    }

    void interpretBMI(double bmi) override
    {
        cout << "Your BMI is: " << fixed << setprecision(2) << bmi << endl;

        if (bmi < 18.5)
        {
            cout << "Underweight" << endl;
        }
        else if (bmi >= 18.5 && bmi < 25)
        {
            cout << "Normal weight" << endl;
        }
        else if (bmi >= 25 && bmi < 30)
        {
            cout << "Overweight" << endl;
        }
        else
        {
            cout << "Obese" << endl;
        }
    }

    double calculateBFI(double bmi, double age, char gender) override
    {
        double bfi = bmi * age / (gender == 'M' ? 1.0 : 2.0);
        return bfi;
    }

    double calculateWaistToHeightRatio(double waist, double height) override
    {
        return waist / height;
    }

    double calculateBAI(double hipCircumference, double height) override
    {
        return hipCircumference / (height / 100.0) - 18;
    }
};

class BMICategory : public StandardBMICalculator
{
public:
    void categorizeBMI(double bmi)
    {
        if (bmi < 16)
        {
            cout << "Severely Underweight" << endl;
        }
        else if (bmi >= 16 && bmi < 18.5)
        {
            cout << "Underweight" << endl;
        }
        else
        {
            StandardBMICalculator::interpretBMI(bmi);
        }
    }
};

class UserInterface
{
public:
    static char getRepeatChoice()
    {
        char repeat;
        cout << "Do you want to calculate again? (y/n): ";
        cin >> repeat;
        return repeat;
    }

    static char getIndexChoice()
    {
        char choice;
        cout << "Select the index to calculate (B - BMI, F - Body Fat Index, W - Waist-to-Height Ratio, A - Body Adiposity Index): ";
        cin >> choice;
        return toupper(choice);
    }
};

int main()
{
    char calculateAgain;
    char indexChoice;
    double bfi, whr, bai;

    do
    {
        double weight, height, waist, hipCircumference, age;
        char gender;

        cout << "BMI Calculator" << endl;
        cout << "Enter your weight (in kilograms): ";
        cin >> weight;
        cout << "Enter your height (in centimeters): ";
        cin >> height;

        if (weight <= 0 || height <= 0)
        {
            cout << "Invalid input. Weight and height must be positive values." << endl;
            return 1;
        }

        BMICategory bmiCalculator;
        double bmi = bmiCalculator.calculateBMI(weight, height);

        indexChoice = UserInterface::getIndexChoice();

        switch (indexChoice)
        {
        case 'B':
            bmiCalculator.categorizeBMI(bmi);
            break;

        case 'F':
            cout << "Enter your age: ";
            cin >> age;
            cout << "Enter your gender (M/F): ";
            cin >> gender;
            bfi = bmiCalculator.calculateBFI(bmi, age, gender);
            cout << "Your Body Fat Index (BFI) is: " << fixed << setprecision(2) << bfi << endl;
            break;

        case 'W':
            cout << "Enter your waist circumference (in centimeters): ";
            cin >> waist;
            whr = bmiCalculator.calculateWaistToHeightRatio(waist, height);
            cout << "Your Waist-to-Height Ratio is: " << fixed << setprecision(2) << whr << endl;
            break;

        case 'A':
            cout << "Enter your hip circumference (in centimeters): ";
            cin >> hipCircumference;bai = bmiCalculator.calculateBAI(hipCircumference, height);
            cout << "Your Body Adiposity Index (BAI) is: " << fixed << setprecision(2) << bai << endl;
            break;

        default:
            cout << "Invalid choice. Please select a valid index." << endl;
            break;
        }

        calculateAgain = UserInterface::getRepeatChoice();
    } while (calculateAgain == 'y' || calculateAgain == 'Y');

    cout << "Thanks for using the Index Calculator. Goodbye." << endl;

    return 0;
}
