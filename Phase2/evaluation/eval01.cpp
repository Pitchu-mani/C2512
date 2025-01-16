#include <iostream>
#include <climits>
#include <vector>
#include <string>
using namespace std;

class LabTest
{
private:
    string testId;
    double resultValue;

public:
    LabTest(string p_TestID, double p_ResultValue)
        : testId(p_TestID), resultValue(p_ResultValue) {}

    double getResultValue() const
    {
        return resultValue;
    }
};

int findSum(const vector<LabTest> &LabTests)
{
    int sum = 0;
    for (auto &test : LabTests)
    {
        sum = sum+test.getResultValue();
    }
    return sum;
}

int findMinInFirstHalf(const vector<LabTest> &LabTests)
{
    int min = INT_MAX;
    int n = LabTests.size();
    for (int i = 0; i < n / 2; ++i)
    {
        min = (min < LabTests[i].getResultValue()) ? min : LabTests[i].getResultValue();
    }
    return min;
}

int findMaxInSecondHalf(const vector<LabTest> &LabTests)
{
    int max = INT_MIN;
    int n = LabTests.size();
    for (int i = n / 2; i < n; ++i)
    {
        max = (max > LabTests[i].getResultValue()) ? max : LabTests[i].getResultValue();
    }
    return max;
}

int main()
{
    int n;
    cout << "Enter the number of Lab tests:" << endl;
    cin >> n;

    vector<LabTest> LabTests;
    for (int i = 1; i <= n; ++i)
    {
        string testId;
        double resultValue;
        cout << "Enter test ID and result value for test " << i << ":" << endl;
        cin >> testId >> resultValue;
        LabTest test(testId, resultValue);
        LabTests.push_back(test);
    }

    int result = findSum(LabTests);
    cout << "sum is: " << result << endl;

    int resultFirstMin = findMinInFirstHalf(LabTests);
    cout << "min in first half is: " << resultFirstMin << endl;

    int resultSecondMax = findMaxInSecondHalf(LabTests);
    cout<<"max in second half is :" << resultSecondMax << endl;

    return 0;

}
