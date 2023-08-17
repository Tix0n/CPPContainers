#include "container.h"
namespace s21 {

template <typename Key, typename T>
Container<Key, T>::Container() noexcept : root_(nullptr), size_cont_(0) {
  dummy_ = new Node<Key, T>;
  dummy_->end_ = true;
  dummy_->color_ = BLACK;
  dummy_->left_ = nullptr;
  dummy_->right_ = nullptr;
  dummy_->parent_ = nullptr;
}

template <typename Key, typename T>
Container<Key, T>::Container(
    std::initializer_list<value_type> const& items) noexcept
    : Container() {
  for (const auto& item : items) {
    Insert(item);
  }
}

template <typename Key, typename T>
Container<Key, T>::Container(const Container& other) noexcept : Container() {
  if (this != &other) {
    for (auto it = other.Begin(); it != other.End(); ++it) {
      if constexpr (std::is_same_v<Key, T>) {
        Insert(it.GetKey());
      } else {
        value_type value(it.GetKey(), it.GetVal());
        Insert(value);
      }
    }
  }
}

template <typename Key, typename T>
Container<Key, T>::Container(Container&& other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    size_cont_ = other.size_cont_;
    dummy_ = other.dummy_;

    other.root_ = nullptr;
    other.size_cont_ = 0;
    other.dummy_ = nullptr;
  }
}

template <typename Key, typename T>
Container<Key, T>::~Container() {
  DeleteTree(root_);
  if (dummy_) delete dummy_;
}

template <typename Key, typename T>
void Container<Key, T>::DeleteTree(Node<Key, T>* node) noexcept {
  if (node && node->end_ != true) {
    Node<Key, T>* left = node->left_;
    Node<Key, T>* right = node->right_;
    delete node;
    node = nullptr;
    if (left) DeleteTree(left);
    if (right) DeleteTree(right);
  }
}

template <typename Key, typename T>
void Container<Key, T>::operator=(Container&& other) noexcept {
  if (this != &other) {
    DeleteTree(root_);
    if (dummy_) delete dummy_;
    root_ = other.root_;
    size_cont_ = other.size_cont_;
    dummy_ = other.dummy_;

    other.root_ = nullptr;
    other.size_cont_ = 0;
    other.dummy_ = nullptr;
  }
}

template <typename Key, typename T>
Container<Key, T>& Container<Key, T>::operator=(
    const Container& other) noexcept {
  if (this != &other) {
    Container<Key, T> temp(other);

    std::swap(root_, temp.root_);
    std::swap(size_cont_, temp.size_cont_);
    std::swap(dummy_, temp.dummy_);
  }
  return *this;
}

template <typename Key, typename T>
bool Container<Key, T>::Empty() const noexcept {
  return size_cont_ <= 0;
}

template <typename Key, typename T>
typename Container<Key, T>::size_type Container<Key, T>::Size() const noexcept {
  return size_cont_;
}

template <typename Key, typename T>
typename Container<Key, T>::size_type Container<Key, T>::MaxSize()
    const noexcept {
  return SIZE_MAX / (2 * sizeof(Node<Key, T>));
}

template <typename Key, typename T>
template <typename V>
std::pair<typename Container<Key, T>::iterator, bool> Container<Key, T>::Insert(
    const V& val_) {
  std::pair<iterator, bool> m;
  m.second = false;
  Node<Key, T>* current = root_;
  Node<Key, T>* parent_ = nullptr;
  Key key;
  if constexpr (std::is_same_v<V, key_type>) {
    key = val_;
  } else {
    key = val_.first;
  }
  while (current != nullptr && current->end_ != true) {
    parent_ = current;
    if (key < current->key_) {
      current = current->left_;
    } else if (key > current->key_) {
      current = current->right_;
    } else {
      m.first = iterator(current);
      return m;
    }
  }
  Node<Key, T>* newNode = new Node<Key, T>();
  if constexpr (std::is_same_v<V, key_type>) {
    newNode->key_ = val_;
    newNode->val_ = T{};
  } else {
    newNode->key_ = val_.first;
    newNode->val_ = val_.second;
  }
  newNode->parent_ = parent_;
  newNode->color_ = RED;
  newNode->left_ = dummy_;
  newNode->right_ = dummy_;

  if (parent_ == nullptr) {
    root_ = newNode;
  } else if (key < parent_->key_) {
    parent_->left_ = newNode;
  } else {
    parent_->right_ = newNode;
  }
  size_cont_++;
  m.first = iterator(newNode);
  m.second = true;
  Rebalancing(newNode);
  return m;
}

