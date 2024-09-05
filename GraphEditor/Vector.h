#ifndef VECTOR_H
#define VECTOR_H

#include<stdlib.h>

template <typename T>
class Vector {
public:
  Vector() :_array(nullptr), _capacity(0), _size(0) {}

  ~Vector()
  {
    delete[] _array;
  }

  Vector(const Vector& other) : _capacity(other._capacity), _size(other._size)
  {
    _array = new T[_capacity];
    for(size_t i = 0; i < _size; ++i)
    {
      _array[i] = other._array[i];
    }
  }

  Vector& operator=(const Vector& other)
  {
    if(this != &other)
    {
      delete[] _array;
      _capacity = other._capacity;
      _size = other._size;
      _array = new T[_capacity];

      for(size_t i = 0; i < _size; ++i)
      {
        _array[i] = other._array[i];
      }
    }
    return *this;
  }

  void push_back(const T& value)
  {
    if(_size >= _capacity)
    {
      if(_capacity == 0) _capacity = 1;
      else _capacity *= 2;
      T* tmp = new T[_capacity];
      for(size_t i = 0; i < _size; ++i)
      {
        tmp[i] = _array[i];
      }
      delete[] _array;
      _array = tmp;
    }
    _array[_size++] = value;
  }

  void pop_back()
  {
    if(_size >= 1) _size--;
  }

  void insert(int idx, const T& val)
  {
    if(idx < 0 || idx > _size)
    {
      abort();
    }

    if(_size >= _capacity)
    {
      if(_capacity == 0) _capacity = 1;
      else _capacity *= 2;
      T* tmp = new T[_capacity];
      for(size_t i = 0; i < _size; ++i)
      {
        tmp[i] = _array[i];
      }
      delete[] _array;
      _array = tmp;
    }

    for(int i = _size; i > idx; i--)
    {
      _array[i] = _array[i - 1];
    }

    _array[idx] = val;
    _size++;
  }
  //É¾³ý[first,end)
  void erase(int firstIdx, int endIdx)
  {
    if(endIdx < firstIdx ||
      firstIdx < 0 || firstIdx >= _size ||
      endIdx <= 0 || endIdx > _size)
    {
      abort();
    }

    int foreMove = endIdx - firstIdx;

    for(int i = endIdx; i < _size; i++)
    {
      _array[i - foreMove] = _array[i];
    }

    _size = _size - foreMove;

  }

  void resize(size_t new_size)
  {
    if(new_size > _capacity)
    {
      _capacity = new_size;
      T* new_array = new T[_capacity];
      for(size_t i = 0; i < _size; ++i) {
        new_array[i] = _array[i];
      }
      delete[] _array;
      _array = new_array;
    }
    for(int i = _size; i < new_size; i++)
    {
      _array[i] = T();
    }
    _size = new_size;

  }

  T& operator[](size_t index) 
  {
    if(index >= _size || index < 0)
    {
      abort();
    }
    return _array[index];
  }

  void clear()
  {
    _size = 0;
  }

  size_t size() const
  {
    return _size;
  }

  bool empty() const
  {
    return _size == 0;
  }
  T* data()
  {
    return _array;
  }

private:
  T *_array;
  size_t _capacity;
  size_t _size;
};
#endif // !VECTOR_H