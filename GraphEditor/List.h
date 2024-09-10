#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

template<typename T>
class List
{
  struct ListNode {
    T data;
    ListNode* front = nullptr;
    ListNode* next = nullptr;
  };
public:

  List() :head(new ListNode), tail(new ListNode)
  {
    head->next = tail;
    tail->front = head;

    head->front = tail->next = nullptr;
    _size = 0;
  }

  ~List()
  {
    clear();
    delete head;
    delete tail;
  }

  void clear()
  {
    while(_size > 0)
    {
      pop_front();
    }
  }

  void push_front(const T& other)
  {
    ListNode* newNode = new ListNode;
    newNode->data = other;

    newNode->front = head;
    newNode->next = head->next;

    head->next->front = newNode;
    head->next = newNode;
    _size++;
  }

  void pop_front()
  {
    if(size() <= 0) return;

    ListNode* node = head->next;

    head->next = node->next;
    node->next->front = head;
    delete node;

    _size--;
  }

  int size() const
  {
    return _size;
  }

  T begin()
  {
    if(size() <= 0) abort();
    return head->next->data;
  }

  T end()
  {
    if(size() <= 0) abort();
    return tail->front->data;
  }

private:
  ListNode* head = nullptr;
  ListNode* tail = nullptr;
  int _size = 0;
};
#endif // LIST_H

