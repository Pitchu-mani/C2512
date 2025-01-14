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

int findSum(const vector<LabTest> &input)
{
    int sum = 0;
    for (auto &test : input)
    {
        sum = sum+test.getResultValue();
    }
    return sum;
}

int findMinInFirstHalf(const vector<LabTest> &input)
{
    int min = INT_MAX;
    int n = input.size();
    for (int i = 0; i < n / 2; ++i)
    {
        min = (min < input[i].getResultValue()) ? min : input[i].getResultValue();
    }
    return min;
}

int findMaxInSecondHalf(const vector<LabTest> &input)
{
    int max = INT_MIN;
    int n = input.size();
    for (int i = n / 2; i < n; ++i)
    {
        max = (max > input[i].getResultValue()) ? max : input[i].getResultValue();
    }
    return max;
}

int main()
{
    int n;
    cout << "Enter the number of Lab tests:" << endl;
    cin >> n;

    vector<LabTest> input;
    for (int i = 1; i < n; ++i)
    {
        string testId;
        double resultValue;
        cout << "Enter test ID and result value for test " << i << ":" << endl;
        cin >> testId >> resultValue;
        LabTest test(testId, resultValue);
        input.push_back(test);
    }

    int result = findSum(input);
    cout << "The sum of results is: " << result << endl;

    int resultFirstMin = findMinInFirstHalf(input);
    cout << "The min in first half is: " << resultFirstMin << endl;

    int resultSecondMax = findMaxInSecondHalf(input);
    cout<<"The max in the second half is :" << resultSecondMax << endl;

    return 0;

}
