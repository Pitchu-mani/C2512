#include <iostream>
#include <iomanip>

using namespace std;

// *****Const.h*****
// Constants
const int MAX_TESTS = 100;
// *****LabTest.h*****
class LabTest
{
    friend class LabTestManager;

private:
    string TestID;
    double ResultValue;
    // string TestID;
    // double Result_Value
};

// *****LabTestManager.h*****
class LabTestManager
{
private:
    // attributes
    LabTest LabTests[MAX_TESTS];
    int numTests;

public:
    // support
    int findIndexById(string TestID);
    // behaviours
    void create();
    void displayAll();
    void editById();
    void deleteById();
    //
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

// *****LabTestManager.cpp*****
/**
 * @brief Creates a new Test and stores details in arrays.
 */
void LabTestManager::create()
{
    if (numTests >= MAX_TESTS)
    {
        cout << "Error: Maximum Test limit reached.\n";
        return;
    }

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

    // Store the patient details
    LabTests[numTests].TestID = TestID;
    LabTests[numTests].ResultValue = ResultValue;
    numTests++;

    cout << "Test created successfully.\n";
}

/**
 * @brief Displays all existing Testts in a tabular format.
 */
void LabTestManager::displayAll()
{
    if (numTests == 0)
    {
        cout << "No Tests available to display.\n";
        return;
    }

    cout << "---------------------------------\n";
    cout << "|Test ID\t|\tResultvalue\t|\n";
    cout << "---------------------------------\n";
    for (int i = 0; i < numTests; i++)
    {
        cout << "|" << "\t" << LabTests[i].TestID << "\t|"
             << "\t" << LabTests[i].ResultValue << "\t|\n";
    }
    cout << "---------------------------------\n";
}

/**
 * @brief Finds the index of a LabTest by ID.
 * @param id Test ID to search for.
 * @return Index of the LabTest if found, -1 otherwise.
 */
int  LabTestManager::findIndexById(string TestID)
{
    for (int i = 0; i < numTests; i++)
    {
        if (LabTests[i].TestID == TestID)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Edits an existing LabTest by ID.
 */
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

    cout << "Enter New  ResultValue: ";
    cin >> LabTests[index].ResultValue;

    cout << "LabTest updated successfully.\n";
}

/**
 * @brief Deletes an existing Test by ID.
 */
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

    // Shift data to fill the gap
    for (int i = index; i < numTests - 1; i++)
    {
        LabTests[i] = LabTests[i + 1];
    }
    numTests--;

    cout << "Test deleted successfully.\n";
}

LabTestManager::LabTestManager()
{
    numTests = 0;
}
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
