// STL
#include <iostream>

// Unit under Test
#include <container/disjoint_set.h>

// TODO: Boost or google test?
int main() {
  mc::container::disjoint_set test_set;

  // Case 0: Create a set {0, 1}
  auto root_opt = test_set.unite(0, 1);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find parent
  root_opt = test_set.find(0);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find child
  root_opt = test_set.find(1);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find not existing
  root_opt = test_set.find(2);
  assert(!root_opt.has_value());

  // Case 1: Join parent
  root_opt = test_set.unite(0, 2);
  assert(root_opt.has_value() && *root_opt == 0);

  root_opt = test_set.find(2);
  assert(root_opt.has_value() && *root_opt == 0);

  // Case 1: Join child
  root_opt = test_set.unite(1, 3);
  assert(root_opt.has_value() && *root_opt == 0);

  root_opt = test_set.find(3);
  assert(root_opt.has_value() && *root_opt == 0);

  // Case 2: Join parent
  root_opt = test_set.unite(4, 0);
  assert(root_opt.has_value() && *root_opt == 0);

  root_opt = test_set.find(4);
  assert(root_opt.has_value() && *root_opt == 0);

  // Case 2: Join child
  root_opt = test_set.unite(5, 3);
  assert(root_opt.has_value() && *root_opt == 0);

  root_opt = test_set.find(5);
  assert(root_opt.has_value() && *root_opt == 0);

  // Case 3: One is parent
  root_opt = test_set.unite(0, 3);
  assert(!root_opt.has_value());

  // Case 3: Both are children
  root_opt = test_set.unite(1, 5);
  assert(!root_opt.has_value());

  // Case 4:
  // Current state S0: {0, 1, 2, 3, 4, 5}
  // Create S6: {6, 7}
  root_opt = test_set.unite(6, 7);
  assert(root_opt.has_value() && *root_opt == 6);

  // Join (dest_parent, src_child)
  root_opt = test_set.unite(0, 7);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find old parent
  root_opt = test_set.find(6);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find child
  root_opt = test_set.find(7);
  assert(root_opt.has_value() && *root_opt == 0);

  // Case 5:
  // Current state S0: {0, 1, 2, 3, 4, 5, 6, 7}
  // Create S9: {9, 8}
  root_opt = test_set.unite(9, 8);
  assert(root_opt.has_value() && *root_opt == 9);

  // Join (src_parent, dest_child)
  root_opt = test_set.unite(9, 6);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find old parent
  root_opt = test_set.find(9);
  assert(root_opt.has_value() && *root_opt == 0);

  // Find child
  root_opt = test_set.find(8);
  assert(root_opt.has_value() && *root_opt == 0);

  // Const find test
  for (uint32_t i = 0; i < 9; i++) {
    mc::container::disjoint_set const &const_set = test_set;
    const_set.find(i);
    assert(root_opt.has_value() && *root_opt == 0);
  }

  return 0;
}