#include <iostream>
#include <vector>
#include <string>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

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

void findSum(double a[], int size, double& sum) {
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }
}

void client(const vector<LabTest>& labTests, double* shared_memory, int& shared_size) {
    int size = labTests.size();
    shared_memory[0] = size; // Store the size in shared memory

    for (int i = 0; i < size; i++) {
        shared_memory[i + 1] = labTests[i].getResultValue(); // Store result values in shared memory
    }
    
    cout << "Client: Written data to shared memory.\n";
    shared_size = size + 1;

    while (shared_memory[shared_size] == 0) {
        // Wait for server to write the sum
    }

    double sum = shared_memory[shared_size];
    cout << "Total sum: " << sum << endl;
}

void server(double* shared_memory, int shared_size) {
    int size = static_cast<int>(shared_memory[0]); // Retrieve the size
    double resultValues[size];
    
    for (int i = 0; i < size; i++) {
        resultValues[i] = shared_memory[i + 1]; // Retrieve the result values
    }
    
    cout << "Server: Received results from shared memory.\n";

    double sum = 0;
    findSum(resultValues, size, sum);

    shared_memory[shared_size] = sum; // Write the sum to shared memory
    cout << "Server: Written sum to shared memory: " << sum << endl;
}

int main() {
    int n;
    cout << "Enter the number of lab tests: ";
    cin >> n;

    vector<LabTest> labTests;
    for (int i = 1; i <= n; ++i) {
        string testId;
        double resultValue;
        cout << "Enter test ID and result value for test " << i << ": ";
        cin >> testId >> resultValue;
        labTests.emplace_back(testId, resultValue);
    }

    // Create shared memory
    int shared_size = n + 2; // One for size, n for results, one for sum
    double* shared_memory = static_cast<double*>(mmap(nullptr, shared_size * sizeof(double),
                                                      PROT_READ | PROT_WRITE,
                                                      MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    memset(shared_memory, 0, shared_size * sizeof(double)); // Initialize shared memory

    pid_t pid = fork();

    if (pid == 0) { // Client process
        client(labTests, shared_memory, shared_size);
        return 0;
    } else if (pid > 0) {
        pid = fork();
        if (pid == 0) { // Server process
            server(shared_memory, shared_size);
            return 0;
        } else if (pid > 0) {
            // Parent process waits for children to complete
            wait(nullptr);
            wait(nullptr);

            // Cleanup shared memory
            munmap(shared_memory, shared_size * sizeof(double));
        } else {
            perror("fork");
            return 1;
        }
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

