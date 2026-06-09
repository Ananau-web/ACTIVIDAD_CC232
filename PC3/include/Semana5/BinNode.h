#pragma once

#include <cstddef>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

namespace ods {

enum class InorderStrategy {
  Recursive,
  Iterative1,
  Iterative2,
  Iterative3,
};

template <typename T> // Nodo de un árbol binario
struct BinNode { 
  using Node = BinNode<T>; // Alias para simplificar la sintaxis

  T data{}; // Valor almacenado en el nodo
  Node* parent{nullptr};  // Puntero al nodo padre, permite subir por le árbol(útil para calcular alturas o buscar sucesores sin usar recursión)
  Node* left{nullptr};    // Puntero al hijo izquierdo
  Node* right{nullptr};   // Puntero al hijo derecho
  int height{0};          // guarda la altura del subárbol que tiene a este nodo como raíz

  BinNode() = default; // Constructor por defecto

  explicit BinNode(const T& value, Node* p = nullptr) // Constructor con valor y puntero al padre
      : data(value), parent(p) {} // Inicializa el nodo con un valor y un puntero al padre

  bool hasLeft() const { return left != nullptr; } // verifica si el arbol tiene un hijo izquierdo
  bool hasRight() const { return right != nullptr; } // verifica si el arbol tiene un hijo derecho
  bool isRoot() const { return parent == nullptr; } // verifica si el nodo es la raíz del árbol (no tiene padre)
  bool isLeaf() const { return left == nullptr && right == nullptr; } // verifica si el nodo es una hoja (no tiene hijos)
  bool isLeftChild() const { return parent != nullptr && parent->left == this; } // Sabe que es el hijo izquierdo si su padre existe y el puntero left del padre apunta hacia él mismo this
  bool isRightChild() const { return parent != nullptr && parent->right == this; } // Sabe que es el hijo derecho si su padre existe y el puntero right del padre apunta hacia él mismo this

  Node* insertAsLC(const T& value) { // Se crean el hijo Left child, se asigna el valor y se establece el puntero al padre
    if (left != nullptr) { 
      throw std::logic_error("El hijo izquierdo ya existe"); 
      /*throw std::logic_error(""); sirve para señalar un error lógico en el flujo del programa y deterner la ejecución normal*/
    }
    left = new Node(value, this); // Crea un nuevo nodo con el valor dado y establece el puntero al padre (this)  
    return left; // Devuelve un puntero al nuevo nodo creado
  }

  Node* insertAsRC(const T& value) { // Se crean el hijo Right child, se asigna el valor y se establece el puntero al padre
    if (right != nullptr) { 
      throw std::logic_error("El hijo derecho ya existe");
    }
    right = new Node(value, this);
    return right;
  }

  std::size_t size() const { // Calcula el tamaño del subárbol que tiene a este nodo como raíz
    const std::size_t ls = (left == nullptr) ? 0U : left->size(); // Si el hijo izquierdo es nulo, el tamaño del subárbol izquierdo es 0, de lo contrario, se llama recursivamente a size() en el hijo izquierdo para obtener su tamaño
    const std::size_t rs = (right == nullptr) ? 0U : right->size(); // Si el hijo derecho es nulo, el tamaño del subárbol derecho es 0, de lo contrario, se llama recursivamente a size() en el hijo derecho para obtener su tamaño
    return 1U + ls + rs; // El tamaño total del subárbol es 1 (por el nodo actual) más el tamaño del subárbol izquierdo y el tamaño del subárbol derecho
  }

  Node* leftmost() {
    Node* u = this;
    while (u->left != nullptr) {
      u = u->left;
    }
    return u;
  }

  const Node* leftmost() const {
    const Node* u = this;
    while (u->left != nullptr) {
      u = u->left;
    }
    return u;
  }

  Node* rightmost() {
    Node* u = this;
    while (u->right != nullptr) {
      u = u->right;
    }
    return u;
  }

  const Node* rightmost() const {
    const Node* u = this;
    while (u->right != nullptr) {
      u = u->right;
    }
    return u;
  }

