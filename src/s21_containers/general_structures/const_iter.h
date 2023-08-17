#ifndef SRC_S21_CONTAINERS_GENERAL_STRUCTURES_CONST_ITER_H_
#define SRC_S21_CONTAINERS_GENERAL_STRUCTURES_CONST_ITER_H_

#include "iter.h"

namespace s21 {

template <typename Key, typename T>
class ConstIter : public Iter<Key, T> {
 public:
  using typename Iter<Key, T>::value_type;
  using typename Iter<Key, T>::key_type;

  ConstIter() noexcept;
  ConstIter(const Node<Key, T>* other) noexcept;
  ConstIter(const ConstIter& other) noexcept;
  ConstIter(ConstIter&& other) noexcept;
  ~ConstIter() {}

  ConstIter& operator=(const ConstIter& other) noexcept;
  ConstIter& operator=(ConstIter&& other) noexcept;
  ConstIter& operator++() noexcept;
  ConstIter& operator--() noexcept;
  ConstIter& operator=(const Node<Key, T>* other) noexcept;
  bool operator!=(const ConstIter& other) const noexcept;

  const Key& GetKey() const { return this->current_->key_; }

  const T& GetVal() const { return this->current_->val_; }

  const Node<Key, T>* getCurrent() const { return this->current_; }

 private:
  using Iter<Key, T>::current_;
};

}  // namespace s21
#include "const_iter.tpp"
#endif  // SRC_S21_CONTAINERS_GENERAL_STRUCTURES_CONST_ITER_H_
