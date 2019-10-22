#include "disjointset.h"

// TODO:remove this
#include <iostream>

/**
 * @brief Adds node to the front of the list.
 *
 * @param node A new node to add.
 */
void SList::pushFront(Node *node) {
  node->linkedList = this;
  node->next = front;

  if (listEmpty()) {
    back = node;
  }

  front = node;
  sizeOfList++;
}

/**
 * @brief Adds node to the back of the list.
 *
 * @param node A new node to add.
 */
void SList::pushBack(Node *node) {
  node->linkedList = this;
  node->next = nullptr;

  if (listEmpty()) {
    front = node;
    back = node;
  } else {
    back->next = node;
    back = node;
  }

  sizeOfList++;
}

/**
 * @brief Returns whether the list is empty or not.
 *
 * @return true If list is emtpy.
 * @return false If list is not empty.
 */
bool SList::listEmpty() const { return front == nullptr; }

/**
 * @brief Returns the node in the front of the list.
 *
 * @return Node* Node in the front.
 */
Node *SList::frontNode() const { return front; }

/**
 * @brief Returns the node in the back of the list.
 *
 * @return Node* Node in the back.
 */
Node *SList::backNode() const { return back; }

/**
 * @brief Returns the size of the list.
 *
 * @return int Size of the list.
 */
int SList::size() const noexcept { return sizeOfList; }

DisjointSet::DisjointSet(int max) { allMembers.resize(max); }

/**
 * @brief Creates a set with object as the only member
 *
 * @param object value to put in the set
 * @return true if a new set is created
 * @return false if object is already in a set
 */
bool DisjointSet::makeSet(int object) {
  if (!allMembers[object]) {
    auto newList = new SList;
    auto newNode = new Node(object);

    newList->pushBack(newNode);
    allMembers[object] = newNode;

    return true;
  }

  return false;
}

/**
 * @brief Returns the representative of a set with object as a member.
 *
 * @param object member of a set.
 * @return int representative of the set.
 */
int DisjointSet::findSet(int object) const {
  auto node = allMembers[object];
  auto representative = node->linkedList->frontNode();

  return representative->data;
}

/**
 * @brief Combine sets with representatives rep1 and rep2.
 *
 * @param rep1 Representative of first set.
 * @param rep2 Representative of second set.
 * @return true if the union was successful.
 * @return false if the union was unsuccessful.
 */
bool DisjointSet::unionSets(int rep1, int rep2) {
  auto firstRepresentative = findSet(rep1);
  auto secondRepresentative = findSet(rep2);

  if (firstRepresentative != rep1 || secondRepresentative != rep2 ||
      rep1 == rep2) {
    return false;
  }

  if (firstRepresentative == secondRepresentative) {
    return true;
  }

  auto firstList = allMembers[rep1]->linkedList;
  auto firstListSize = firstList->size();

  auto secondList = allMembers[rep2]->linkedList;
  auto secondListSize = secondList->size();

  if (firstListSize > secondListSize) {
    moveAllListMembers(firstList, secondList);
    delete secondList;
  } else {
    moveAllListMembers(secondList, firstList);
    delete firstList;
  }

  return true;
}

/**
 * @brief Move all members of second to first
 *
 * @param first Destination list
 * @param second Source list
 */
void DisjointSet::moveAllListMembers(SList *first, SList *second) noexcept {
  auto currentNode = second->frontNode();
  while (currentNode) {
    auto nextNode = currentNode->next;
    first->pushBack(currentNode);

    currentNode = nextNode;
  }
}

/**
 * @brief Clear all the data in the set.
 *
 */
void DisjointSet::clear() {
  for (auto i = 0u; i < allMembers.size(); i++) {
    if (allMembers[i]) {
      auto list = allMembers[i]->linkedList;

      auto currentNode = list->frontNode();
      while (currentNode) {
        auto nextNode = currentNode->next;
        auto data = currentNode->data;

        delete currentNode;
        allMembers[data] = nullptr;

        currentNode = nextNode;
      }

      delete list;
    }
  }
}

/**
 * @brief Construct a new Disjoint Set:: Disjoint Set object
 *
 * @param other The set to copy from.
 */
DisjointSet::DisjointSet(const DisjointSet &other) {
  if (this != &other) {
    allMembers.resize(other.allMembers.size());

    for (auto i = 0u; i < allMembers.size(); i++) {
      if (!allMembers[i]) {
        auto newList = new SList;

        auto otherList = other.allMembers[i]->linkedList;
        copyAllListMembers(newList, otherList);
      }
    }
  }
}

/**
 * @brief Copy all list members of second to first.
 *
 * @param first Destination list.
 * @param second Source list.
 */
void DisjointSet::copyAllListMembers(SList *first, SList *second) {
  auto currentNode = second->frontNode();
  while (currentNode) {
    auto newNode = new Node(currentNode->data);

    auto data = currentNode->data;
    allMembers[data] = newNode;

    first->pushBack(newNode);

    currentNode = currentNode->next;
  }
}

/**
 * @brief Copies other to a new list.
 *
 * @param other A list to copy from.
 * @return DisjointSet& A new set with other's values copied over.
 */
DisjointSet &DisjointSet::operator=(const DisjointSet &other) {
  if (this != &other) {
    clear();
    allMembers.clear();
    allMembers.resize(other.allMembers.size());

    for (auto i = 0u; i < allMembers.size(); i++) {
      if (!allMembers[i]) {
        auto newList = new SList;

        auto otherList = other.allMembers[i]->linkedList;
        copyAllListMembers(newList, otherList);
      }
    }
  }

  return *this;
}

/**
 * @brief Moves others' data to the current object.
 *
 * @param other Another set.
 */
DisjointSet::DisjointSet(DisjointSet &&other) {
  if (this != &other) {
    allMembers = std::move(other.allMembers);
  }
}

/**
 * @brief Moves others' data to the current object.
 *
 * @param other Another set.
 * @return DisjointSet& A new set with others' data.
 */
DisjointSet &DisjointSet::operator=(DisjointSet &&other) {
  if (this != &other) {
    allMembers = std::move(other.allMembers);
  }

  return *this;
}

/**
 * @brief Destroy the object.
 *
 */
DisjointSet::~DisjointSet() { clear(); }