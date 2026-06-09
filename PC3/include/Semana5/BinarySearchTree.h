#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

#include "BinaryTree.h"

namespace ods {

template <typename T, typename Compare = std::less<T>>
class BinarySearchTree : public BinaryTree<T> {
 public:
  using Node = typename BinaryTree<T>::Node;
  using BinaryTree<T>::root_;
  using BinaryTree<T>::updateHeight;
  using BinaryTree<T>::updateHeightAbove;
  using BinaryTree<T>::size_;

  BinarySearchTree() = default;

  explicit BinarySearchTree(Compare cmp) : comp_(cmp) {}

  Node* findLast(const T& value) const { // 
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(value, w->data)) { // si value es menor que w->data, sigue buscando en el subárbol izquierdo
        w = w->left;
      } else if (comp_(w->data, value)) { // si value es mayor que w->data, sigue buscando en el subárbol derecho
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& value) const { // busca un nodo con valor exactamente igual a value, o nullptr si no existe
    Node* w = root_; // comienza la búsqueda desde la raíz
    while (w != nullptr) {
      if (comp_(value, w->data)) { // si value es menor que w->data, sigue buscando en el subárbol izquierdo
        w = w->left;
      } else if (comp_(w->data, value)) { // si value es mayor que w->data, sigue buscando en el subárbol derecho
        w = w->right;
      } else {
        return w; // si value es igual a w->data, se encontró el nodo y se devuelve
      }
    }
    return nullptr; // si se llega a un nodo nulo, significa que no se encontró un nodo con valor igual a value, por lo que se devuelve nullptr
  } // findEQ vs findLast: findEQ busca un nodo con valor exactamente igual a value, mientras que findLast busca el nodo padre adecuado para insertar un nuevo nodo con valor value, lo que puede ser un nodo con valor igual a value o un nodo con valor menor o mayor que value dependiendo de la estructura del árbol

  Node* lowerBound(const T& value) const { // busca el nodo con el valor más pequeño que sea mayor o igual a value, o nullptr si no existe
    Node* w = root_; // comienza la búsqueda desde la raíz
    Node* candidate = nullptr; // 
    while (w != nullptr) { // complejidad O(h) donde h es la altura del árbol, ya que en el peor caso se puede recorrer desde la raíz hasta una hoja
      if (comp_(value, w->data)) { // si value es menor que w->data, w es un candidato a ser el nodo buscado, pero sigue buscando en el subárbol izquierdo para encontrar un nodo con valor más pequeño que sea mayor o igual a value
        candidate = w;
        w = w->left;
      } else if (comp_(w->data, value)) { // si value es mayor que w->data, sigue buscando en el subárbol derecho para encontrar un nodo con valor mayor o igual a value
        w = w->right;
      } else {
        return w;
      }
    }
    return candidate; // si se llega a un nodo nulo, significa que no se encontró un nodo con valor igual a value, por lo que se devuelve el candidato encontrado durante la búsqueda, que puede ser nullptr si no se encontró ningún nodo con valor mayor o igual a value
  }

  Node* upperBound(const T& value) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(value, w->data)) {
        candidate = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    return candidate;
  }

  Node* find(const T& value) const {
    return lowerBound(value);
  }

  Node* minNode() const { 
    return root_ == nullptr ? nullptr : root_->leftmost();
  }

  Node* maxNode() const {
    return root_ == nullptr ? nullptr : root_->rightmost();
  }

  bool contains(const T& value) const { return findEQ(value) != nullptr; }

  bool add(const T& value) { // agrega un nuevo nodo con valor value al árbol, manteniendo la propiedad de búsqueda binaria, y devuelve true si se agregó el nodo o false si ya existe un nodo con valor igual a value
    Node* node = new Node(value);
    if (!add(node)) {
      delete node;
      return false;
    }
    return true;
  }

  bool add(Node* node) {
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;
    Node* parent = findLast(node->data); // encuentra el nodo padre adecuado para el nuevo nodo
    return addChild(parent, node); // decide dónde agregar el nuevo nodo y actualizar el árbol en consecuencia
  }

