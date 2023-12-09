#pragma once
#include <iostream>
#include <stack>
template <class T, int SIZE = 10> /*非类型模板参数的使用场景：1.数组或缓冲区大小的确认 2.常量表达式的计算*/
class Stack_Sequential            // 顺序栈
{
public:
    Stack_Sequential() : top(-1) {} // 默认构造函数初始化 top
    bool IsEmpty();
    bool Push(const T &temp);
    bool Pop();
    T GetTop();

private:
    T stackArray[SIZE];
    int top; // 栈顶指针
};

template <class T, int SIZE> // SIZE非类型模板参数
bool Stack_Sequential<T, SIZE>::IsEmpty()
{
    return this->top == -1;
}

template <class T, int SIZE>
bool Stack_Sequential<T, SIZE>::Push(const T &temp)
{
    if (this->top == SIZE - 1)
        return false;
    this->stackArray[++top] = temp;
    return true; //++top能保证先加，在赋值
}

template <class T, int SIZE>
bool Stack_Sequential<T, SIZE>::Pop()
{
    if (this->IsEmpty())
        return false;
    this->top--;
    return true;
}

template <class T, int SIZE>
T Stack_Sequential<T, SIZE>::GetTop()
{
    if (this->IsEmpty())
        throw std::out_of_range("Stack is empty"); // 抛出异常，表示栈为空
    return this->stackArray[top];
}