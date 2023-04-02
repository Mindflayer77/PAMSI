#pragma once
#include "QueueEmpty.h"
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
    void enQueue(SNode<T> *newNode);
    void deQueue();
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
    const T &min() const;
    void display() const;
    std::ostream &display(std::ostream &ostrm) const;
    bool remove(const T &elem);
};

// tutaj chodzi o to , że musimy mieć wskaźnik na element poprzedni
//  do tego, który chcemy usunąć, więc musimy sprawdzać z wyprzedzeniem,
//  czy następny element będzie tym, którego szukamy
//  jest to najprostszy sposób implementacji usuwania elementu wewnątrz listy
//  funkcja zwraca true jeśli znaleźliśmy szukany element
//  oraz zwraca false, jeśli w całej liście nie ma danego elementu
template <typename T> bool SLPQueue<T>::remove(const T &elemRmv)
{
    SNode<T> *iter = front; // ustawiamy iterator na poczatek listy
    SNode<T> *tmp = nullptr;
    if (isEmpty()) // jesli jest pusta lista to zwracamy false;
        return false;
    if (iter->elem == elemRmv)
    {              // jezeli element jest na poczatku listy
        deQueue(); // usuwamy pierwszy element listy;
        return true;
    }
    while (iter != back)
    { // dopoki nie dojdzie do konca listy
        if (iter->next->elem == elemRmv)
        {                                  // sprawdzamy element w następnym Node
            tmp = iter->next;              // ustawiamy tymczasowy wskaznik na element który chcemy
                                           // usunąć
            iter->next = iter->next->next; // przesuwmy wskaznik na kolejny element
            delete tmp;
            return true;
        }
        else
        {
            iter = iter->next; // jak nie znaleźliśmy to przechodzimy dalej
        }
    }
    return false;
}

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

template <typename T> std::ostream &SLPQueue<T>::display(std::ostream &ostrm) const
{
    SNode<T> *tmp = front;
    while (tmp != nullptr)
    {
        try
        {
            ostrm << tmp->elem << " ";
            tmp = tmp->next;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return ostrm;
        }
    }
    return ostrm;
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

template <typename T> const T &SLPQueue<T>::min() const
{
    SNode<T> *iter = front;
    static T min;
    while (iter != back)
    {
        if (iter->priority > iter->next->priority)
        {
            min = iter->next->priority;
        }
        iter = iter->next;
    }
    return min;
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

template <typename T> void SLPQueue<T>::enQueue(SNode<T> *newNode)
{
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
        throw QueueEmpty("Queue is empty\n");
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