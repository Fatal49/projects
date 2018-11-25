#include <iostream>
#include <string>
#include "CVector.h"

using namespace std;
using namespace vector;

struct Height
{
    Height(int f, int i) : feet(f), inches(i) {}
    int feet;
    int inches;
};

struct Person 
{
    Person(const string& n, int a, int f, int i)
        : name(n), age(a), h(f, i) {}
    string name; 
    int age;
    Height h; 
};

template <typename T>
void printVector(CVector<T>& vector)
{
    // Create two iterators
    // 1) Pointing to the begining of the vector
    // 2) Pointing to the end of the vector
    CVector<int>::iterator begin = vector.begin();
    CVector<int>::iterator end = vector.end();
     
    cout << "Vector: "; 
    while (begin != end) {
        cout << *begin << " "; 
        begin++;
    }
    cout << endl;
}

void printPerson(CVector<Person*>& vector)
{
    CVector<Person*>::iterator begin = vector.begin();
    CVector<Person*>::iterator end = vector.end();
     
    cout << "Vector:\n"; 
    while (begin != end) {
        cout << "\tName: " << (*begin)->name
             << ", Age: " << (*begin)->age
             << ", Height: " << (*begin)->h.feet 
                << "' " << (*begin)->h.inches << "''" << endl;
        begin++;
    }
    cout << endl;
}

int main(int argc, char** argv) 
{
    // Create a vector of 10 ints intialized to -1
    CVector<int> vec(10, -1); 

    // Print the vector
    printVector(vec);

    // Change the first 5 ints
    for (int i = 0; i < 5; i++) {
        vec[i] = i + 1;
    }

    // Print the vector
    printVector(vec);

    // Now create a vector with 3 people and initialize them to nullptr
    CVector<Person*> people(3, nullptr);

    // Add 3 people
    people.push_back(new Person("John Doe", 21, 5, 10));
    people.push_back(new Person("Jane Doe", 52, 5, 3));
    people.push_back(new Person("Jane Doe", 46, 5, 6));


    // Print vector
    printPerson(people);

    // Delete the people in the vector (sad but it has to be done)
    for (int i = 0; i < people.size(); i++) 
        delete people[i];

    return 0;
}
