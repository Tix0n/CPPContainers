#ifndef SRC_S21_CONTAINERS_LIST_LIST_H_
#define SRC_S21_CONTAINERS_LIST_LIST_H_

#include <cstddef>
#include <initializer_list>

#include "list_iterators.h"
#include "list_node.h"

namespace s21 {
template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = std::size_t;
  using node_type = node<T>;

  List() noexcept;
  List(size_type n);
  List(std::initializer_list<value_type> const& items) noexcept;
  List(const List& l) noexcept;
  List(List&& l) noexcept;
  ~List() noexcept;

  List& operator=(List&& l) noexcept;
  List& operator=(const List& other) noexcept;

  const_reference Front() const;
  const_reference Back() const;
  iterator Begin() const noexcept;
  iterator End() const noexcept;
  bool Empty() const noexcept;
  size_type Size() const noexcept;
  size_type MaxSize() const noexcept;

  void Clear() noexcept;
  iterator Insert(iterator pos, const_reference value) noexcept;
  void Erase(iterator pos) noexcept;
  void PushBack(const_reference value) noexcept;
  void PopBack() noexcept;
  void PushFront(const_reference value) noexcept;
  void PopFront() noexcept;
  void Swap(List& other) noexcept;
  void Merge(List& other) noexcept;
  void Splice(const_iterator pos, List& other) noexcept;

  void Reverse() noexcept;
  void Unique() noexcept;
  void Sort() noexcept;

 private:
  node_type* root_;
  node_type* end_;
  size_type size_list_;
  node_type* fake_ = nullptr;
  void FakeEndElement() noexcept;
};
}  // namespace s21
#include "list.tpp"
#endif  // SRC_S21_CONTAINERS_LIST_LIST_H_
