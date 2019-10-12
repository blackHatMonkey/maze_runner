#include "linked_list.h"

/**
 * @brief Adds node to the front of the list.
 *
 * @param node A new node to add.
 */
void SList::push_front(Node *node) {
  node->linked_list = this;
  node->next = front;

  if (list_empty()) {
    back = node;
  }

  front = node;
  size_of_list++;
}

/**
 * @brief Adds node to the back of the list.
 *
 * @param node A new node to add.
 */
void SList::push_back(Node *node) {
  node->linked_list = this;
  node->next = nullptr;

  if (list_empty()) {
    front = node;
    back = node;
  } else {
    back->next = node;
    back = node;
  }

  size_of_list++;
}

/**
 * @brief Returns whether the list is empty or not.
 *
 * @return true If list is emtpy.
 * @return false If list is not empty.
 */
bool SList::list_empty() const { return front == nullptr; }

/**
 * @brief Returns the node in the front of the list.
 *
 * @return Node* Node in the front.
 */
Node *SList::front_node() const { return front; }

/**
 * @brief Returns the node in the back of the list.
 *
 * @return Node* Node in the back.
 */
Node *SList::back_node() const { return back; }

/**
 * @brief Returns the size of the list.
 *
 * @return int Size of the list.
 */
int SList::size() const noexcept { return size_of_list; }
