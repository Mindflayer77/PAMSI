#pragma once

template <typename T> class SNode;
template <typename T> class SLPQueue;

template <typename T> class SNode {
private:
  SNode<T> *next;
  T elem;
  int priority;

public:
  SNode() : next(nullptr), priority(0) {}
  ~SNode() {}
  friend class SLPQueue<T>;
};