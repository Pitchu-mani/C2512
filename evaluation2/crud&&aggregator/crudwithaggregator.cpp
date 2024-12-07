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

public:
    bool GreaterThan(const LabTest &other);
    bool LessThan(const LabTest &other);
    // getters-setters
    string GetTestID();
    double GetResultValue();
};

// *****LabTestManager.h*****
class LabTestManager
{
    friend class LabTestAggregator;
    friend int main();
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


//*****LabTestAggregator.h*****
class LabTestAggregator
{
public:
    int findMin(LabTestManager &manager);
    int findMax(LabTestManager &manager);
    int findSecondMin(LabTestManager &manager);
    int findSecondMax(LabTestManager &manager);
};

// *****Menu.h*****
void printMenu();

// *****Main.cpp*****

int main()
{
    LabTestManager manager;
    LabTestAggregator aggregator;

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
            std::cout << "TestID with Min ResultValue: "
                      << manager.LabTests[aggregator.findMin(manager)].GetTestID()
                      << " with ResultValue "
                      << manager.LabTests[aggregator.findMin(manager)].GetResultValue()
                      << std::endl;
            break;
        case 6:
            std::cout << "TestID with Max ResultValue: "
                      << manager.LabTests[aggregator.findMax(manager)].GetTestID()
                      << " with ResultValue "
                      << manager.LabTests[aggregator.findMax(manager)].GetResultValue()
                      << std::endl;
            break;
        case 7:
           std::cout << "TestID with 2nd Min ResultValue: "
                      << manager.LabTests[aggregator.findSecondMin(manager)].GetTestID()
                      << " with ResultValue "
                      << manager.LabTests[aggregator.findSecondMin(manager)].GetResultValue()
                      << std::endl;
            break;
        case 8:
           std::cout << "TestID with 2nd Max ResultValue: "
                      << manager.LabTests[aggregator.findSecondMax(manager)].GetTestID()
                      << " with ResultValue "
                      << manager.LabTests[aggregator.findSecondMax(manager)].GetResultValue()
                      << std::endl;
            break;
        case 9:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);

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
    cout << "5. Find Min Resultvalue\n";
    cout << "6. Find Max ResultValue\n";
    cout << "7. Find Second Min ResultValue\n";
    cout << "8. Find Second Max ResultValue\n";
    cout << "9. Exit\n";
}


//*****LabTest.cpp*****
bool LabTest::GreaterThan(const LabTest &other)
{
    return (ResultValue > other.ResultValue);
}

bool LabTest::LessThan(const LabTest &other)
{
    return (ResultValue < other.ResultValue);
}

// getters-setters
string LabTest::GetTestID()
{
    return TestID;
}
double LabTest::GetResultValue()
{
    return ResultValue;
}
//*****LabTestAggregator.cpp*****
// Function to find the index of the Test with the minimum ResultValue
int LabTestAggregator::findMin(LabTestManager &manager)
{
    LabTest *arr = manager.LabTests;
    int n = manager.numTests;
    //
    int minIndex = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i].LessThan(arr[minIndex]))
        {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to find the index of the LabTest with the maximum ResultValue
int LabTestAggregator::findMax(LabTestManager &manager)
{
    LabTest *arr = manager.LabTests;
    int &n = manager.numTests;
    //
    int maxIndex = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i].GreaterThan(arr[maxIndex]))
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to find the index of the LabTest with the second minimum result value
int LabTestAggregator::findSecondMin(LabTestManager &manager)
{
    LabTest *arr = manager.LabTests;
    int &n = manager.numTests;
    //
    int minIndex = findMin(manager);
    int secondMinIndex = (minIndex == 0) ? 1 : 0;

    for (int i = 0; i < n; ++i)
    {
        if (i != minIndex)
        {
            if (arr[i].LessThan(arr[secondMinIndex]))
            {
                secondMinIndex = i;
            }
        }
    }
    return secondMinIndex;
}

// Function to find the index of the LabTest with the second maximum ResultValue
int LabTestAggregator::findSecondMax(LabTestManager &manager)
{
    LabTest *arr = manager.LabTests;
    int &n = manager.numTests;
    //
    int maxIndex = findMax(manager);
    int secondMaxIndex = (maxIndex == 0) ? 1 : 0;

    for (int i = 0; i < n; ++i)
    {
        if (i != maxIndex)
        {
            if (arr[i].GreaterThan(arr[secondMaxIndex]))
            {
                secondMaxIndex = i;
            }
        }
    }
    return secondMaxIndex;
}
