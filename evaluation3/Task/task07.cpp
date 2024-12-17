#include <iostream>
#include <iomanip>
#include <deque>
#include <string>

using namespace std;

// *****LabTest.h*****
class LabTest
{
    friend class LabTestManager;
private:
    string TestID;
    double ResultValue;
};

// *****LabTestManager.h*****
class LabTestManager
{
private:
    // attributes
    deque<LabTest> LabTests;

public:
    // support
    int findIndexById(const string& TestID);
    // behaviours
    void create();
    void displayAll();
    void editById();
    void deleteById();

    LabTestManager();
};

// *****Menu.h*****
void printMenu();

// *****Main.cpp*****
int main()
{
    LabTestManager manager;

    int choice; // User's menu choice

    do
    {
        printMenu(); // Display menu
        cout << "Enter your choice: ";
        cin >> choice;

        // Menu-driven functionality
        switch (choice)
        {
        case 1:
            manager.create();
            break;
        case 2:
            manager.displayAll();
            break;
        case 3:
            manager.editById();
            break;
        case 4:
            manager.deleteById();
            break;
        case 5:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

void LabTestManager::create()
{
    string TestID;
    double ResultValue;

    cout << "Enter Test ID: ";
    cin >> TestID;

    // Ensure Test ID is unique
    if (findIndexById(TestID) != -1)
    {
        cout << "Error: Test ID already exists. Please use a unique ID.\n";
        return;
    }

    cout << "Enter ResultValue: ";
    cin >> ResultValue;

    // Add new LabTest to the deque
    LabTest newTest;
    newTest.TestID = TestID;
    newTest.ResultValue = ResultValue;
    LabTests.push_back(newTest);

    cout << "Test created successfully.\n";
}

void LabTestManager::displayAll()
{
    if (LabTests.empty())
    {
        cout << "No Tests available to display.\n";
        return;
    }

    cout << "---------------------------------\n";
    cout << "| Test ID       | Result Value   |\n";
    cout << "---------------------------------\n";
    for (auto test : LabTests)
    {
        cout << "| " << "\t" << test.TestID
             << "\t|" << "\t" << test.ResultValue << "\t|\n";
    }
    cout << "---------------------------------\n";
}

int LabTestManager::findIndexById(const string& TestID)
{
    for (size_t i = 0; i < LabTests.size(); i++)
    {
        if (LabTests[i].TestID == TestID)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void LabTestManager::editById()
{
    string TestID;
    cout << "Enter Test ID to edit: ";
    cin >> TestID;

    int index = findIndexById(TestID);
    if (index == -1)
    {
        cout << "Error: Test ID not found.\n";
        return;
    }

    cout << "Current Details - ResultValue: " << LabTests[index].ResultValue << "\n";

    cout << "Enter New ResultValue: ";
    cin >> LabTests[index].ResultValue;

    cout << "LabTest updated successfully.\n";
}

void LabTestManager::deleteById()
{
    string TestID;
    cout << "Enter Test ID to delete: ";
    cin >> TestID;

    int index = findIndexById(TestID);
    if (index == -1)
    {
        cout << "Error: Test ID not found.\n";
        return;
    }

    // Remove the LabTest from the deque
    LabTests.erase(LabTests.begin() + index);

    cout << "Test deleted successfully.\n";
}

LabTestManager::LabTestManager() {}

// *****Menu.cpp*****
void printMenu()
{
    cout << "\n=== LabTest Management System ===\n";
    cout << "1. Create LabTest\n";
    cout << "2. Display All LabTests\n";
    cout << "3. Edit LabTest\n";
    cout << "4. Delete LabTest\n";
    cout << "5. Exit\n";
}
