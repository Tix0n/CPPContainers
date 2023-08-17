#ifndef SRC_S21_CONTAINERS_GENERAL_STRUCTURES_ITER_H_
#define SRC_S21_CONTAINERS_GENERAL_STRUCTURES_ITER_H_

#include "node.h"

namespace s21 {

template <typename Key, typename T>
class Iter {
 public:
  using value_type = T;
  using key_type = Key;

  Iter() noexcept;
  Iter(Node<Key, T>* other) noexcept;
  Iter(const Iter& other) noexcept;
  ~Iter() {}

  bool operator==(const Iter& other) const noexcept;
  Iter operator=(const Iter& other) noexcept;
  void operator++() noexcept;
  void operator--() noexcept;
  bool operator!=(const Iter& other) const noexcept;

  const Key& GetKey() const { return current_->key_; }

  const T& GetVal() const { return current_->val_; }

  Node<Key, T>* getCurrent() const { return current_; }

 protected:
  Node<Key, T>* current_;
};

}  // namespace s21
#include "iter.tpp"
#endif  // SRC_S21_CONTAINERS_GENERAL_STRUCTURES_ITER_H_
