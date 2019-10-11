#include "disjointset.h"

int main(int argc, char const *argv[]) {
  DisjointSet d(4);

  for (int i = 0; i < 3; i++) {
    d.makeSet(i);
  }

  return 0;
}
