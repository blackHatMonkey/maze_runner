#include "linked_list.h"

void SList::push_front(Node *node) {
  node->linked_list = this;
  node->next = front;

  if (list_empty()) {
    back = node;
  }

  front = node;
  size_of_list++;
}
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

bool SList::list_empty() const { return front == nullptr; }

void SList::print() const {
  auto curr = front;
  while (curr != nullptr) {
    std::cout << curr->data << " ";
    curr = curr->next;
  }
  if (!front) {
    std::cout << "empty list";
  }

  std::cout << "parent list:" << front->linked_list << std::endl
            << "front:" << front->linked_list->front->data << std::endl
            << "back:" << front->linked_list->back->data << std::endl;

  std::cout << std::endl;
}

Node *SList::front_node() const { return front; }

Node *SList::back_node() const { return back; }

// void SList::set_back(Node *node) { back = node; }

// void SList::set_front(Node *node) { front = node; }

int SList::size() const noexcept { return size_of_list; }

void SList::clear(){
  front = nullptr;
  back = nullptr;
}

SList::~SList() {
  auto current = front;
  while (current) {
    auto next = current->next;
    delete current;
    current = next;
  }
}
