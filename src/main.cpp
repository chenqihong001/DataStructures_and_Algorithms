#include <iostream>
#include "stack.h"
int main()
{
    Stack_Sequential<int> stack;
    stack.Push(89);
    stack.Push(20);
    stack.Push(20);
    stack.Pop();
    std::cout << stack.GetTop();
    return 0;
}