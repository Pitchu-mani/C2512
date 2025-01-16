
#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;

class labTest {
private:
    string testId;
    double resultValue;

public:
    labTest(string testId, double resultValue) : testId(testId), resultValue(resultValue) {}

    double getresultValue() const {
        return resultValue;
    }
};

struct Message {
    long msg_type;
    double data[100];
};

void client(int msgid) {
    vector<labTest> labTests = {
        labTest("101", 3.4), 
        labTest("102", 7.5), 
        labTest("103", 8.9), 
        labTest("104", 16.7), 
        labTest("105", 9.7)
    };

    int size = labTests.size();
    Message msg;
    msg.msg_type = 1;

    for (int i = 0; i < size; ++i) {
        msg.data[i] = labTests[i].getresultValue();
    }

    cout << "Client sending test results: ";
    for (int i = 0; i < size; ++i) {
        cout << msg.data[i] << " ";
    }
    cout << endl;

    msgsnd(msgid, &msg, sizeof(msg.data), 0);

    double sum;
    msgrcv(msgid, &msg, sizeof(msg.data), 2, 0);
    sum = msg.data[0];
    cout << "Client received sum from server: " << sum << endl;
}

void server(int msgid) {
    Message msg;
    double sum = 0;

    msgrcv(msgid, &msg, sizeof(msg.data), 1, 0);

    cout << "Server received test results: ";
    for (int i = 0; i < 5; ++i) {
        cout << msg.data[i] << " ";
        sum += msg.data[i];
    }
    cout << endl;

    cout << "Server calculated sum: " << sum << endl;

    msg.msg_type = 2;
    msg.data[0] = sum;
    msgsnd(msgid, &msg, sizeof(msg.data), 0);
}

int main() {
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Message queue creation failed");
        return 1;
    }

    {
        int pid = fork();
        if (pid == 0) {
            client(msgid);
            return 0;
        }
    }

    {
        int pid = fork();
        if (pid == 0) {
            server(msgid);
            return 0;
        }
    }

    wait(nullptr);
    wait(nullptr);

    msgctl(msgid, IPC_RMID, nullptr);
    return 0;
}
