namespace s21 {

template <typename T>
Queue<T>::Queue() noexcept : root_(nullptr), end_(nullptr), size_queue_(0) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const& items) noexcept
    : Queue() {
  for (const auto& item : items) {
    Push(item);
  }
}

template <typename T>
Queue<T>::Queue(const Queue& q) noexcept : Queue() {
  node* current = q.root_;
  while (current) {
    Push(current->value_);
    current = current->next_;
  }
}

template <typename T>
Queue<T>::Queue(Queue&& q) noexcept
    : root_(q.root_), end_(q.end_), size_queue_(q.size_queue_) {
  q.root_ = nullptr;
  q.end_ = nullptr;
  q.size_queue_ = 0;
}

template <typename T>
Queue<T>::~Queue() noexcept {
  while (root_) {
    node* temp_ = root_->next_;
    delete root_;
    root_ = temp_;
  }
}

template <typename T>
void Queue<T>::operator=(Queue&& q) noexcept {
  if (this != &q) {
    while (root_) {
      node* temp_ = root_->next_;
      delete root_;
      root_ = temp_;
    }
    root_ = q.root_;
    end_ = q.end_;
    size_queue_ = q.size_queue_;
    q.root_ = nullptr;
    q.end_ = nullptr;
    q.size_queue_ = 0;
  }
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::Front() const {
  if (Empty()) {
    throw std::out_of_range("Queue is Empty");
  }
  return root_->value_;
}

template <typename T>
bool Queue<T>::Empty() const noexcept {
  return size_queue_ == 0;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::Size() const noexcept {
  return size_queue_;
}

template <typename T>
void Queue<T>::Push(const_reference value) noexcept {
  node* new_node_ = new node{value, nullptr};
  if (Empty()) {
    root_ = new_node_;
    end_ = new_node_;
  } else {
    end_->next_ = new_node_;
    end_ = new_node_;
  }
  ++size_queue_;
}

template <typename T>
void Queue<T>::Pop() noexcept {
  if (!Empty()) {
    node* temp_ = root_;
    root_ = root_->next_;
    delete temp_;

    if (root_ == nullptr) {
      end_ = nullptr;
    }
    --size_queue_;
  }
}

template <typename T>
void Queue<T>::Swap(Queue& other) noexcept {
  node* tmp_root_ = root_;
  node* tmp_end_ = end_;
  root_ = other.root_;
  other.root_ = tmp_root_;
  end_ = other.end_;
  other.end_ = tmp_end_;

  size_type tmp_size_ = size_queue_;
  size_queue_ = other.size_queue_;
  other.size_queue_ = tmp_size_;
}

}  // namespace s21
