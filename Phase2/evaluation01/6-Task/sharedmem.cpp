#include<iostream>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<cstring>
#include <string>
#include<vector>
using namespace std;

#define SHM_KEY 1234

class labTest{
    private:
       string testId;
       int resultValue;
    public:
       labTest(string p_TestId , int p_ResultValue ) 
            : testId(p_TestId) , resultValue(p_ResultValue) {}

       int getResultValue() const
       {
         return resultValue;
       }
};

void findSum(int *array, int size, int& sum) {
    for (int i=1; i<=size;i++) {
        sum = sum + array[i];
    }
}

void client(const vector<labTest>& labTests, int shmid) { 
    int* resultValues = (int*)shmat(shmid, nullptr, 0); 

    int size = labTests.size();
    resultValues[0] = size;
    for(int i=1;i<=size;i++) {
        resultValues[i] = labTests[i-1].getResultValue(); 
    }

    // Print the message written
    cout << "Message is written to shared memory" << endl;
    for(int i = 0; i <= size; i++){
        cout << resultValues[i] << " ";  
    }
    cout << endl;

    shmdt(resultValues); 
}

// resultValue[1]  => *(resultValue + 1)

void server(int shmid) { //child 2
    int* resultValues = (int*)shmat(shmid, nullptr, 0); 
    int sum = 0;
    int size = resultValues[0]; 

    // for (int i = 0; i < size; i++) {
    //     sum += resultValues[i];
    // }
    
    findSum(resultValues, size, sum);   
    cout << "Sum of results retrieved from shared memory: " << sum << endl;

    shmdt(resultValues); // detach shared memory
}

int main() { 
    int n;
    cout << "Enter the number of lab tests: ";
    cin >> n;

    vector<labTest> labTests;
    for (int i = 1; i <= n; ++i) {
        string testId;
        int resultValue;
        cout << "Enter test ID and result value for test " << i << ": ";
        cin >> testId >> resultValue;
        labTests.emplace_back(testId, resultValue);
    }

    int shmid = shmget(SHM_KEY, sizeof(int) * n, 0666 | IPC_CREAT);   
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child 1: Client process
        sleep(1); // simulate delay
        client(labTests, shmid);
        return 0;
    }

    pid = fork();
    if (pid == 0) {
        sleep(2); // ensure the client writes first
        server(shmid);
        shmctl(shmid, IPC_RMID, nullptr); 
        return 0;
    }

    wait(nullptr);
    wait(nullptr);

    return 0;
}
