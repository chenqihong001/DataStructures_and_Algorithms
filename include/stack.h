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

template <class T, int SIZE = 10>
class Stack_Shared // 共享栈
{
public:
    Stack_Shared() : top0(-1), top1(SIZE) {} // 默认构造函数初始化 top
    bool IsEmpty();
    bool Push(const T &temp, int stackNumber);
    bool Pop(int stackNumber);
    T GetTop(int stackNumber);

private:
    T stackArray[SIZE];
    int top0;
    int top1;
};

template <class T>
struct ListNode
{
    T elem;
    ListNode *next;
    ListNode(const T &value) : elem(value), next(nullptr) {}
};

template <class T>
using listNodePtr = ListNode<T> *;

template <class T>
class Stack_Linked
{
private:
    listNodePtr<T> stackTop{nullptr}; // 栈顶指针
    int count{};                      // 数据量
public:
    bool Push(const T &val);
    bool Pop();
    T GetTop();
};
template <class T>
bool Stack_Linked<T>::Push(const T &val)
{
    ListNode<T> *listNode = new ListNode<T>(val);
    listNode->next = this->stackTop;
    this->stackTop = listNode;
    this->count++;
    return true;
}
template <class T>
bool Stack_Linked<T>::Pop()
{
    if (this->stackTop != nullptr)
    {
        listNodePtr<T> tempItem = this->stackTop;
        this->stackTop = this->stackTop->next;
        delete tempItem;
        tempItem = nullptr;
        this->count--;
        return true;
    }
    return false;
}
template <class T>
T Stack_Linked<T>::GetTop()
{
    if (this->stackTop == nullptr)
        throw std::out_of_range("LinkedStack is empty");
    return this->stackTop->elem;
}

// 顺序栈
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

// 共享栈
template <class T, int SIZE> // SIZE非类型模板参数
bool Stack_Shared<T, SIZE>::IsEmpty()
{
    return this->top0 == -1 && this->top1 == SIZE;
}

template <class T, int SIZE>
bool Stack_Shared<T, SIZE>::Push(const T &temp, int stackNumber)
{
    if (this->top0 + 1 == this->top1)
        return false;
    if (stackNumber == 0)
        this->stackArray[++top0] = temp;
    else
        this->stackArray[--top1] = temp;
    return true;
}
template <class T, int SIZE>
bool Stack_Shared<T, SIZE>::Pop(int stackNumber)
{
    if (stackNumber == 0)
    {
        if (top0 == -1)
            return false;
        this->top0--;
    }
    else
    {
        if (top1 == SIZE)
            return false;
        this->top1++;
    }
    return true;
}

template <class T, int SIZE>
T Stack_Shared<T, SIZE>::GetTop(int stackNumber)
{
    if (stackNumber == 0)
    {
        if (this->top0 == -1)
            throw std::out_of_range("Stack0 is empty");
        return this->stackArray[top0];
    }
    else
    {
        if (this->top1 == SIZE)
            throw std::out_of_range("Stack1 is empty");
        return this->stackArray[top1];
    }
}