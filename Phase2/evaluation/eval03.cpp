#include<iostream>
#include<vector>
#include<climits>
#include<string>
#include<thread>
#include<algorithm>
#include<unistd.h>
#include<cstring>

using namespace std;

class labTest {
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


void findSum(const vector<labTest>& labTests, double& sum) {
    for (auto& test : labtests) {
        sum += test.getResultValue();
    }
}


void client( vector<labTest>& labTests, int& write_end_fd1, int& read_end_fd2){
	int size =labtests.size();
	write(write_end_fd1, &size, 4);
	int buffer[size];
	for(int i = 0; i < labtests.size(); i++){
		buffer[i]=(labTests[i].getResultValue());
	}
	write(write_end_fd1, buffer, sizeof(buffer));
	
	cout << "client : " << buffer[1] << endl;
	close(write_end_fd1);
	sleep(2);

	int sum=0;
	read(read_end_fd2, &sum, sizeof(int));

	cout << "total sum : "<< sum << endl;
	close(read_end_fd2);


}

void server(int& read_end_fd1,int& write_end_fd2){
	sleep(1);

	int size;

	read(read_end_fd1,&size,sizeof(size));

	int a[size];

	read(read_end_fd1,
	a,
	sizeof(int)*size);

	cout << "server ..." << endl;
	close(read_end_fd1);
	int s= 0; 
	findSum(a,s);
	write(write_end_fd2, &s, sizeof(s));
	cout << "sum sent : " <<s<< endl;
	close(write_end_fd2);

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

    int pipe_fd1[2];
    int pipe_fd2[2];
    if(pipe(pipe_fd1)==-1){
        perror("pipe");
        cout << "pipe not created" << endl;
        return 1;
    }
	if(pipe(pipe_fd2)==-1){
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
			client(vec,write_end_fd1,read_end_fd2);
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


	sleep(3);

	return 0;


}
