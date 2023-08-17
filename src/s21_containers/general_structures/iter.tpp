#include "iter.h"
#include "node.h"

namespace s21 {

template <typename Key, typename T>
Iter<Key, T>::Iter() noexcept : current_(nullptr) {}

template <typename Key, typename T>
Iter<Key, T>::Iter(Node<Key, T>* other) noexcept : current_(other) {}

template <typename Key, typename T>
Iter<Key, T>::Iter(const Iter& other) noexcept : current_(other.current_) {}

template <typename Key, typename T>
bool Iter<Key, T>::operator==(const Iter& other) const noexcept {
  return current_ == other.current_;
}

template <typename Key, typename T>
Iter<Key, T> Iter<Key, T>::operator=(const Iter& other) noexcept {
  current_ = other.current_;
  return *this;
}

template <typename Key, typename T>
void Iter<Key, T>::operator++() noexcept {
  if (current_->end_) {
    return;
  }
  if (current_->right_ && current_->right_->end_ != true) {
    current_ = current_->right_;
    while (current_->left_ && current_->left_->end_ != true)
      current_ = current_->left_;
  } else {
    Node<Key, T>* save = current_;
    Node<Key, T>* p = current_->parent_;

    while (p != nullptr && current_ == p->right_) {
      current_ = p;
      p = p->parent_;
    }
    current_ = (p == nullptr) ? save->right_ : p;
  }
}

template <typename Key, typename T>
void Iter<Key, T>::operator--() noexcept {
  if (current_->end_) {
    current_ = current_->parent_;
    return;
  }
  if (current_->left_ && current_->left_->end_ != true) {
    current_ = current_->left_;
    while (current_->right_ && current_->right_->end_ != true)
      current_ = current_->right_;
  } else {
    Node<Key, T>* save = current_;
    Node<Key, T>* p = current_->parent_;

    while (current_ == p->left_ && p->left_->end_ != true) {
      current_ = p;
      if (p->parent_) {
        p = p->parent_;
      } else {
        current_ = save;
        return;
      }
    }
    current_ = p;
  }
}

template <typename Key, typename T>
bool Iter<Key, T>::operator!=(const Iter& other) const noexcept {
  return current_ != other.current_;
}

}  // namespace s21
