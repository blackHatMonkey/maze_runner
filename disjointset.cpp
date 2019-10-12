#include "disjointset.h"

DisjointSet::DisjointSet(int max) { all_members.resize(max); }

/**
 * @brief Creates a set with object as the only member
 *
 * @param object value to put in the set
 * @return true if a new set is created
 * @return false if object is already in a set
 */
bool DisjointSet::makeSet(int object) {
  if (!all_members[object]) {
    auto new_list = new SList;
    auto new_node = new Node(object);

    new_list->push_back(new_node);
    all_members[object] = new_node;

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
  auto node = all_members[object];
  auto representative = node->linked_list->front_node();
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
  auto first_representative = findSet(rep1);
  auto second_representative = findSet(rep2);

  if (first_representative != rep1 || second_representative != rep2 ||
      rep1 == rep2) {
    return false;
  }

  if (first_representative == second_representative) {
    return true;
  }

  auto first_list = all_members[rep1]->linked_list;
  auto second_list = all_members[rep2]->linked_list;

  auto first_list_size = first_list->size();
  auto second_list_size = second_list->size();

  if (first_list_size > second_list_size) {
    move_all_list_members(first_list, second_list);
    delete second_list;
  } else {
    move_all_list_members(second_list, first_list);
    delete first_list;
  }

  return true;
}

/**
 * @brief Move all members of second to first
 *
 * @param first Destination list
 * @param second Source list
 */
void DisjointSet::move_all_list_members(SList *first, SList *second) noexcept {
  auto current_node = second->front_node();
  while (current_node) {
    auto next_node = current_node->next;
    first->push_back(current_node);

    current_node = next_node;
  }
}

/**
 * @brief Clear all the data in the set.
 *
 */
void DisjointSet::clear() {
  for (auto i = 0u; i < all_members.size(); i++) {
    if (all_members[i]) {
      auto list = all_members[i]->linked_list;

      auto current_node = list->front_node();
      while (current_node) {
        auto next_node = current_node->next;
        auto data = current_node->data;

        delete current_node;
        all_members[data] = nullptr;

        current_node = next_node;
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
    all_members.resize(other.all_members.size());

    for (auto i = 0u; i < all_members.size(); i++) {
      if (!all_members[i]) {
        auto new_list = new SList;

        auto other_list = other.all_members[i]->linked_list;
        copy_all_list_members(new_list, other_list);
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
void DisjointSet::copy_all_list_members(SList *first, SList *second) {
  auto current_node = second->front_node();
  while (current_node) {
    auto new_node = new Node(current_node->data);
    
    auto data = current_node->data;
    all_members[data] = new_node;
    
    first->push_back(new_node);

    current_node = current_node->next;
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
    all_members.clear();
    all_members.resize(other.all_members.size());

    for (auto i = 0u; i < all_members.size(); i++) {
      if (!all_members[i]) {
        auto new_list = new SList;

        auto other_list = other.all_members[i]->linked_list;
        copy_all_list_members(new_list, other_list);
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
    all_members = std::move(other.all_members);
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
    all_members = std::move(other.all_members);
  }

  return *this;
}

/**
 * @brief Destroy the object.
 * 
 */
DisjointSet::~DisjointSet() { clear(); }