  Node*   () {
    Node* s = this;
    if (right != nullptr) {
      s = right;
      while (s->left != nullptr) {
        s = s->left;
      }
      return s;
    }
    while (s->isRightChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  const Node* succ() const {
    const Node* s = this;
    if (right != nullptr) {
      s = right;
      while (s->left != nullptr) {
        s = s->left;
      }
      return s;
    }
    while (s->isRightChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  Node* pred() {
    Node* s = this;
    if (left != nullptr) {
      s = left;
      while (s->right != nullptr) {
        s = s->right;
      }
      return s;
    }
    while (s->isLeftChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  const Node* pred() const {
    const Node* s = this;
    if (left != nullptr) {
      s = left;
      while (s->right != nullptr) {
        s = s->right;
      }
      return s;
    }
    while (s->isLeftChild()) {
      s = s->parent;
    }
    return s->parent;
  }

  template <typename Visit>
  void travPre(Visit visit) {
    visit(*this);
    if (left != nullptr) {
      left->travPre(visit);
    }
    if (right != nullptr) {
      right->travPre(visit);
    }
  }

  template <typename Visit>
  void travPreIterative2(Visit visit) {
    std::stack<Node*> st;
    st.push(this);
    while (!st.empty()) {
      Node* u = st.top();
      st.pop();
      visit(*u);
      if (u->right != nullptr) {
        st.push(u->right);
      }
      if (u->left != nullptr) {
        st.push(u->left);
      }
    }
  }

  template <typename Visit>
  void travInRecursive(Visit visit) {
    if (left != nullptr) {
      left->travInRecursive(visit);
    }
    visit(*this);
    if (right != nullptr) {
      right->travInRecursive(visit);
    }
  }

  template <typename Visit>
  void travInIterative1(Visit visit) {
    std::stack<Node*> st;
    Node* u = this;
    while (u != nullptr || !st.empty()) {
      while (u != nullptr) {
        st.push(u);
        u = u->left;
      }
      u = st.top();
      st.pop();
      visit(*u);
      u = u->right;
    }
  }

  template <typename Visit>
  void travInIterative2(Visit visit) {
    Node* prev = nullptr;
    Node* curr = this;
    while (curr != nullptr) {
      Node* next = nullptr;
      if (prev == curr->parent) {
        if (curr->left != nullptr) {
          next = curr->left;
        } else {
          visit(*curr);
          next = (curr->right != nullptr) ? curr->right : curr->parent;
        }
      } else if (prev == curr->left) {
        visit(*curr);
        next = (curr->right != nullptr) ? curr->right : curr->parent;
      } else {
        next = curr->parent;
      }
      prev = curr;
      curr = next;
    }
  }

  template <typename Visit>
  void travInIterative3(Visit visit) {
    Node* end = rightmost()->succ();
    for (Node* u = leftmost(); u != end; u = u->succ()) {
      visit(*u);
    }
  }

  template <typename Visit>
  void travIn(Visit visit, InorderStrategy strategy = InorderStrategy::Recursive) {
    switch (strategy) {
      case InorderStrategy::Recursive:
        travInRecursive(visit);
        break;
      case InorderStrategy::Iterative1:
        travInIterative1(visit);
        break;
      case InorderStrategy::Iterative2:
        travInIterative2(visit);
        break;
      case InorderStrategy::Iterative3:
        travInIterative3(visit);
        break;
    }
  }

  template <typename Visit>
  void travPost(Visit visit) {
    if (left != nullptr) {
      left->travPost(visit);
    }
    if (right != nullptr) {
      right->travPost(visit);
    }
    visit(*this);
  }

  template <typename Visit>
  void travPostIterative(Visit visit) {
    std::stack<Node*> s1;
    std::stack<Node*> s2;
    s1.push(this);
    while (!s1.empty()) {
      Node* u = s1.top();
      s1.pop();
      s2.push(u);
      if (u->left != nullptr) {
        s1.push(u->left);
      }
      if (u->right != nullptr) {
        s1.push(u->right);
      }
    }
    while (!s2.empty()) {
      visit(*s2.top());
      s2.pop();
    }
  }

  template <typename Visit>
  void travLevel(Visit visit) {
    std::queue<Node*> q;
    q.push(this);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      visit(*u);
      if (u->left != nullptr) {
        q.push(u->left);
      }
      if (u->right != nullptr) {
        q.push(u->right);
      }
    }
  }
};

template <typename T>
inline int stature(const BinNode<T>* node) {
  return node == nullptr ? -1 : node->height;
}

template <typename T>
inline std::vector<T> preorderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPre([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> preorderValuesIterative(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPreIterative2([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> inorderValues(BinNode<T>* root,
                                    InorderStrategy strategy = InorderStrategy::Recursive) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travIn([&out](const BinNode<T>& node) { out.push_back(node.data); }, strategy);
  }
  return out;
}

template <typename T>
inline std::vector<T> postorderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPost([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> postorderValuesIterative(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travPostIterative([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

template <typename T>
inline std::vector<T> levelOrderValues(BinNode<T>* root) {
  std::vector<T> out;
  if (root != nullptr) {
    root->travLevel([&out](const BinNode<T>& node) { out.push_back(node.data); });
  }
  return out;
}

}  // namespace ods
