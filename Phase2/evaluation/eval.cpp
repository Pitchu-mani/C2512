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
