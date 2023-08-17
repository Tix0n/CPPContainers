namespace s21 {

template <typename T>
Vector<T>::Vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_type n)
    : arr_(new value_type[n]), size_(n), capacity_(n) {
  if (arr_ == nullptr) {
    throw std::bad_alloc();
  }
  for (size_type i = 0; i < n; ++i) {
    arr_[i] = T();
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : Vector(items.size()) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T>
Vector<T>::Vector(const Vector& v) : Vector(v.size_) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
Vector<T>::Vector(Vector&& v) {
  arr_ = v.arr_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
  if (this != &v) {
    delete[] arr_;
    arr_ = v.arr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::At(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out range");
  }
  return arr_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::Front() {
  if (Empty()) {
    throw std::out_of_range("Container is Empty");
  }
  return arr_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::Back() {
  if (Empty()) {
    throw std::out_of_range("Container is Empty");
  }
  return arr_[size_ - 1];
}

template <typename T>
T* Vector<T>::Data() {
  return arr_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Begin() {
  return iterator(arr_);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::End() {
  return iterator(arr_ + size_);
}

template <typename T>
bool Vector<T>::Empty() {
  return size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::Size() {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::MaxSize() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <typename T>
void Vector<T>::Reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }

  if (size > MaxSize()) {
    throw std::length_error(
        "Reserve capacity can't be larger than MaxSize of Vector");
  }

  Vector<value_type> Tmp(size);
  for (size_type i = 0; i < size_; ++i) {
    Tmp.arr_[i] = arr_[i];
  }
  Tmp.size_ = size_;
  *this = std::move(Tmp);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::Capacity() {
  return capacity_;
}

template <typename T>
void Vector<T>::ShrinkToFit() {
  if (size_ < capacity_) {
    Vector<value_type> tmp(size_);
    for (size_type i = 0; i < size_; ++i) {
      tmp.arr_[i] = arr_[i];
    }
    *this = std::move(tmp);
  }
}

template <typename T>
void Vector<T>::Clear() {
  size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - Begin();
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }
  if (size_ >= capacity_) {
    Reserve(size_ + 1);
  }
  for (size_type i = size_; i > index; --i) {
    arr_[i] = arr_[i - 1];
  }
  ++size_;
  arr_[index] = value;
  return Begin() + index;
}

template <typename T>
void Vector<T>::Erase(iterator pos) {
  size_type index = pos - Begin();
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }
  --size_;
  for (size_type i = index; i < size_; ++i) {
    arr_[i] = arr_[i + 1];
  }
}

template <typename T>
void Vector<T>::PushBack(const_reference value) {
  Insert(End(), value);
}

template <typename T>
void Vector<T>::PopBack() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void Vector<T>::Swap(Vector& other) {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}
}  // namespace s21
