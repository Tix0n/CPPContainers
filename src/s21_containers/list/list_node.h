#ifndef SRC_S21_CONTAINERS_LIST_LIST_NODE_H_
#define SRC_S21_CONTAINERS_LIST_LIST_NODE_H_

namespace s21 {
template <typename T>
struct node {
  T value_;
  node* next_;
  node* prev_;
  node(const T& value, node* next = nullptr, node* prev = nullptr)
      : value_(value), next_(next), prev_(prev) {}
};
}  // namespace s21
#endif  // SRC_S21_CONTAINERS_LIST_LIST_NODE_H_
