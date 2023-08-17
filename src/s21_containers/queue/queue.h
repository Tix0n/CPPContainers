#ifndef SRC_S21_CONTAINERS_QUEUE_QUEUE_H_
#define SRC_S21_CONTAINERS_QUEUE_QUEUE_H_

#include <cstddef>
#include <initializer_list>

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Queue() noexcept;
  Queue(std::initializer_list<value_type> const& items) noexcept;
  Queue(const Queue& q) noexcept;
  Queue(Queue&& q) noexcept;
  ~Queue() noexcept;

  void operator=(Queue&& q) noexcept;

  const_reference Front() const;
  const_reference Back() const;
  bool Empty() const noexcept;
  size_type Size() const noexcept;

  void Push(const_reference value) noexcept;
  void Pop() noexcept;
  void Swap(Queue& other) noexcept;

 private:
  struct node {
    value_type value_;
    node* next_;
  };

  node* root_;
  node* end_;
  size_type size_queue_;
};
}  // namespace s21
#include "queue.tpp"
#endif  // SRC_S21_CONTAINERS_QUEUE_QUEUE_H_
