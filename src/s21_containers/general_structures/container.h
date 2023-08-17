#ifndef SRC_S21_CONTAINERS_GENERAL_STRUCTURES_CONTAINER_H_
#define SRC_S21_CONTAINERS_GENERAL_STRUCTURES_CONTAINER_H_

#include <cstddef>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "const_iter.h"
#include "iter.h"
#include "node.h"

namespace s21 {

template <typename Key, typename T>
class Container {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = Iter<Key, T>;
  using const_iterator = ConstIter<Key, T>;

  Container() noexcept;
  Container(std::initializer_list<value_type> const& items) noexcept;
  Container(const Container& other) noexcept;
  Container(Container&& other) noexcept;
  ~Container();

  void operator=(Container&& other) noexcept;
  Container<Key, T>& operator=(const Container& other) noexcept;

  iterator Begin() const noexcept;
  iterator End() const noexcept;

  const_iterator CBegin() const noexcept;
  const_iterator CEnd() const noexcept;

  template <typename V>
  std::pair<iterator, bool> Insert(const V& value);

  bool Empty() const noexcept;
  size_type Size() const noexcept;
  size_type MaxSize() const noexcept;

  void Clear() noexcept;
  void Swap(Container& other) noexcept;

  void Merge(Container& other) noexcept;

  void Erase(iterator pos);

  iterator Find(const Key& key) noexcept;
  bool Contains(const Key& key) noexcept;

  void DeleteTree(Node<Key, T>* node) noexcept;
  void Rebalancing(Node<Key, T>* node) noexcept;
  void RotateLeft(Node<Key, T>* x) noexcept;
  void RotateRight(Node<Key, T>* x) noexcept;
  void EraseFixup(Node<Key, T>* x) noexcept;
  Node<Key, T>* GetRoot() const;

  void PrintTree() const;
  void PrintTree(Node<Key, T>* node, int indent, int level) const;

 protected:
  Node<Key, T>* root_;
  Node<Key, T>* dummy_;
  size_type size_cont_;
};

}  // namespace s21

#include "container.tpp"
#endif  // S21_CONTAINERS_GENERAL_STRUCTURES_CONTAINER_H_
