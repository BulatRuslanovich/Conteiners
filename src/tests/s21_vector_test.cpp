#include <vector>

#include "gtest/gtest.h"
#include "test.h"

template <class Type>
bool container_comparison(std::vector<Type> &std_vector,
                          s21::vector<Type> &s21_vector) {
  if (std_vector.size() != s21_vector.size()) return false;
  auto it_std_vector = std_vector.begin();
  auto it_s21_vector = s21_vector.begin();

  while (it_s21_vector != s21_vector.end()) {
    if (*it_s21_vector != *it_std_vector) {
      return false;
    }
    it_s21_vector++;
    it_std_vector++;
  }
  return true;
}

TEST(Vector, default_c) {
  std::vector<std::string> first;
  s21::vector<std::string> second;
  ASSERT_EQ(first.size(), second.size());
}

TEST(Vector, size) {
  s21::vector<std::vector<int>> s21_vector(3);
  std::vector<std::vector<int>> std_vector(3);
  ASSERT_EQ(std_vector.size(), s21_vector.size());
  EXPECT_TRUE(container_comparison(std_vector, s21_vector));
}

TEST(Vector, initializer_list) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  EXPECT_TRUE(container_comparison(std_vector, s21_vector));
}

TEST(Vector, copy) {
  s21::vector<double> s21_first = {3.4, 2.5, 3.4, 2.423455};
  std::vector<double> std_first = {3.4, 2.5, 3.4, 2.423455};
  s21::vector<double> s21_second = s21_first;
  std::vector<double> std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(Vector, move) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double> s21_second = std::move(s21_first);
  std::vector<double> std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(Vector, operator_copy) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double> s21_second;
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_second;
  s21_second = s21_first;
  std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, s21_second));
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, operator_move) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double> s21_second;
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_second;
  s21_second = std::move(s21_first);
  std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, s21_second));
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_front) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_NEAR(s21_first.front(), std_first.front(), 1e-7);
}

TEST(Vector, method_back) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(s21_first.back(), std_first.back());
}

TEST(Vector, method_data) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*s21_first.data(), *std_first.data());
}

TEST(Vector, method_begin) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*s21_first.begin(), *std_first.begin());
}

TEST(Vector, method_end) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*(s21_first.end() - 1), *(std_first.end() - 1));
}

TEST(Vector, method_empty) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double> s21_second;
  std::vector<double> std_second;
  EXPECT_TRUE(s21_first.empty() == std_first.empty());
  EXPECT_TRUE(s21_second.empty() == std_second.empty());
}

TEST(Vector, method_size) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  EXPECT_TRUE(s21_first.size() == std_first.size());
}

TEST(Vector, method_clear) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21_first.clear();
  std_first.clear();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_insert) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  auto it_std_vector = std_first.begin();
  auto it_s21_vector = s21_first.begin();
  it_s21_vector = s21_first.insert(it_s21_vector, 345.345634);
  it_std_vector = std_first.insert(it_std_vector, 345.345634);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  ++it_std_vector;
  ++it_std_vector;
  ++it_s21_vector;
  ++it_s21_vector;
  s21_first.insert(it_s21_vector, 4325.3456);
  std_first.insert(it_std_vector, 4325.3456);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_earse) {
  s21::vector<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  std::vector<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  auto it_std_vector = std_first.begin();
  auto it_s21_vector = s21_first.begin();
  std_first.erase(it_std_vector);
  s21_first.erase(it_s21_vector);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  it_std_vector = std_first.begin();
  it_s21_vector = s21_first.begin();
  ++it_std_vector;
  ++it_std_vector;
  ++it_s21_vector;
  ++it_s21_vector;
  std_first.erase(it_std_vector);
  s21_first.erase(it_s21_vector);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_push_back) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21_first.push_back(534.532);
  s21_first.push_back(0.432456);
  std_first.push_back(534.532);
  std_first.push_back(0.432456);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_pop_back) {
  s21::vector<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  std::vector<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  s21_first.pop_back();
  s21_first.pop_back();
  std_first.pop_back();
  std_first.pop_back();
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_swap) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double> s21_second = {53.543, 234.543, 436.543, 6436.435};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  s21_first.swap(s21_second);
  std_first.swap(std_second);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
  EXPECT_TRUE(container_comparison(std_second, s21_second));
}

