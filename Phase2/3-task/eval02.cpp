#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

class LabTest {
private:
    string testId;
    double resultValue;

public:
    LabTest(string p_TestID, double p_ResultValue)
        : testId(p_TestID), resultValue(p_ResultValue) {}

    double getResultValue() const {
        return resultValue;
    }
};


void findSum(const vector<LabTest>& labTests, double& sum) {
    for (auto& test : labTests) {
        sum += test.getResultValue();
    }
}

void findMinInFirstHalf(const vector<LabTest>& labTests, double& min, int n) {
    for (int i = 0; i < n / 2; i++){
        min = min < labTests[i].getResultValue() ? min : labTests[i].getResultValue();
    }
}

void findMaxInSecondHalf(const vector<LabTest>& labTests, double& max, int n) {
    for (int i = n / 2; i < n; i++) {
        max = max > labTests[i].getResultValue() ? max : labTests[i].getResultValue();
    }
}

int main() {
    int n;
    cout << "Enter the number of lab tests: " << endl;
    cin >> n;

    vector<LabTest> labTests;
    for (int i = 1; i <= n; ++i) {
        string testId;
        double resultValue;
        cout << "Enter test ID and result value for test " << i << ":" << endl;
        cin >> testId >> resultValue;
        LabTest test(testId, resultValue);
        labTests.push_back(test);
    }
    double sum = 0;
    double max = INT_MIN;
    double min = INT_MAX;

    thread thrFindSum(findSum, ref(labTests), ref(sum));
    thread thrFindMinInFirstHalf(findMinInFirstHalf, ref(labTests), ref(min), ref(n));
    thread thrFindMaxInSecondHalf(findMaxInSecondHalf, ref(labTests), ref(max), ref(n));

    thrFindSum.join();
    thrFindMinInFirstHalf.join();
    thrFindMaxInSecondHalf.join();

    cout << "Sum is " << sum << endl;
    cout << "Max is " << max << endl;
    cout << "Min is " << min << endl;

    return 0;
}