template <typename Key, typename T>
void Container<Key, T>::Rebalancing(Node<Key, T>* x) noexcept {
  while (x != root_ && x->parent_->color_ == RED) {
    if (x->parent_ == x->parent_->parent_->left_) {
      Node<Key, T>* uncle = x->parent_->parent_->right_;
      if (uncle->color_ == RED) {
        x->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        x->parent_->parent_->color_ = RED;
        x = x->parent_->parent_;
      } else {
        if (x == x->parent_->right_) {
          x = x->parent_;
          RotateLeft(x);
        }
        x->parent_->color_ = BLACK;
        x->parent_->parent_->color_ = RED;
        RotateRight(x->parent_->parent_);
      }
    } else {
      Node<Key, T>* uncle = x->parent_->parent_->left_;
      if (uncle->color_ == RED) {
        x->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        x->parent_->parent_->color_ = RED;
        x = x->parent_->parent_;
      } else {
        if (x == x->parent_->left_) {
          x = x->parent_;
          RotateRight(x);
        }
        x->parent_->color_ = BLACK;
        x->parent_->parent_->color_ = RED;
        RotateLeft(x->parent_->parent_);
      }
    }
  }
  root_->color_ = BLACK;
}

template <typename Key, typename T>
void Container<Key, T>::RotateLeft(Node<Key, T>* x) noexcept {
  Node<Key, T>* y = x->right_;
  x->right_ = y->left_;
  if (y->left_ != dummy_) y->left_->parent_ = x;

  if (y != dummy_) y->parent_ = x->parent_;

  if (x->parent_ == nullptr) {
    root_ = y;
  } else if (x == x->parent_->left_) {
    x->parent_->left_ = y;
  } else {
    x->parent_->right_ = y;
  }

  y->left_ = x;
  if (x != dummy_) x->parent_ = y;
}

template <typename Key, typename T>
void Container<Key, T>::RotateRight(Node<Key, T>* x) noexcept {
  Node<Key, T>* y = x->left_;
  x->left_ = y->right_;
  if (y->right_ != dummy_) y->right_->parent_ = x;

  if (y != dummy_) y->parent_ = x->parent_;

  if (x->parent_ == nullptr) {
    root_ = y;
  } else if (x == x->parent_->right_) {
    x->parent_->right_ = y;
  } else {
    x->parent_->left_ = y;
  }

  y->right_ = x;
  if (x != dummy_) x->parent_ = y;
}

template <typename Key, typename T>
typename Container<Key, T>::iterator Container<Key, T>::Begin() const noexcept {
  Node<Key, T>* p = nullptr;
  if (!root_) {
    p = dummy_;
  } else {
    p = root_;
    while (p && p->left_ && p->left_->end_ != true) p = p->left_;
  }
  return iterator(p);
}

template <typename Key, typename T>
typename Container<Key, T>::iterator Container<Key, T>::End() const noexcept {
  Node<Key, T>* p = nullptr;
  if (!root_) {
    p = dummy_;
  } else {
    p = root_;
    while (p && p->right_ && p->right_->end_ != true) p = p->right_;
    Node<Key, T>* save = p;
    p = p->right_;
    p->parent_ = save;
  }
  return iterator{p};
}

template <typename Key, typename T>
void Container<Key, T>::Swap(Container& other) noexcept {
  if (this == &other) {
    return;
  }

  Node<Key, T>* tmpRoot = root_;
  root_ = other.root_;
  other.root_ = tmpRoot;

  Node<Key, T>* tmpDummy = dummy_;
  dummy_ = other.dummy_;
  other.dummy_ = tmpDummy;

  size_type tmpSize = size_cont_;
  size_cont_ = other.size_cont_;
  other.size_cont_ = tmpSize;
}

template <typename Key, typename T>
void Container<Key, T>::Merge(Container& other) noexcept {
  if (this == &other) {
    return;
  }
  std::pair<Container<Key, T>::iterator, bool> res;
  for (auto it = other.Begin(); it != other.End();) {
    it = other.Begin();
    for (; it != other.End(); ++it) {
      if constexpr (std::is_same_v<Key, T>) {
        res = Insert(it.GetKey());
      } else {
        value_type value(it.GetKey(), it.GetVal());
        res = Insert(value);
      }

      if (res.second) {
        other.Erase(it);
        break;
      }
    }
  }
}

template <typename Key, typename T>
void Container<Key, T>::Clear() noexcept {
  DeleteTree(root_);
  root_ = nullptr;
  size_cont_ = 0;
  if (dummy_) {
    delete dummy_;
    dummy_ = nullptr;
  }
}

