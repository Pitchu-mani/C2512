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

void findSum(double a[], int size, double& sum) {
    for (int i=0; i<size;i++) {
        sum = sum + a[i];
    }
}

void client(const vector<LabTest>& labTests, int& write_end_fd1, int& read_end_fd2) {
    int size = labTests.size();
    write(write_end_fd1, &size, sizeof(size));


    double resultValues[size]; //here i need to change the buffer into resultValues like array
    for(int i=0;i<labTests.size();i++)
    {
        resultValues[i]=(labTests[i].getResultValue());
    }

    write(write_end_fd1, resultValues , sizeof(resultValues));
    close(write_end_fd1);

    sleep(1);

    double sum;
    read(read_end_fd2, &sum, sizeof(double));

    cout << "Total sum : " << sum << endl;
    close(read_end_fd2);
}

void server(int& read_end_fd1, int& write_end_fd2) {
    int size;
    read(read_end_fd1, &size , sizeof(size));

    double resultValues[size];
    read(read_end_fd1, resultValues , size * sizeof(double));

    cout << "Server: Received results from client." << endl;
    close(read_end_fd1);

    double sum = 0;
    findSum(resultValues , size, sum);

    write(write_end_fd2, &sum, sizeof(sum));
    cout << "Server: Sent sum back to client: " << sum << endl;
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
    if(pipe(pipe_fd1)==-1)
    {
        perror("pipe");
        cout << "pipe not created" << endl;
        return 1;
    }
	if(pipe(pipe_fd2)==-1)
    {
        perror("pipe");
        cout << "pipe not created" << endl;
        return 1;
    }

    int& read_end_fd1 = pipe_fd1[0];
    int& write_end_fd1 = pipe_fd1[1];
    int& write_end_fd2 = pipe_fd2[1];
    int& read_end_fd2 = pipe_fd2[0];

    pid_t pid = -1;

    {
		pid = fork();
        if(0==pid){
			close(read_end_fd1);
			client(labTests,write_end_fd1,read_end_fd2);
			return 0;
		}
    }

	{
		pid = fork();
		if(0==pid){
			close(write_end_fd1);
			server(read_end_fd1,write_end_fd2);
			return 0;
		}
	}
    sleep(2);
    return 0;
}

