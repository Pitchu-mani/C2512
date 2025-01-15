#include <iostream>
#include <vector>
#include <string>
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

void findSum(const vector<double>& results, double& sum) {
    for (const auto& value : results) {
        sum += value;
    }
}

void client(const vector<LabTest>& labTests, int write_end_fd1, int read_end_fd2) {
    int size = labTests.size();
    write(write_end_fd1, &size, sizeof(size));

    vector<double> resultValues;
    for (const auto& test : labTests) {
        resultValues.push_back(test.getResultValue());
    }
    write(write_end_fd1, resultValues.data(), resultValues.size() * sizeof(double));

    cout << "Client: Sent results to the server." << endl;
    close(write_end_fd1);

    double sum = 0;
    read(read_end_fd2, &sum, sizeof(double));

    cout << "Total sum received by client: " << sum << endl;
    close(read_end_fd2);
}

void server(int read_end_fd1, int write_end_fd2) {
    int size;
    read(read_end_fd1, &size, sizeof(size));

    vector<double> results(size);
    read(read_end_fd1, results.data(), size * sizeof(double));

    cout << "Server: Received results from the client." << endl;
    close(read_end_fd1);

    double sum = 0;
    findSum(results, sum);

    write(write_end_fd2, &sum, sizeof(sum));
    cout << "Server: Sent sum back to the client: " << sum << endl;
    close(write_end_fd2);
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

    int pipe_fd1[2];
    int pipe_fd2[2];
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1) {
        perror("pipe");
        cout << "Pipe creation failed." << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process (Client)
        close(pipe_fd1[0]); // Close unused read end of pipe 1
        close(pipe_fd2[1]); // Close unused write end of pipe 2
        client(labTests, pipe_fd1[1], pipe_fd2[0]);
        return 0;
    } else if (pid > 0) {
        // Parent process (Server)
        close(pipe_fd1[1]); // Close unused write end of pipe 1
        close(pipe_fd2[0]); // Close unused read end of pipe 2
        server(pipe_fd1[0], pipe_fd2[1]);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
