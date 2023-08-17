namespace s21 {
template <typename T>
List<T>::List() noexcept : root_(nullptr), end_(nullptr), size_list_(0) {
  FakeEndElement();
}

template <typename T>
void List<T>::FakeEndElement() noexcept {
  fake_ = new node_type(T());
  fake_->next_ = nullptr;
  fake_->prev_ = nullptr;
}

template <typename T>
List<T>::List(size_type n) : root_(nullptr), end_(nullptr), size_list_(0) {
  if (n == 0) {
    throw std::out_of_range("Index out of range");
  }
  FakeEndElement();
  for (size_type i = 0; i < n; ++i) {
    PushBack(T());
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items) noexcept
    : root_(nullptr), end_(nullptr), size_list_(0) {
  FakeEndElement();
  for (const_reference item : items) {
    PushBack(item);
  }
}

template <typename T>
List<T>::List(const List& l) noexcept
    : root_(nullptr), end_(nullptr), size_list_(0) {
  FakeEndElement();
  *this = l;
}

template <typename T>
List<T>::List(List&& l) noexcept
    : root_(l.root_), end_(l.end_), size_list_(l.size_list_), fake_(l.fake_) {
  l.root_ = nullptr;
  l.end_ = nullptr;
  l.fake_ = nullptr;
  l.size_list_ = 0;
}

template <typename T>
List<T>::~List() noexcept {
  Clear();
  if (fake_ != nullptr) {
    delete fake_;
  }
  fake_ = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& l) noexcept {
  if (this != &l) {
    List<T> Tmp_lst(std::move(l));
    *this = Tmp_lst;
  }
  return *this;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) noexcept {
  if (this != &other) {
    Clear();

    if (!fake_) {
      FakeEndElement();
    }

    node_type* tmp_node = other.root_;
    while (tmp_node != other.fake_) {
      PushBack(tmp_node->value_);
      tmp_node = tmp_node->next_;
    }
  }
  return *this;
}

template <typename T>
typename List<T>::const_reference List<T>::Front() const {
  if (Empty()) {
    throw std::out_of_range("List is Empty");
  }
  return root_->value_;
}

template <typename T>
typename List<T>::const_reference List<T>::Back() const {
  if (Empty()) {
    throw std::out_of_range("List is Empty");
  }
  return end_->value_;
}

template <typename T>
typename List<T>::iterator List<T>::Begin() const noexcept {
  return iterator(root_ ? root_ : fake_);
}

template <typename T>
typename List<T>::iterator List<T>::End() const noexcept {
  return iterator(fake_);
}

template <typename T>
bool List<T>::Empty() const noexcept {
  return size_list_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::Size() const noexcept {
  return size_list_;
}

template <typename T>
typename List<T>::size_type List<T>::MaxSize() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(node_type) / 2;
}

template <typename T>
void List<T>::Clear() noexcept {
  while (size_list_ != 0) {
    PopFront();
  }
}

template <typename T>
typename List<T>::iterator List<T>::Insert(iterator pos,
                                           const_reference value) noexcept {
  node_type* new_node_ = new node_type{value, nullptr, nullptr};
  node_type* pos_node_ = pos.GetNodePointer();
  if (size_list_ == 0) {
    root_ = new_node_;
    end_ = new_node_;
    end_->next_ = fake_;
    root_->prev_ = fake_;
  } else if (pos_node_ == root_) {
    new_node_->next_ = root_;
    root_->prev_ = new_node_;
    root_ = new_node_;
  } else if (pos_node_ == fake_) {
    new_node_->prev_ = end_;
    end_->next_ = new_node_;
    end_ = new_node_;
    end_->next_ = fake_;
  } else {
    node_type* prev_node = pos_node_->prev_;
    new_node_->prev_ = prev_node;
    new_node_->next_ = pos_node_;
    pos_node_->prev_ = new_node_;
    prev_node->next_ = new_node_;
  }

  ++size_list_;
  fake_->prev_ = end_;
  fake_->next_ = root_;

  return iterator(new_node_);
}

template <typename T>
void List<T>::Erase(iterator pos) noexcept {
  node_type* pos_node_ = pos.GetNodePointer();
  if (pos_node_ != fake_) {
    if (pos_node_ == root_) {
      PopFront();
    } else if (pos_node_ == end_) {
      PopBack();
    } else {
      node_type* prev = pos_node_->prev_;
      node_type* next = pos_node_->next_;
      prev->next_ = next;
      next->prev_ = prev;
      --size_list_;
      delete pos_node_;
    }
  };
}

template <typename T>
void List<T>::PushBack(const_reference value) noexcept {
  node_type* new_node = new node_type{value, nullptr, nullptr};
  if (!root_) {
    root_ = new_node;
    root_->next_ = fake_;
    root_->prev_ = fake_;
    fake_->prev_ = root_;
    fake_->next_ = root_;
  } else if (!end_) {
    end_ = new_node;
    end_->next_ = fake_;
    end_->prev_ = root_;
    fake_->prev_ = end_;
    fake_->next_ = root_;
    root_->next_ = end_;
  } else {
    new_node->prev_ = end_;
    end_->next_ = new_node;
    end_ = new_node;
    end_->next_ = fake_;
    fake_->prev_ = end_;
  }
  ++size_list_;
}

template <typename T>
void List<T>::PopBack() noexcept {
  if (end_) {
    if (end_ == root_) {
      root_ = nullptr;
      end_ = nullptr;
      size_list_ = 0;
    } else {
      end_->next_->prev_ = end_->prev_;
      end_->prev_->next_ = fake_;
      node_type* rm_elem = end_;
      end_ = end_->prev_;
      delete rm_elem;
      --size_list_;
    }
  }
}

template <typename T>
void List<T>::PushFront(const_reference value) noexcept {
  node_type* new_node = new node_type{value, nullptr, nullptr};
  if (!root_) {
    root_ = new_node;
    root_->prev_ = fake_;
    root_->next_ = fake_;
    fake_->next_ = root_;
    fake_->prev_ = root_;
  } else if (!end_) {
    end_ = root_;
    end_->next_ = fake_;
    end_->prev_ = new_node;
    fake_->prev_ = end_;
    fake_->next_ = new_node;
    new_node->next_ = end_;
    root_ = new_node;
  } else {
    new_node->next_ = root_;
    root_ = new_node;
    fake_->next_ = root_;
    root_->prev_ = fake_;
  }
  ++size_list_;
}

template <typename T>
void List<T>::PopFront() noexcept {
  if (root_) {
    node_type* rm_elem = root_;
    if (root_->next_ != fake_) {
      root_ = root_->next_;
    } else {
      root_ = nullptr;
      end_ = nullptr;
    }

    if (rm_elem->next_) {
      rm_elem->next_->prev_ = fake_;
      delete rm_elem;
    }

    if (size_list_ == 2) {
      root_ = end_;
      fake_->next_ = root_;
      fake_->prev_ = root_;
      root_->next_ = fake_;
      root_->prev_ = fake_;
      end_ = nullptr;
    }
    --size_list_;
  }
}

template <typename T>
void List<T>::Swap(List& other) noexcept {
  node_type* swap_root_ = root_;
  node_type* swap_end_ = end_;
  node_type* swap_fake_ = fake_;
  size_type swap_size_ = size_list_;
  root_ = other.root_;
  end_ = other.end_;
  fake_ = other.fake_;
  size_list_ = other.size_list_;
  other.root_ = swap_root_;
  other.end_ = swap_end_;
  other.fake_ = swap_fake_;
  other.size_list_ = swap_size_;
}

template <typename T>
void List<T>::Merge(List& other) noexcept {
  if (this == &other) {
    return;
  }

  List<value_type> merged_list;

  while (!Empty() && !other.Empty()) {
    if (Front() <= other.Front()) {
      merged_list.PushBack(Front());
      PopFront();
    } else {
      merged_list.PushBack(other.Front());
      other.PopFront();
    }
  }
  while (!Empty()) {
    merged_list.PushBack(Front());
    PopFront();
  }
  while (!other.Empty()) {
    merged_list.PushBack(other.Front());
    other.PopFront();
  }
  Swap(merged_list);
}

template <typename T>
void List<T>::Splice(const_iterator pos, List& other) noexcept {
  List<T>::iterator pos_ = pos;
  node_type* pos_node_ = pos_.GetNodePointer();
  if (!other.Empty() && pos_node_ != nullptr) {
    if (pos_node_ == root_) {
      other.end_->next_ = root_;
      root_->prev_ = other.end_;
      root_ = other.root_;
    } else if (pos_node_ == end_) {
      end_->next_ = other.root_;
      other.root_->prev_ = end_;
      end_ = other.end_;
    } else {
      pos_node_->prev_->next_ = other.root_;
      other.root_->prev_ = pos_node_->prev_;
      other.end_->next_ = pos_node_;
      pos_node_->prev_ = other.end_;
    }
    size_list_ += other.size_list_;
  }
  other.root_ = nullptr;
  other.end_ = nullptr;
  if (other.fake_ != nullptr) {
    delete other.fake_;
  }
  other.fake_ = nullptr;
  other.size_list_ = 0;
}

template <typename T>
void List<T>::Reverse() noexcept {
  if (size_list_ > 1) {
    node_type* current_ = end_;
    node_type* tmp_ = nullptr;
    while (current_ != fake_) {
      current_->next_ = current_->prev_;
      current_->prev_->next_ = current_;
      current_ = current_->prev_;
    }

    tmp_ = root_;
    root_ = end_;
    end_ = tmp_;
  }
}

template <typename T>
void List<T>::Unique() noexcept {
  if (size_list_ > 1) {
    node_type* current_ = root_;
    node_type* next_node_ = nullptr;

    while (current_->next_ != fake_) {
      next_node_ = current_->next_;
      if (current_->value_ == next_node_->value_) {
        current_->next_ = next_node_->next_;
        next_node_->next_->prev_ = current_;
        --size_list_;
        if (next_node_ != nullptr) {
          delete next_node_;
          next_node_ = nullptr;
        }
      } else {
        current_ = current_->next_;
      }
    }
    end_ = fake_->prev_;
  }
}

template <typename T>
void List<T>::Sort() noexcept {
  if (size_list_ > 1) {
    for (node_type* it_i = root_; it_i != fake_; it_i = it_i->next_) {
      for (node_type* it_j = root_; it_j != fake_; it_j = it_j->next_) {
        value_type tmp_;
        if (it_j->value_ > it_i->value_) {
          tmp_ = it_j->value_;
          it_j->value_ = it_i->value_;
          it_i->value_ = tmp_;
        }
      }
    }
  }
}
}  // namespace s21
