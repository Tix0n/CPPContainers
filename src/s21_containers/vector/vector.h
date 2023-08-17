#ifndef SRC_S21_CONTAINERS_VECTOR_VECTOR_H_
#define SRC_S21_CONTAINERS_VECTOR_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "vector_iterators.h"

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v);
  ~Vector();

  Vector& operator=(Vector&& v);
  reference At(size_type pos);
  reference operator[](size_type pos);
  const_reference Front();
  const_reference Back();
  T* Data();

  iterator Begin();
  iterator End();

  bool Empty();
  size_type Size();
  size_type MaxSize();
  void Reserve(size_type size);
  size_type Capacity();
  void ShrinkToFit();
  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void Swap(Vector& other);

 private:
  T* arr_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21
#include "vector.tpp"
#endif  // SRC_S21_CONTAINERS_VECTOR_VECTOR_H_
