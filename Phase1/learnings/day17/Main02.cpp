#include <iostream>
#include <iomanip>
#include <string>
using std::string;

class LabTest
{
        private:
            string TestID;
            double ResultValue;
        public:
            LabTest(string p_TestID , double ResultValue); //Contructor
            friend bool LessThan(const LabTest& first, const LabTest& second);
            friend bool Equals(const LabTest& first ,const LabTest& second);
            friend bool NotEquals(const LabTest& first ,const LabTest& second);
            friend bool GreaterThan(const LabTest& first , const LabTest& second);
            friend bool LessThanEquals(const LabTest& first , const LabTest& second);
            friend bool GreaterThanEquals(const LabTest& first , const LabTest& second);
};
bool LessThan(const LabTest& first, const LabTest& second);
bool Equals(const LabTest& first ,const LabTest& second);
bool NotEquals(const LabTest& first ,const LabTest& second);
bool GreaterThan(const LabTest& first , const LabTest& second);
bool LessThanEquals(const LabTest& first , const LabTest& second);
bool GreaterThanEquals(const LabTest& first , const LabTest& second);


int main() {
    LabTest lt1("LT001", 75.5);
    LabTest lt2("LT002", 80.0);

    std::cout << std::boolalpha;
    std::cout << "Equals: " << Equals(lt1,lt2) << std::endl;
    std::cout << "GreaterThan: " << GreaterThan(lt1,lt2) << std::endl;
    std::cout << "LessThanEquals: " << LessThanEquals(lt1,lt2) << std::endl;
    std::cout << "NotEquals: " << NotEquals(lt1,lt2) << std::endl;
    std::cout << "GreaterThanEquals: " << GreaterThanEquals(lt1,lt2) << std::endl;
    std::cout << "LessThan: " << LessThan(lt1,lt2) << std::endl;

    return 0;
}

//Constructor

LabTest::LabTest(string p_TestID, double p_ResultValue)
{
    TestID = p_TestID;
    ResultValue = p_ResultValue;
}


bool Equals(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue == second.ResultValue);
}

bool NotEquals(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue != second.ResultValue);
}

bool GreaterThan(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue > second.ResultValue);
}

bool GreaterThanEquals(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue >= second.ResultValue);
}

bool LessThan(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue < second.ResultValue);
}

bool LessThanEquals(const LabTest& first, const LabTest& second)
{
    return (first.ResultValue <= second.ResultValue);
}

