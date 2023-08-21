#include <iostream>

template <typename T>
class SmrtPtr {
public:
    SmrtPtr(T* ptr) : data(ptr), ref_count(new int(1)) {}
    SmrtPtr(const SmrtPtr<T>& other) : data(other.data), ref_count(other.ref_count) 
    {
        (*ref_count)++;
    }
    ~SmrtPtr() 
    {
        if (--(*ref_count) == 0) // if (*ref_count == 0)
        {
            delete data;
            delete ref_count;
        }
    }

    SmrtPtr<T>& operator=(const SmrtPtr<T>& other) 
    {
        if (this != &other) 
        {
            if (--(*ref_count) == 0) // if (*ref_count == 0)
            {
                delete data;
                delete ref_count;
            }
            data = other.data;
            ref_count = other.ref_count;
            (*ref_count)++;
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
    int* ref_count;  // Счетчик ссылок
};
