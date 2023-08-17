#ifndef SRC_S21_CONTAINERS_STACK_STACK_H_
#define SRC_S21_CONTAINERS_STACK_STACK_H_

#include <cstddef>
#include <initializer_list>

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Stack() noexcept;
  Stack(std::initializer_list<value_type> const& items) noexcept;
  Stack(const Stack& s) noexcept;
  Stack(Stack&& s) noexcept;
  ~Stack() noexcept;

  void operator=(Stack&& s) noexcept;

  const_reference Top() const;
  bool Empty() const noexcept;
  size_type Size() const noexcept;

  void Push(const_reference value) noexcept;
  void Pop() noexcept;
  void Swap(Stack& other) noexcept;

 private:
  void Clear() noexcept;

  struct node {
    value_type value_;
    node* next_;
  };

  node* root_;
  size_type size_stack_ = 0;
};
}  // namespace s21
#include "stack.tpp"
#endif  // SRC_S21_CONTAINERS_STACK_STACK_H_
