namespace s21 {

template <typename T>
Stack<T>::Stack() noexcept {
  size_stack_ = 0;
  root_ = nullptr;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const& items) noexcept {
  size_stack_ = 0;
  root_ = nullptr;
  for (const value_type& item : items) {
    Push(item);
  }
}

template <typename T>
Stack<T>::Stack(const Stack& s) noexcept {
  size_stack_ = s.size_stack_;
  root_ = nullptr;
  if (s.root_ != nullptr) {
    root_ = new node{s.root_->value_, nullptr};
    node* current = root_;
    node* current_s = s.root_->next_;
    while (current_s != nullptr) {
      current->next_ = new node{current_s->value_, nullptr};
      current = current->next_;
      current_s = current_s->next_;
    }
  }
}

template <typename T>
Stack<T>::Stack(Stack&& s) noexcept {
  size_stack_ = s.size_stack_;
  root_ = s.root_;
  s.size_stack_ = 0;
  s.root_ = nullptr;
}

template <typename T>
Stack<T>::~Stack() noexcept {
  Clear();
}

template <typename T>
void Stack<T>::Clear() noexcept {
  while (root_ != nullptr) {
    node* tmp = root_;
    root_ = root_->next_;
    delete tmp;
  }
  size_stack_ = 0;
}

template <typename T>
void Stack<T>::Push(const_reference value) noexcept {
  node* tmp = new node;
  tmp->value_ = value;
  if (root_) {
    tmp->next_ = root_;
    root_ = tmp;
  } else {
    root_ = tmp;
    root_->next_ = nullptr;
  }
  size_stack_++;
}

template <typename T>
void Stack<T>::Pop() noexcept {
  if (root_) {
    node* tmp = root_->next_;
    delete root_;
    root_ = tmp;
    size_stack_--;
  }
}

template <typename T>
void Stack<T>::Swap(Stack& other) noexcept {
  node* tmp = root_;
  root_ = other.root_;
  other.root_ = tmp;

  size_type tmp_size = size_stack_;
  size_stack_ = other.size_stack_;
  other.size_stack_ = tmp_size;
}

template <typename T>
bool Stack<T>::Empty() const noexcept {
  return root_ == nullptr;
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::Top() const {
  if (root_ == nullptr) {
    throw std::out_of_range("Stack is empty.");
  }
  return root_->value_;
}

template <typename T>
void Stack<T>::operator=(Stack&& s) noexcept {
  if (this != &s) {
    Clear();
    size_stack_ = s.size_stack_;
    root_ = s.root_;
    s.size_stack_ = 0;
    s.root_ = nullptr;
  }
}

template <typename T>
typename Stack<T>::size_type Stack<T>::Size() const noexcept {
  return size_stack_;
}

}  // namespace s21