TEST(Vector, method_reserve) {
  s21::vector<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  std::vector<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};

  s21_first.reserve(2);
  std_first.reserve(2);
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
  s21_first.reserve(100);
  std_first.reserve(100);
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
}

TEST(Vector, method_shrink_to_fit) {
  s21::vector<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  std::vector<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};

  s21_first.shrink_to_fit();
  std_first.shrink_to_fit();
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
  s21_first.reserve(100);
  std_first.reserve(100);
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
}

TEST(Vector, method_shrink_to_fit_2) {
  s21::vector<double> s21_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};
  std::vector<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                   42545.123, 4563456.7564, 6543.6436};

  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
  s21_first.reserve(100);
  std_first.reserve(100);
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
  s21_first.shrink_to_fit();
  std_first.shrink_to_fit();
  EXPECT_TRUE(std_first.capacity() == s21_first.capacity());
}

TEST(Vector, method_max_size) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::vector<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_EQ(s21_first.max_size(), std_first.max_size());
}

TEST(Vector, method_emplace) {
  s21::vector<double> s21_first = {2, 3, 4, 5};
  std::vector<double> std_first = {2, 3, 4, 5};
  std_first.emplace(std_first.begin(), 1);
  s21_first.insert_many(s21_first.begin(), 1);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, method_emplace_back) {
  s21::vector<double> s21_first = {2, 3, 4, 5};
  std::vector<double> std_first = {2, 3, 4, 5};
  std_first.emplace_back(543.2345);
  s21_first.insert_many_back(543.2345);
  EXPECT_TRUE(container_comparison(std_first, s21_first));
}

TEST(Vector, class_list_iterator) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::iterator it = s21_first.begin();
  s21::vector<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == s21_first.begin());
}

TEST(Vector, class_list_iterator2) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::iterator it = s21_first.begin();
  s21::vector<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == s21_first.begin());
}

TEST(Vector, class_list_iterator_const) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.begin();
  s21::vector<double>::const_iterator second_it = first_it;
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(Vector, class_list_iterator_const2) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.begin();
  s21::vector<double>::const_iterator second_it = std::move(first_it);
  first_it = second_it;
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(Vector, class_list_iterator_const3) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.begin();
  s21::vector<double>::const_iterator second_it = s21_first.end();
  second_it = std::move(first_it);
  EXPECT_TRUE(second_it == s21_first.begin());
}

TEST(Vector, class_list_iterator_const4) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.begin();
  s21::vector<double>::const_iterator second_it = s21_first.begin();
  first_it++;
  second_it++;
  EXPECT_FALSE(first_it != second_it);
}

TEST(Vector, class_list_iterator_const44) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.begin();
  s21::vector<double>::const_iterator second_it = s21_first.begin();
  first_it++;
  second_it++;

  ++first_it;
  ++second_it;
  EXPECT_FALSE(first_it != second_it);
}

TEST(Vector, class_list_iterator_const5) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::const_iterator first_it = s21_first.end();
  s21::vector<double>::const_iterator second_it = s21_first.end();
  first_it--;
  second_it--;
  EXPECT_TRUE(*first_it == *second_it);
}

TEST(Vector, class_list_iterator_const6) {
  s21::vector<double> s21_first = {3.423, 2.5234, 3.4567, 2.423455};
  s21::vector<double>::iterator first_it = s21_first.end();
  s21::vector<double>::iterator second_it = s21_first.end();
  first_it--;
  second_it--;
  --first_it;
  --second_it;
  EXPECT_TRUE(*first_it == *second_it);
}

TEST(Vector, At1) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  std::vector<int> B({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A.at(i), B.at(i));
    A.at(i) = i + 2;
    B.at(i) = i + 2;
    EXPECT_EQ(A.at(i), B.at(i));
  }
  const s21::vector<int> AA({1, 2, 3, 4, 5});
  const std::vector<int> BB({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A.at(i), B.at(i));
  }
  EXPECT_ANY_THROW(A.at(999));
}

TEST(Vector, SquareBrackets) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  std::vector<int> B({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A[i], B[i]);
    A[i] = i + 2;
    B[i] = i + 2;
    EXPECT_EQ(A[i], B[i]);
  }
  const s21::vector<int> AA({1, 2, 3, 4, 5});
  const std::vector<int> BB({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}