  bool addChild(Node* parent, Node* node) { 
    if (parent == nullptr) {
      root_ = node;
      node->parent = nullptr;
      ++size_;
      return true;
    }

    if (comp_(node->data, parent->data)) { // el nuevo nodo es menor que el padre, va a la izquierda
      if (parent->left != nullptr) { // si ya hay un nodo a la izquierda del padre, no se puede agregar el nuevo nodo
        return false;
      }
      parent->left = node;
    } else if (comp_(parent->data, node->data)) {
      if (parent->right != nullptr) { // el nuevo nodo es mayor que el padre, va a la derecha, pero si ya hay un nodo a la derecha del padre, no se puede agregar el nuevo nodo
        return false;
      }
      parent->right = node;
    } else {
      return false;
    }

    node->parent = parent;
    ++size_;
    updateHeightAbove(parent);
    return true;
  }

  bool remove(const T& value) {
    Node* u = findEQ(value);
    if (u == nullptr) {
      return false;
    }
    remove(u);
    return true;
  }

  void remove(Node* node) {
    if (node == nullptr) {
      return;
    }

    if (node->left == nullptr || node->right == nullptr) {
      splice(node);
      delete node;
      return;
    }

    Node* w = node->succ();
    node->data = w->data;
    splice(w);
    delete w;
  }

  void splice(Node* node) {
    Node* child = (node->left != nullptr) ? node->left : node->right;
    Node* parent = node->parent;

    if (node == root_) {
      root_ = child;
    } else if (node->isLeftChild()) {
      parent->left = child;
    } else {
      parent->right = child;
    }

    if (child != nullptr) {
      child->parent = parent;
    }

    --size_;
    updateHeightAbove(parent);
  }

  void rotateLeft(Node* u) {
    if (u == nullptr || u->right == nullptr) {
      return;
    }

    Node* w = u->right;
    w->parent = u->parent;

    if (u->parent == nullptr) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }

    u->right = w->left;
    if (u->right != nullptr) {
      u->right->parent = u;
    }

    w->left = u;
    u->parent = w;

    updateHeight(u);
    updateHeight(w);
    updateHeightAbove(w->parent);
  }

  void rotateRight(Node* u) {
    if (u == nullptr || u->left == nullptr) {
      return;
    }

    Node* w = u->left;
    w->parent = u->parent;

    if (u->parent == nullptr) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }

    u->left = w->right;
    if (u->left != nullptr) {
      u->left->parent = u;
    }

    w->right = u;
    u->parent = w;

    updateHeight(u);
    updateHeight(w);
    updateHeightAbove(w->parent);
  }

  bool isBST() const { // verifica que el árbol cumple la propiedad de búsqueda binaria y que los enlaces parent son correctos
    return isBST(root_, nullptr, nullptr) && this->checkParentLinks(); // checkParentLinks es un método heredado de BinaryTree que verifica que los enlaces parent de los nodos son correctos
  }

  static BinarySearchTree buildBalancedFromSorted(const std::vector<T>& sorted, // 
                                                  Compare cmp = Compare{}) {
    BinarySearchTree tree(cmp);
    tree.root_ = buildBalancedRecursive(sorted, 0, static_cast<int>(sorted.size()), nullptr);
    tree.size_ = sorted.size();
    tree.updateHeightAbove(tree.root_);
    return tree;
  }

  const Compare& comparator() const { return comp_; }

 private:
  Compare comp_{};

  bool isBST(const Node* node, const T* low, const T* high) const {
    if (node == nullptr) {
      return true;
    }
    if (low != nullptr && !comp_(*low, node->data)) {
      return false;
    }
    if (high != nullptr && !comp_(node->data, *high)) {
      return false;
    }
    return isBST(node->left, low, &node->data) && isBST(node->right, &node->data, high);
  }

  static Node* buildBalancedRecursive(const std::vector<T>& sorted, int lo, int hi, Node* parent) {
    if (lo >= hi) {
      return nullptr;
    }
    const int mid = lo + (hi - lo) / 2;
    Node* node = new Node(sorted[mid], parent);
    node->left = buildBalancedRecursive(sorted, lo, mid, node);
    node->right = buildBalancedRecursive(sorted, mid + 1, hi, node);
    node->height = 1 + std::max(stature(node->left), stature(node->right));
    return node;
  }
};

}  // namespace ods
