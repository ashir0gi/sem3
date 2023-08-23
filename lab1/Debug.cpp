#include <iostream>
#include "MyPtrLib.h"

int main() 
{
    // Тестирование SmrtPtr
    {
        SmrtPtr<int> smartPtr1 = new int(504);
        SmrtPtr<int> smartPtr2 = smartPtr1;
        std::cout << "SmrtPtr1: " << *smartPtr1 << ", Ref Count: " << *(smartPtr1.refCount) << std::endl; // Выведет: 504, Ref Count: 2
        std::cout << "SmrtPtr2: " << *smartPtr2 << ", Ref Count: " << *(smartPtr2.refCount) << std::endl; // Выведет: 504, Ref Count:
        
        smartPtr2 = smartPtr1;
        std::cout << "SmrtPtr2 (after assignment): " << *smartPtr2 << ", Ref Count: " << *(smartPtr2.refCount) << std::endl; // Выведет: 42, Ref Count: 2
    }

    // Тестирование UnqPtr
    {
        UnqPtr<int> uniquePtr1 = new int(504);
        std::cout << "UnqPtr1: " << *uniquePtr1 << std::endl;

        UnqPtr<int> uniquePtr2 = uniquePtr1; // Ошибка компиляции - нельзя копировать UnqPtr

        UnqPtr<int> uniquePtr3 = std::move(uniquePtr1);
        std::cout << "UnqPtr3 (after move): " << *uniquePtr3 << std::endl; // Выведет: 504
    }

    // Тестирование ShrdPtr
    {
        UnqPtr<int> unqPtr = new int(42);
        ShrdPtr<int> sharedPtr1 = unqPtr;
        ShrdPtr<int> sharedPtr2 = sharedPtr1;
        std::cout << "ShrdPtr1: " << *sharedPtr1 << ", Ref Count: " << *(sharedPtr1.refCount) << std::endl; // Выведет: 42, Ref Count: 3
        std::cout << "ShrdPtr2: " << *sharedPtr2 << ", Ref Count: " << *(sharedPtr2.refCount) << std::endl; // Выведет: 42, Ref Count: 3
    }

    return 0;
}