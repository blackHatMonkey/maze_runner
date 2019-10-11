#include <vector>
#include <memory>

#include "linked_list.h"

class DisjointSet {
private:
  std::vector<Node *> all_members;
  std::vector<std::unique_ptr<SList>> linked_lists;

  void remove_list(SList *);
  void moveAllListMembers(SList *, SList *) noexcept;

public:
  DisjointSet(int max);
  bool makeSet(int object);
  int findSet(int object) const;
  bool unionSets(int rep1, int rep2);
  DisjointSet(const DisjointSet &other);
  DisjointSet &operator=(const DisjointSet &other);
  DisjointSet(DisjointSet &&other);
  DisjointSet &operator=(DisjointSet &&other);
};