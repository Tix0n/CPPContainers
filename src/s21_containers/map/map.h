#ifndef SRC_S21_CONTAINERS_MAP_MAP_H_
#define SRC_S21_CONTAINERS_MAP_MAP_H_

#include "../general_structures/container.h"

namespace s21 {

template <typename Key, typename T>
class Map : public Container<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Container<Key, T>::iterator;
  using const_iterator = typename Container<Key, T>::const_iterator;
  using size_type = typename Container<Key, T>::size_type;

  Map() noexcept : Container<Key, T>() {}
  Map(std::initializer_list<value_type> const& items)
      : Container<Key, T>(items) {}
  Map(const Map& m) noexcept = default;
  Map(Map&& m) noexcept = default;
  ~Map() = default;
  Map<Key, T>& operator=(Map&& m) noexcept = default;
  Map<Key, T>& operator=(const Map& m) noexcept = default;

  std::pair<iterator, bool> Insert(const value_type& value) {
    return Container<Key, T>::Insert(value);
  }

  std::pair<iterator, bool> Insert(const Key& key, const T& obj) {
    value_type value(key, obj);
    return Insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type value(key, obj);
    auto result = Insert(value);
    if (!result.second) {
      if (result.first.getCurrent()->val_ != obj) {
        result.first.getCurrent()->val_ = obj;
        result.second = true;
      }
    }
    return result;
  }

  using Container<Key, T>::Begin;
  using Container<Key, T>::End;
  using Container<Key, T>::CBegin;
  using Container<Key, T>::CEnd;

  using Container<Key, T>::Merge;
  using Container<Key, T>::Clear;

  using Container<Key, T>::Swap;
  using Container<Key, T>::Erase;

  using Container<Key, T>::Find;
  using Container<Key, T>::Contains;

  using Container<Key, T>::Empty;
  using Container<Key, T>::Size;
  using Container<Key, T>::MaxSize;

  using Container<Key, T>::GetRoot;

  T& At(const Key& key) {
    iterator it = Find(key);
    if (it == End()) {
      throw std::out_of_range("Key not found in Map");
    }
    return it.getCurrent()->val_;
  }
  T& operator[](const Key& key) {
    iterator iter = Find(key);
    if (iter == End()) {
      value_type value(key, T());
      auto res = Insert(value);
      iter = res.first;
    }
    return iter.getCurrent()->val_;
  }

 private:
  using Container<Key, T>::root_;
  using Container<Key, T>::dummy_;
  using Container<Key, T>::size_cont_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_MAP_MAP_H_
