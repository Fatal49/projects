#ifndef __CVECTOR_HPP__
#define __CVECTOR_HPP__

#include <cstdint>

namespace vector {

    // Create unsigned int typedef
    typedef unsigned int u_int;

    // Forward Declaration for vector class
    template <typename T>
    class CVector;

    // CVectorIter Class
    template <typename Object>
    class CVectorIter {

        // Make the vector class a friend Class
        friend class CVector<Object>;

    public:

        // Copy Constructor
        CVectorIter(const CVectorIter& rhs)
            : _data(rhs._data), cur_pos(rhs.cur_pos), vec_size(rhs.vec_size) {}

        // Operator Overloads
        CVectorIter& operator ++ ();            // Pre-increment
        CVectorIter  operator ++ (int);         // Post-increment
        CVectorIter& operator +  (int x);
        CVectorIter& operator +  (u_int x);
        CVectorIter& operator -- ();            // Pre-decrement
        CVectorIter  operator -- (int);         // Post-decrement
        CVectorIter& operator -  (int x);
        CVectorIter& operator -  (u_int x);
        Object       operator *  () const;
        bool         operator != (const CVectorIter& rhs);
        bool         operator == (const CVectorIter& rhs);
        const CVectorIter& operator = (const CVectorIter& rhs);

    private:

        // Constructor
        CVectorIter(Object*& data, u_int vector_size, u_int position = 0);

        /* Member Variables */
        const Object* const* _data;     // Double pointer to our data
        u_int cur_pos;                  // Current position in the vector
        u_int vec_size;                 // Size of the vector
    };

    // Constructor
    template <typename T>
    CVectorIter<T>::CVectorIter(T*& data, u_int vector_size, u_int position)
        : cur_pos(position), vec_size(vector_size) {
        _data = &data;
    }

    // Operator Overloads
    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator ++ () {
        // Check if the current position is equal to
        // or less than the vector size
        if (cur_pos <= vec_size)
            cur_pos++;

        // Return myself
        return *this;
    }

    template <typename T>
    CVectorIter<T> CVectorIter<T>::operator ++ (int) {
        // Make a copy of myself
        CVectorIter<T>* temp = this;

        // Increment my position
        operator++();

        // Return my old self
        return *temp;
    }

    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator + (int x) {
        // Modify the current position
        cur_pos += x;

        // Return myself
        return *this;
    }

    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator + (u_int x) {
        // Modify the current position
        cur_pos += x;

        // Return myself
        return *this;
    }

    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator -- () {
        // Check if the current position is equal to
        // or greater than 0
        if (cur_pos >= 0)
            cur_pos--;

        // Return myself
        return *this;
    }

    template <typename T>
    CVectorIter<T> CVectorIter<T>::operator -- (int) {
        // Make a copy of myself
        CVectorIter<T>* temp = this;

        // Increment my position
        operator--();

        // Return my old self
        return *temp;
    }

    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator - (int x) {
        // Modify the current position
        if (cur_pos != 0)
            cur_pos -= 1;

        // Return myself
        return *this;
    }

    template <typename T>
    CVectorIter<T>& CVectorIter<T>::operator - (u_int x) {
        // Modify the current position
        if (cur_pos != 0)
            cur_pos -= 1;

        // Return myself
        return *this;
    }

    template <typename T>
    T CVectorIter<T>::operator * () const {
        return (*_data)[cur_pos];
    }

    template <typename T>
    bool CVectorIter<T>::operator != (const CVectorIter<T>& rhs) {
        // Check if the size of the vectors are the same
        if (vec_size == rhs.vec_size) {
            // Check if the addresses are not the same
            if (&(*_data)[cur_pos] != &(*rhs._data)[rhs.cur_pos])
                return true;
        }

        return false;
    }

    template <typename T>
    bool CVectorIter<T>::operator == (const CVectorIter<T>& rhs) {
        // Check if the size of the vectors are the same
        if (vec_size == rhs.vec_size) {
            // Check if the addresses are the same
            if (&(*_data)[cur_pos] == &(*rhs._data)[rhs.cur_pos])
                return true;
        }

        return false;
    }

    template <typename T>
    const CVectorIter<T>& CVectorIter<T>::operator = (const CVectorIter<T>& rhs) {
        // Check for self assignment
        if (this != &rhs) {
            // Set the old data to the new data
            _data = rhs._data;
            cur_pos = rhs.cur_pos;
            vec_size = rhs.vec_size;
        }

        // Return myself
        return *this;
    }

    // CVector class
    template <typename Object>
    class CVector {
    public:

        // Iterator typedef
        typedef CVectorIter<Object> iterator;

