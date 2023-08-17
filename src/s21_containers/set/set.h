#ifndef SRC_S21_CONTAINERS_SET_SET_H_
#define SRC_S21_CONTAINERS_SET_SET_H_

#include "../general_structures/container.h"

namespace s21 {
template <typename Key>
class Set : public Container<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Container<Key, Key>::iterator;
  using const_iterator = typename Container<Key, Key>::const_iterator;
  using size_type = std::size_t;

  Set() noexcept = default;
  Set(std::initializer_list<value_type> const& items) noexcept : Set<Key>() {
    for (const auto& item : items) {
      Insert(item);
    }
  }
  Set(const Set& s) noexcept = default;
  Set(Set&& other) noexcept = default;
  ~Set() = default;
  Set<Key>& operator=(Set&& other) noexcept = default;
  Set<Key>& operator=(const Set& other) noexcept = default;

  using Container<Key, Key>::Insert;

  using Container<Key, Key>::Begin;
  using Container<Key, Key>::End;
  using Container<Key, Key>::CBegin;
  using Container<Key, Key>::CEnd;

  using Container<Key, Key>::Clear;
  using Container<Key, Key>::Merge;
  using Container<Key, Key>::Swap;
  using Container<Key, Key>::Erase;

  using Container<Key, Key>::Find;
  using Container<Key, Key>::Contains;

  using Container<Key, Key>::Empty;
  using Container<Key, Key>::Size;
  using Container<Key, Key>::MaxSize;

  using Container<Key, Key>::GetRoot;

 private:
  using Container<Key, Key>::root_;
  using Container<Key, Key>::dummy_;
  using Container<Key, Key>::size_cont_;
};

}  // namespace s21
#endif  // SRC_S21_CONTAINERS_SET_SET_H_
