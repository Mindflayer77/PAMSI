#pragma once
#include "SNode.h"

template <typename T> class SLPQueue
{
  private:
    SNode<T> *front;
    SNode<T> *back;
    int size;

  public:
    SLPQueue() : front(nullptr), back(nullptr), size(0)
    {
    }
    ~SLPQueue()
    {
        while (!isEmpty())
            deQueue();
    }
    void enQueue(const T &newElem, const int &priority);
    void deQueue();
    SNode<T> *removeMin();
    bool isEmpty() const;
    int getSize() const
    {
        return size;
    }
    const T &getFront() const;
    const T &getBack() const;
    const SNode<T> *const getFrontNode() const
    {
        return front;
    }
    const SNode<T> *const min() const;
    void display() const;
    void sort();
};

template <typename T> void SLPQueue<T>::display() const
{
    SNode<T> *tmp = front;
    bool first = true;
    std::cout << "[ ";
    while (tmp != nullptr)
    {
        if (first == true)
        {
            std::cout << tmp->elem;
            tmp = tmp->next;
            first = false;
        }
        else
        {
            std::cout << " , " << tmp->elem;
            tmp = tmp->next;
        }
    }
    std::cout << " ]" << std::endl;
}

template <typename T> bool SLPQueue<T>::isEmpty() const
{
    return back == nullptr;
}

template <typename T> const T &SLPQueue<T>::getFront() const
{
    if (!isEmpty())
        return front->elem;
    static T t;
    return t;
}

template <typename T> const T &SLPQueue<T>::getBack() const
{
    if (!isEmpty())
        return back->elem;
    static T t;
    return t;
}

template <typename T> const SNode<T> *const SLPQueue<T>::min() const
{
    SNode<T> *iter = front, *min = front;
    while (iter != back)
    {
        if (min->priority > iter->next->priority)
        {
            min = iter->next;
        }
        iter = iter->next;
    }
    return min;
}

template <typename T> SNode<T> *SLPQueue<T>::removeMin()
{
    SNode<T> *iter = front, *prevToMin = front, *min = front;
    while (iter != back)
    {
        if (min->priority > iter->next->priority)
        {
            min = iter->next;
            prevToMin = iter;
        }
        iter = iter->next;
    }
    if (min == front)
    {
        front = front->next;
        min->next = nullptr;
        if (min == back)
        {
            back = front;
        }
    }
    else if (min == back)
    {
        prevToMin->next = nullptr;
        back = prevToMin;
    }
    else
    {
        prevToMin->next = prevToMin->next->next;
    }
    --size;
    min->next = nullptr;
    return min;
}

template <typename T> void SLPQueue<T>::sort()
{
    SLPQueue<T> copy;
    SNode<T> *tmp;
    while (!this->isEmpty())
    {
        copy.enQueue(this->getFrontNode()->getElem(), this->getFrontNode()->getPriority());
        this->deQueue();
    }
    while (!copy.isEmpty())
    {
        tmp = copy.removeMin();
        this->enQueue(tmp->getElem(), tmp->getPriority());
        delete tmp;
    }
}

template <typename T> void SLPQueue<T>::enQueue(const T &newElem, const int &priority)
{
    SNode<T> *newNode = new SNode<T>;
    newNode->elem = newElem;
    newNode->priority = priority;
    newNode->next = nullptr;
    if (isEmpty())
    {
        front = back = newNode;
    }
    else
    {
        back->next = newNode;
        back = newNode;
    }
    size++;
}


template <typename T> void SLPQueue<T>::deQueue()
{
    if (isEmpty())
    {
        std::cerr << "Error while removing element: Queue is empty!\n";
        return;
    }
    else
    {
        SNode<T> *tmp = front;
        front = front->next;
        delete tmp;
        size--;
        if (front == nullptr)
            back = nullptr;
    }
}