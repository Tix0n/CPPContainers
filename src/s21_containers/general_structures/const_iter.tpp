#include "const_iter.h"
#include "node.h"

namespace s21 {

template <typename Key, typename T>
ConstIter<Key, T>::ConstIter() noexcept : Iter<Key, T>() {}

template <typename Key, typename T>
ConstIter<Key, T>::ConstIter(const Node<Key, T>* other) noexcept
    : Iter<Key, T>(const_cast<Node<Key, T>*>(other)) {}

template <typename Key, typename T>
ConstIter<Key, T>::ConstIter(const ConstIter& other) noexcept
    : Iter<Key, T>(other) {}

template <typename Key, typename T>
ConstIter<Key, T>::ConstIter(ConstIter&& other) noexcept
    : Iter<Key, T>(std::move(other.current_)) {
  other.current_ = nullptr;
}

template <typename Key, typename T>
ConstIter<Key, T>& ConstIter<Key, T>::operator=(
    const ConstIter& other) noexcept {
  if (this != &other) {
    this->current_ = other.current_;
  }
  return *this;
}

template <typename Key, typename T>
ConstIter<Key, T>& ConstIter<Key, T>::operator=(ConstIter&& other) noexcept {
  if (this != &other) {
    this->current_ = std::move(other.current_);
    other.current_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
ConstIter<Key, T>& ConstIter<Key, T>::operator++() noexcept {
  Iter<Key, T>::operator++();
  return *this;
}

template <typename Key, typename T>
ConstIter<Key, T>& ConstIter<Key, T>::operator--() noexcept {
  Iter<Key, T>::operator--();
  return *this;
}

template <typename Key, typename T>
ConstIter<Key, T>& ConstIter<Key, T>::operator=(
    const Node<Key, T>* other) noexcept {
  this->current_ = const_cast<Node<Key, T>*>(other);
  return *this;
}

template <typename Key, typename T>
bool ConstIter<Key, T>::operator!=(const ConstIter& other) const noexcept {
  return this->current_ != other.current_;
}

}  // namespace s21