        /* Iterator Methods (Public) */
        CVectorIter<Object> begin()  { return CVectorIter<Object>(_data, _size, 0); }
        CVectorIter<Object> end() { return CVectorIter<Object>(_data, _size, _size); }

        // Constructors
        // CVector(Object (&&arr)[]);
        explicit CVector(u_int size = 5);
        CVector(u_int size, Object&& data);
        CVector(const CVector& rhs);

        // Destructor
        ~CVector();

        // Operator Overloads
        const CVector& operator = (const CVector& rhs);
        Object&  operator [] (u_int index);
        Object   operator [] (u_int index) const;

        // Methdos

        /* Getters */
        u_int size() const;
        u_int capacity() const;
        bool  isEmpty() const;


        /* Vector Modifiers (Public) */
        void push_back(const Object& x);
        void push_back(Object&& x);
        void clear();

    private:

        /* Vector Modifiers (Private) */
        void extend();

        u_int _index;       // The current index into the array
        u_int _size;        // The current number of elements in the vector
        u_int _capacity;    // The current capacity of the vector
        Object* _data;      // The array to wrap
    };

    // Constructors
    template <typename T>
    CVector<T>::CVector(u_int size)
        : _index(0), _size(0), _capacity(size), _data( new T[_capacity] ) {}

    template <typename T>
    CVector<T>::CVector(u_int size, T&& data)
        : _index(0), _size(size), _capacity(size * 2), _data( new T[_capacity] ) {
        // Fill the array with the given data
        for (int i = 0; i < _size; i++)
            _data[i] = data;
    }

    // Copy Constructor
    template <typename T>
    CVector<T>::CVector(const CVector<T>& rhs)
    : _index(rhs._index), _size(rhs._size), _capacity(rhs._capacity) {
        // Create a new array on the heap
        T* new_data = new T[_capacity];

        // Copy over all the data from the old
        // array to the new array
        for (u_int i = 0; i < _size; i++) {
            new_data[i] = rhs._data[i];
        }

        // Set the new array to the old array
        _data = new_data;
    }

    // Destructor
    template <typename T>
    CVector<T>::~CVector() { delete [] _data; }

    // Operator Overloads
    template <typename T>
    const CVector<T>& CVector<T>::operator = (const CVector<T>& rhs) {
        // Check for self assignment
        if (this != &rhs) {
            // Destructor
            delete [] _data;

            // Copy Constructor
            _index = rhs._index;
            _size = rhs._size;
            _capacity = rhs._capacity;

            T* new_data = new T[_capacity];

            for (u_int i = 0; i < _size; i++)
                new_data[i] = rhs._data[i];

            _data = new_data;
        }

        // Return our actual self
        return *this;
    }

    template <typename T>
    T& CVector<T>::operator [] (u_int index) { return _data[index]; }

    template <typename T>
    T CVector<T>::operator [] (u_int index) const { return _data[index]; }

    // Getters 
    template <typename T>
    u_int CVector<T>::size() const { return _size; }

    template <typename T>
    u_int CVector<T>::capacity() const { return _capacity; }

    template <typename T>
    bool CVector<T>::isEmpty() const { if (_size == 0) return true; else return false; }

    /* Vector Modifiers (Public) */
    template <typename T>
    void CVector<T>::push_back(const T& data) {
        // Check if the size and capacity are equal
        if (_size == _capacity)
            extend();

        // Add the new data to the array
        _data[_index++] = data;
        
        // Check if the index is equal to the size
        if (_index == _size)
            _size = _index;
    }

    template <typename T>
    void CVector<T>::push_back(T&& data) {
        // Check if the size and capacity are equal
        if (_size == _capacity)
            extend();

        // Add the new data to the array
        _data[_index++] = data;

        // Check if the index is equal to the size
        if (_index >= _size)
            _size = _index;
    }

    template <typename T>
    void CVector<T>::clear() {
        // Delete the old array
        delete [] _data;

        // Set the index to 0
        _index = 0;

        // Set the size to 0
        _size = 0;

        // Set the capacity to 5
        _capacity = 5;

        // Create a new array on the heap
        T* new_data = new T[_capacity];

        // Set the old array to the new array
        _data = new_data;
    }

    /* Vector Modifiers (Private) */
    template <typename T>
    void CVector<T>::extend() {
        // Increase the capacity
        _capacity *= 2;

        // Create a new array on the heap
        T* new_data = new T[_capacity];

        // Copy over all the data from the old
        // to the new array
        for (u_int i = 0; i < _size; i++)
            new_data[i] = _data[i];

        // Delete the old array
        delete [] _data;

        // Set the old array to the new array
        _data = new_data;
    }
}

#endif /* __CVECTOR_HPP__ defined */
