#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class Employee {
private:
    int* id;
    int* age;     
    char* name;

public:
    // Constructor
    Employee(int id, int age, const char* name) {
        this->id = new int(id);                  
        this->age = new int(age);   
        this->name = new char[strlen(name) + 1]; 
        strcpy(this->name, name);
    }

    // Destructor
    ~Employee() {
        delete id;   // Free memory for id
        delete age;  // Free memory for age
        delete[] name; // Free memory for name
    }

    // Move Constructor
    Employee(Employee&& other) noexcept 
        : id(other.id), age(other.age), name(other.name) {
        other.id = nullptr;
        other.age = nullptr;
        other.name = nullptr; // Nullify the source to prevent double deletion
    }

    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            // Free existing memory
            delete id;
            delete age;
            delete[] name;

            // Steal resources from `other`
            id = other.id;
            age = other.age;
            name = other.name;

            // Nullify the source
            other.id = nullptr;
            other.age = nullptr;
            other.name = nullptr;
        }
        return *this;
    }

    // Swap Function using Move Constructor
    void swap(Employee& other) {
        Employee temp(std::move(other)); // Move `other` into `temp`
        other = std::move(*this);       // Move `this` into `other`
        *this = std::move(temp);        // Move `temp` back into `this`
    }

    friend ostream& operator<<(ostream& os, const Employee& emp);
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << *emp.id << " " << *emp.age << " " << emp.name;
    return os;
}

int main() {
    Employee e1(101, 22, "Athira"), e2(102, 23, "Bhagya");

    cout << e1 << endl; // Output: 101 22 Athira
    cout << e2 << endl; // Output: 102 23 Bhagya

    e1.swap(e2);

    cout << e1 << endl; // Output: 102 23 Bhagya
    cout << e2 << endl; // Output: 101 22 Athira

    return 0;
}
