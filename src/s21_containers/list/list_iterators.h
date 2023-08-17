#ifndef SRC_S21_CONTAINERS_LIST_LIST_ITERATORS_H_
#define SRC_S21_CONTAINERS_LIST_LIST_ITERATORS_H_

#include "list_node.h"

namespace s21 {
template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using node_type = node<T>;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;

  ListIterator() : node_(nullptr){};
  ListIterator(node_type *node) : node_(node) {}
  reference operator*() { return node_->value_; }

  bool operator!=(const iterator &iterator) const {
    return node_ != iterator.node_;
  }
  bool operator==(const iterator &iterator) const {
    return node_ == iterator.node_;
  }
  //++i
  iterator &operator++() {
    if (node_ != nullptr) {
      node_ = node_->next_;
    }
    return *this;
  }
  // i++
  iterator &operator++(int) {
    iterator buffer(node_);
    node_ = node_->next_;
    return buffer;
  }

  iterator operator+(int n) {
    while (n-- && node_ != nullptr) {
      node_ = node_->next_;
    }
    return *this;
  }

  iterator &operator+=(int n) {
    while (n-- && node_ != nullptr) {
      node_ = node_->next_;
    }
    return *this;
  }

  iterator &operator--() {
    if (node_ != nullptr && node_->prev_ != nullptr) {
      node_ = node_->prev_;
    }
    return *this;
  }

  iterator operator-(int n) {
    while (n-- && node_ != nullptr) {
      node_ = node_->prev_;
    }
    return *this;
  }

  iterator operator--(int) {
    iterator buffer(node_);
    node_ = node_->prev_;
    return buffer;
  }

  node_type *GetNodePointer() const { return node_; }

 private:
  node_type *node_;
};

template <typename T>
class ListConstIterator {
 public:
  using value_type = T;
  using node_type = node<T>;
  using const_reference = const T &;
  using const_iterator = ListConstIterator<T>;
  using iterator = ListIterator<T>;

 public:
  ListConstIterator() : node_(nullptr){};
  ListConstIterator(const node_type *node) : node_(node) {}
  ListConstIterator(const iterator &iter) : node_(iter.GetNodePointer()) {}

  const_reference operator*() { return node_->value_; }

  bool operator!=(const const_iterator &iter) { return node_ != iter.node_; }

  bool operator==(const const_iterator &iter) { return node_ == iter.node_; }

  const_iterator &operator++() {
    node_ = node_->next_;
    return *this;
  }

  const_iterator &operator--() {
    node_ = node_->prev_;
    return *this;
  }

  operator iterator() const { return iterator(const_cast<node_type *>(node_)); }

 private:
  const node_type *node_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_LIST_LIST_ITERATORS_H_
