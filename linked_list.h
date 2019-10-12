class SList;

struct Node {
  int data;
  SList *linked_list = nullptr;
  Node *next = nullptr;

  Node(int data) noexcept { this->data = data; }
};

class SList {
private:
  Node *front = nullptr;
  Node *back = nullptr;
  int size_of_list = 0;

  bool list_empty() const;

public:
  void push_front(Node *node);
  void push_back(Node *node);
  Node *front_node() const;
  Node *back_node() const;
  int size() const noexcept;
};