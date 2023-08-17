#ifndef SRC_S21_CONTAINERS_VECTOR_VECTOR_ITERATORS_H_
#define SRC_S21_CONTAINERS_VECTOR_VECTOR_ITERATORS_H_

namespace s21 {
template <typename T>
class VectorIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using difference_type = std::ptrdiff_t;
  using iterator = VectorIterator<T>;

  VectorIterator() : ptr_(nullptr) {}
  VectorIterator(pointer ptr) : ptr_(ptr) {}
  reference operator*() const { return *ptr_; }
  pointer operator->() const { return ptr_; }

  iterator& operator++() {
    ++ptr_;
    return *this;
  }

  iterator operator++(int) {
    iterator temp(*this);
    ++ptr_;
    return temp;
  }

  iterator& operator--() {
    --ptr_;
    return *this;
  }

  iterator operator--(int) {
    VectorIterator temp(*this);
    --ptr_;
    return temp;
  }

  iterator operator+(difference_type n) const {
    return VectorIterator(ptr_ + n);
  }

  iterator operator-(difference_type n) const {
    return VectorIterator(ptr_ - n);
  }

  difference_type operator-(const iterator& other) const {
    return ptr_ - other.ptr_;
  }

  iterator& operator+=(difference_type n) {
    ptr_ += n;
    return *this;
  }

  iterator& operator-=(difference_type n) {
    ptr_ -= n;
    return *this;
  }

  reference operator[](difference_type n) const { return ptr_[n]; }

  bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }

  bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

  bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }

  bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }

  bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }

  bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

  iterator GetPointer() { return ptr_; }

 private:
  pointer ptr_;
};

template <typename T>
class VectorConstIterator {
 public:
  using value_type = T;
  using reference = const T&;
  using pointer = const T*;
  using difference_type = std::ptrdiff_t;
  using const_iterator = VectorConstIterator<T>;
  using iterator = VectorIterator<T>;

  VectorConstIterator() : ptr_(nullptr) {}

  VectorConstIterator(pointer ptr) : ptr_(ptr) {}

  VectorConstIterator(const iterator& it) : ptr_(it.GetPointer()) {}

  reference operator*() const { return *ptr_; }

  const_iterator& operator++() {
    ++ptr_;
    return *this;
  }

  const_iterator operator++(int) {
    VectorConstIterator temp(*this);
    ++ptr_;
    return temp;
  }

  const_iterator& operator--() {
    --ptr_;
    return *this;
  }

  const_iterator operator--(int) {
    VectorConstIterator temp(*this);
    --ptr_;
    return temp;
  }

  reference operator[](difference_type n) const { return ptr_[n]; }

  bool operator==(const const_iterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const const_iterator& other) const {
    return ptr_ != other.ptr_;
  }

 private:
  pointer ptr_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_VECTOR_VECTOR_ITERATORS_H_
