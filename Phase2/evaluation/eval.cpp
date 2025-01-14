#include <iostream>
#include <climits>
#include <vector>
using namespace std;

class labTest
{
    private:
      string testId;
      double resultValue;
   public:
        labTest(string p_TestID, double p_ResultValue)
        {
           TestID = p_TestID;
           ResultValue = p_ResultValue;
       }
}; 


int findSum(const vector<int> &input)
{
    int sum = 0;
    for(auto number:input)
    {
       sum=sum+number[1];
    }
    return sum;
}

int findMinInFirstHalf(const vector<int> &input)
{
    int min = INT_MAX;
    for(int i=0;i<=(n/2);i++)
    {
      min = min<input[i][1] ? input[i][1] : min;
    }
    return min;
}

int findMaxInSecondHalf(const vector<int> &input)
{
    int max = INT_MIN;
    for(int i=n/2;i<=n;i++)
    {
      max = max>input[i][1] ? input[i][1] : min;
    }
    return max;
}

int main()
{
     int n;
     cout << "Enter the number of Labtest :" <<endl;
     cin >> n;
     vector<int> input;
     for(int i=1 ; i<=n ;i++)
     {  
          labtest test;
          input.push_back(test);
     }
     result = findSum(ref(input));
     cout << "The find sum is : " << result << endl;
     resultfirstmin = findMinInFirstHalf(ref(input);
     cout << " The min of first half is : " << resultfirstmin << endl;
     resultsecondhalf = findMaxInSecondHalf(ref(input);
     cout << " The Max  of second half is : " << resultsecondmax << endl;
     return 0;
        
}
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
    for (const auto &test : input)
    {
        sum += test.getResultValue();
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
    for (int i = 0; i < n; ++i)
    {
        string testId;
        double resultValue;
        cout << "Enter test ID and result value for test " << i + 1 << ":" << endl;
        cin >> testId >> resultValue;
        LabTest test(testId, resultValue);
        input.push_back(test);
    }

    int result = findSum(input);
    cout << "The sum of results is: " << result << endl;

    int resultFirstMin = findMinInFirstHalf(input);
    cout << "The minimum value in the first half is: " << resultFirstMin << endl;

    int resultSecondMax = findMaxInSecondHalf

