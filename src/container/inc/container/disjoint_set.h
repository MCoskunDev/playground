#include <cassert>
#include <optional>
#include <unordered_map>

namespace mc::container {

// Let's start with non templatized naive implementation.
//
class disjoint_set {
public:
  disjoint_set() = default;

public:
  /**
   * @brief Unites set that contains i with set that contains j.
   */
  std::optional<uint32_t> unite(uint32_t i, uint32_t j) {
    auto i_opt = find(i);
    auto j_opt = find(j);

    // Case 0: If both could not be found, lets create a new set rooted by i.
    if (!i_opt.has_value() && !j_opt.has_value()) {
      m_map[j] = i;
      m_map[i] = -2; // -2 indicates that i is a root with set size of 2.
      return i;
    }

    // Case 1: If there exists a set that includes i, but no set that contains
    // j, add j to the set that includes i.
    if (i_opt.has_value() && !j_opt.has_value()) {
      m_map[j] = *i_opt;
      --m_map[*i_opt]; // Adding one more to the set.
      return *i_opt;
    }

    // Case 2: If there exists a set that includes j, but no set that contains
    // i, add i to the set that includes j.
    if (!i_opt.has_value() && j_opt.has_value()) {
      m_map[i] = *j_opt;
      --m_map[*j_opt]; // Adding one more to the set.
      return *j_opt;
    }

    // Case 3: If they are in the same set, we can fail the call
    if (*i_opt == *j_opt) {
      return std::nullopt;
    }

    // They are in seperate sets. We need to join the two sets.
    int i_neg_size = m_map[*i_opt];
    int j_neg_size = m_map[*j_opt];

    // Case 4: If set that contains i is bigger than set that contains j, join j
    // to i.
    if (i_neg_size < j_neg_size) {
      m_map[*j_opt] = *i_opt;       // Make parent(j) point at i
      m_map[*i_opt] += j_neg_size;  // Increase the size of set(i)
      return *i_opt;
    }

    // Case 5: If set that contains j is bigger than set that contains i, join i
    // to j.
    m_map[*i_opt] = *j_opt;
    m_map[*j_opt] += i_neg_size;
    return *j_opt;
  }

  std::optional<uint32_t> find(uint32_t i) const {
    auto itr = m_map.find(i);

    // If i is unknown, return nullopt.
    if (itr == m_map.end()) {
      return std::nullopt;
    }

    // i is a root
    if (itr->second < 0) {
      return i;
    }

    // Tail recursion.
    return find(itr->second);
  }

  std::optional<uint32_t> find(uint32_t i) {
    auto itr = m_map.find(i);

    // If i is unknown, return nullopt.
    if (itr == m_map.end()) {
      return std::nullopt;
    }

    // i is a root
    if (itr->second < 0) {
      return i;
    }

    // TODO: Consider iterative approach
    auto parent_opt = find(itr->second);
    assert(parent_opt.has_value() && "Invariant");

    // Collapse if necessary
    if (itr->second != *parent_opt) {
      itr->second = *parent_opt;
    }

    return parent_opt;
  }

private:
  std::unordered_map<uint32_t, int> m_map;
};
} // namespace mc::container