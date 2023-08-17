#ifndef SRC_S21_CONTAINERS_GENERAL_STRUCTURES_NODE_H_
#define SRC_S21_CONTAINERS_GENERAL_STRUCTURES_NODE_H_

enum NodeColors { RED, BLACK };

namespace s21 {

template <typename Key, typename T>
class Node {
 public:
  Key key_;
  T val_;
  Node<Key, T>* left_;
  Node<Key, T>* right_;
  Node<Key, T>* parent_;
  NodeColors color_;
  bool end_;

  Node()
      : key_(),
        val_(),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        color_(RED),
        end_(false) {}

  Node(const Node& other)
      : key_(other.key_),
        val_(other.val_),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        color_(other.color_),
        end_(other.end_) {}

  Node(Node&& other)
      : key_(std::move(other.key_)),
        val_(std::move(other.val_)),
        left_(other.left_),
        right_(other.right_),
        parent_(other.parent_),
        color_(other.color_),
        end_(other.end_) {
    other.key_ = Key();
    other.val_ = T();
    other.color_ = RED;
    other.left_ = nullptr;
    other.right_ = nullptr;
    other.parent_ = nullptr;
    other.end_ = false;
  }

  Node& operator=(const Node& other) {
    if (this != &other) {
      key_ = other.key_;
      val_ = other.val_;
      color_ = other.color_;
      end_ = other.end_;
      parent_ = other.parent_;
      left_ = other.left_;
      right_ = other.right_;
    }
    return *this;
  }

  Node& operator=(Node&& other) {
    if (this != &other) {
      key_ = std::move(other.key_);
      val_ = std::move(other.val_);
      color_ = other.color_;
      end_ = other.end_;
      left_ = other.left_;
      right_ = other.right_;
      parent_ = other.parent_;
      other.key_ = Key();
      other.val_ = T();
      other.color_ = RED;
      other.left_ = nullptr;
      other.right_ = nullptr;
      other.parent_ = nullptr;
      other.end_ = false;
    }
    return *this;
  }

  ~Node() {}
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_GENERAL_STRUCTURES_NODE_H_
