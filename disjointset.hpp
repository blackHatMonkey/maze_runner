#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include <vector>

class SList;

struct Node {
  int data;
  SList *linkedList = nullptr;
  Node *next = nullptr;

  Node(int data) noexcept { this->data = data; }
};

class SList {
private:
  Node *front = nullptr;
  Node *back = nullptr;
  int sizeOfList = 0;

  bool listEmpty() const;

public:
  void pushFront(Node *node);
  void pushBack(Node *node);
  Node *frontNode() const;
  Node *backNode() const;
  int size() const noexcept;
};

class DisjointSet {
private:
  std::vector<Node *> allMembers;

  void clear();
  void moveAllListMembers(SList *, SList *) noexcept;
  void copyAllListMembers(SList *, SList *);

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