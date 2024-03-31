
#ifndef CONTEINERS_S21_MAP_H

#include <functional>
#include <limits>

namespace s21 {
template <class Key, class Type>
class Map {
public:
  using key_type = Key;
  using mapped_type = Type;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  struct MapValueComparator {
    bool operator()(const_reference value1,
                    const_reference value2) const noexcept {
      return value1.first < value2.first;
    }
  };




};
}




#define CONTEINERS_S21_MAP_H

#endif // CONTEINERS_S21_MAP_H
