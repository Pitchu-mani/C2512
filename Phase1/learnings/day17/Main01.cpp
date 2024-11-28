
========================================= LabTest.h =============================================

#pragma once

#include <string>

using std::string;

class LabTest
{
    private:
        string TestID;
        double ResultValue;
    public:
        //behaviours
        bool Equals(const LabTest& other);
        bool NotEquals(const LabTest& other);
        bool GreaterThan(const LabTest& other);
        bool GreaterThanEquals(const LabTest& other);
        bool LessThan(const LabTest& other);
        bool LessThanEquals(const LabTest& other);
        //constructor
        LabTest(string p_TestID, double p_ResultValue);
};

========================================== Main.cpp =======================================

#include <iostream>
#include <iomanip>

#include "LabTest.h"
int main() {
    LabTest lt1("LT001", 75.5);
    LabTest lt2("LT002", 80.0);

    std::cout << std::boolalpha;
    std::cout << "Equals: " << lt1.Equals(lt2) << std::endl;
    std::cout << "GreaterThan: " << lt1.GreaterThan(lt2) << std::endl;
    std::cout << "LessThanEquals: " << lt1.LessThanEquals(lt2) << std::endl;
    std::cout << "NotEquals: " << lt1.NotEquals(lt2) << std::endl;
    std::cout << "GreaterThanEquals: " << lt1.GreaterThanEquals(lt2) << std::endl;
    std::cout << "LessThan: " << lt1.LessThan(lt2) << std::endl;

    return 0;
}

============================================== LabTest.cpp =================================

#include <string>

#include "LabTest.h"

using std::string;

//behaviours
bool LabTest::Equals(const LabTest& other)
{
    return (ResultValue == other.ResultValue);
}

bool LabTest::NotEquals(const LabTest& other)
{
    return (ResultValue != other.ResultValue);
}

bool LabTest::GreaterThan(const LabTest& other)
{
    return (ResultValue > other.ResultValue);
}

bool LabTest::GreaterThanEquals(const LabTest& other)
{
    return (ResultValue >= other.ResultValue);
}

bool LabTest::LessThan(const LabTest& other)
{
    return (ResultValue < other.ResultValue);
}

bool LabTest::LessThanEquals(const LabTest& other)
{
    return (ResultValue <= other.ResultValue);
}

//constructor

LabTest::LabTest(string p_TestID, double p_ResultValue)
{
    TestID = p_TestID;
    ResultValue = p_ResultValue;
}
