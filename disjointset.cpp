#include "disjointset.h"

DisjointSet::DisjointSet(int max) { all_members.resize(max); }

bool DisjointSet::makeSet(int object) {
  if (!all_members[object]) {
    auto new_list = std::make_unique<SList>();
    auto new_node = new Node(object);
    new_node->next = nullptr;

    new_list->push_front(new_node);
    all_members[object] = new_node;
    linked_lists.push_back(std::move(new_list));

    return true;
  }

  return false;
}

int DisjointSet::findSet(int object) const {
  auto node = all_members[object];
  auto representative = node->linked_list->front_node();
  return representative->data;
}

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
    moveAllListMembers(first_list, second_list);
    second_list->clear();
    remove_list(second_list);
  } else {
    moveAllListMembers(second_list, first_list);
    first_list->clear();
    remove_list(first_list);
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
  auto current_node = second->front_node();
  while (current_node) {
    auto next_node = current_node->next;
    first->push_back(current_node);

    current_node = next_node;
  }
}

void DisjointSet::remove_list(SList *list) {
  auto end = linked_lists.end();

  for (auto it = linked_lists.begin(); it < end; it++) {
    if (it->get() == list) {
      // linked_lists.erase(it);
      it->release();
      return;
    }
  }
}

DisjointSet::DisjointSet(const DisjointSet &other) {
  if (this != &other) {
    all_members.resize(other.all_members.size());

    for (auto &i : other.linked_lists) {
      auto new_list = std::make_unique<SList>();

      auto current = i->front_node();
      while (current) {
        auto new_node = new Node(current->data);

        new_list->push_back(new_node);
        all_members[current->data] = new_node;

        current = current->next;
      }
        linked_lists.push_back(std::move(new_list));
    }
  }
}

DisjointSet &DisjointSet::operator=(const DisjointSet &other) {
  if (this != &other) {
    all_members.clear();
    all_members.resize(other.all_members.size());
    linked_lists.clear();

    for (auto &i : other.linked_lists) {
      auto new_list = std::make_unique<SList>();

      auto current = i->front_node();
      while (current) {
        auto new_node = new Node(current->data);

        new_list->push_front(new_node);
        all_members[current->data] = new_node;

        current = current->next;
      }
        linked_lists.push_back(std::move(new_list));
    }
  }

  return *this;
}

DisjointSet::DisjointSet(DisjointSet &&other) {
  if (this != &other) {
    all_members = std::move(other.all_members);
    linked_lists = std::move(other.linked_lists);
  }
}

DisjointSet &DisjointSet::operator=(DisjointSet &&other) {
  if (this != &other) {
    all_members = std::move(other.all_members);
    linked_lists = std::move(other.linked_lists);
  }

  return *this;
}