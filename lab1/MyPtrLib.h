#include <iostream>

template <typename T>
class SmrtPtr {
public:
    SmrtPtr(T* ptr) : data(ptr), refCount(new int(1)) {}
    SmrtPtr(const SmrtPtr<T>& other) : data(other.data), refCount(other.refCount) 
    {
        (*refCount)++;
    }
    ~SmrtPtr() 
    {
        if (--(*refCount) == 0) // if (*refCount == 0)
        {
            delete data;
            delete refCount;
        }
    }

    SmrtPtr<T>& operator=(const SmrtPtr<T>& other) 
    {
        if (this != &other) 
        {
            if (--(*refCount) == 0) // if (*refCount == 0)
            {
                delete data;
                delete refCount;
            }
            data = other.data;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    T& operator*() const 
    {
        return *data;
    }

    T* operator->() const 
    {
        return data;
    }

private:
    T* data;         // Указатель на данные
    int* refCount;  // Счетчик ссылок
};

template <typename T>
class UnqPtr;

template <typename T>
class ShrdPtr {
public:
    ShrdPtr(UnqPtr<T>& ptr) : data(ptr.data), refCount(ptr.refCount) 
    {
        (*refCount)++;
    }

    ShrdPtr(const ShrdPtr<T>& other) : data(other.data), refCount(other.refCount) 
    {
        (*refCount)++;
    }

    ~ShrdPtr() 
    {
        if (--(*refCount) == 0) 
        {
            delete data;
            delete refCount;
        }
    }

    T& operator*() const 
    {
        return *data;
    }

    T* operator->() const 
    {
        return data;
    }

private:
    T* data;         // Указатель на данные
    int* refCount;  // Счетчик ссылок

    friend class UnqPtr<T>;
};

template <typename T>
class UnqPtr {
public:
    UnqPtr(T* ptr) : data(ptr), refCount(new int(1)) {}

    UnqPtr(ShrdPtr<T>&& other) : data(other.data), refCount(other.refCount) 
    {
        other.data = nullptr;
        other.refCount = nullptr;
    }

    ~UnqPtr() 
    {
        if (--(*refCount) == 0) 
        {
            delete data;
            delete refCount;
        }
    }

private:
    T* data;         // Указатель на данные
    int* refCount;  // Счетчик ссылок

    friend class ShrdPtr<T>;
};