template <typename Key, typename T>
void Container<Key, T>::Erase(typename Container<Key, T>::iterator pos) {
  Node<Key, T>* node = pos.getCurrent();
  if (size_cont_ == 1) {
    delete root_;
    root_ = nullptr;
    size_cont_ = 0;
    return;
  }
  if (node->end_) {
    return;
  }
  if (!node->left_->end_ && !node->right_->end_) {
    Node<Key, T>* x = node->right_;
    while (!x->left_->end_) {
      x = x->left_;
    }
    node->key_ = x->key_;
    node->val_ = x->val_;
    node = x;
  }
  if (node->left_->end_ && node->right_->end_ && node->color_ == RED) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = dummy_;
    } else {
      node->parent_->right_ = dummy_;
    }
    dummy_->parent_ = node->parent_;
    delete node;
    size_cont_--;
    return;
  }
  if (node->left_->end_ || node->right_->end_) {
    Node<Key, T>* child = node->left_->end_ ? node->right_ : node->left_;
    bool is_black = node->color_ == BLACK;
    child->parent_ = node->parent_;
    if (node->parent_ == nullptr) {
      root_ = child;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = child;
    } else {
      node->parent_->right_ = child;
    }
    if (is_black) {
      EraseFixup(child);
    }
    delete node;
    size_cont_--;
  }
}

template <typename Key, typename T>
void Container<Key, T>::EraseFixup(Node<Key, T>* x) noexcept {
  while (x != root_ && x->color_ == BLACK) {
    Node<Key, T>* parent_ = x->parent_;
    Node<Key, T>* sibling =
        (x == parent_->left_) ? parent_->right_ : parent_->left_;
    if (sibling->color_ == RED) {
      sibling->color_ = BLACK;
      parent_->color_ = RED;
      if (x == parent_->left_)
        RotateLeft(parent_);
      else
        RotateRight(parent_);
      sibling = (x == parent_->left_) ? parent_->right_ : parent_->left_;
    }

    if (sibling->left_->color_ == BLACK && sibling->right_->color_ == BLACK) {
      sibling->color_ = RED;
      x = parent_;
    } else {
      if (x == parent_->left_) {
        if (sibling->right_->color_ == BLACK) {
          sibling->left_->color_ = BLACK;
          sibling->color_ = RED;
          RotateRight(sibling);
          sibling = parent_->right_;
        }
        sibling->color_ = parent_->color_;
        parent_->color_ = BLACK;
        sibling->right_->color_ = BLACK;
        RotateLeft(parent_);
      } else {
        if (sibling->left_->color_ == BLACK) {
          sibling->right_->color_ = BLACK;
          sibling->color_ = RED;
          RotateLeft(sibling);
          sibling = parent_->left_;
        }
        sibling->color_ = parent_->color_;
        parent_->color_ = BLACK;
        sibling->left_->color_ = BLACK;
        RotateRight(parent_);
      }
      x = root_;
    }
  }
  x->color_ = BLACK;
}

template <typename Key, typename T>
Node<Key, T>* Container<Key, T>::GetRoot() const {
  return root_;
}

template <typename Key, typename T>
typename Container<Key, T>::iterator Container<Key, T>::Find(
    const Key& key) noexcept {
  iterator it = Begin();
  while (it != End()) {
    if (it.GetKey() == key) {
      return it;
    }
    ++it;
  }
  return End();
}

template <typename Key, typename T>
bool Container<Key, T>::Contains(const Key& key) noexcept {
  iterator it = Find(key);
  return (it != End());
}

template <typename Key, typename T>
void Container<Key, T>::PrintTree(Node<Key, T>* node, int indent,
                                  int level) const {
  if (node != nullptr) {
    std::string color_ = (node->color_ == NodeColors::RED)
                             ? "\x1b[31mRed\x1b[0m"
                             : "\x1b[30mBlack\x1b[0m";

    PrintTree(node->right_, indent + 4, level + 1);

    if (indent > 0) {
      std::cout << std::setw(indent) << " ";
    }

    std::cout << "L" << level << ":<" << node->key_ << ">,<" << node->val_
              << "> (" << color_ << ")" << std::endl;

    PrintTree(node->left_, indent + 4, level + 1);
  }
}
template <typename Key, typename T>
void Container<Key, T>::PrintTree() const {
  PrintTree(root_, 0, 0);
}

template <typename Key, typename T>
typename Container<Key, T>::const_iterator Container<Key, T>::CBegin()
    const noexcept {
  return const_iterator(const_cast<Node<Key, T>*>(Begin().getCurrent()));
}

template <typename Key, typename T>
typename Container<Key, T>::const_iterator Container<Key, T>::CEnd()
    const noexcept {
  return const_iterator(const_cast<Node<Key, T>*>(End().getCurrent()));
}

}  // namespace s21
