#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

#include "linked_list.h"

class DisjointSet {
private:
  std::vector<Node *> all_members;

  void clear();
  void move_all_list_members(SList *, SList *) noexcept;
  void copy_all_list_members(SList *, SList *);

public:
  DisjointSet(int max);
  bool makeSet(int object);
  int findSet(int object) const;
  bool unionSets(int rep1, int rep2);
  DisjointSet(const DisjointSet &other);
  DisjointSet &operator=(const DisjointSet &other);
  DisjointSet(DisjointSet &&other);
  DisjointSet &operator=(DisjointSet &&other);
  ~DisjointSet();
};

#endif