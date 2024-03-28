#include <iostream>
#include "stack.h"
#include "stack.cpp"
int main() {
   
    s21::stack<int> myStack;
    
   
    myStack.push(5);
    std::cout << "push " << myStack.top() <<std::endl;
   
    std::cout << "Top element of stack: " << myStack.top() << std::endl;
    
    std::cout<< "Pop" << std::endl;
    myStack.pop();
    
    // Выводим размер стека
    std::cout << "Size of stack after popping: " << myStack.size() << std::endl;
    
    return 0;
}