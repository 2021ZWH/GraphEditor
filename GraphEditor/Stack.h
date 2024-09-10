#ifndef STACK_H
#define STACK_H

#include "List.h"

template<typename T>
class Stack
{
public:

  Stack()
  {

  }

  ~Stack()
  {
    clear();
  }

  void clear()
  {
    _data.clear();
  }

  T top()
  {
    if(size() <= 0) abort();

    return _data.begin();
  }

  void push(const T& other)
  {
    _data.push_front(other);
  }

  void pop()
  {
    _data.pop_front();
  }

  int size()
  {
    return _data.size();
  }

private:
  List<T> _data;
};
#endif

