#include "gtest/gtest.h"
#include "test.h"
#include <map>


TEST(Map, Constructor1) {
  s21::map<int, double> my_map{
      std::make_pair(42, 12.21), std::make_pair(3, 21.12),
      std::make_pair(33, 66.66), std::make_pair(3, 1.1)};
  std::map<int, double> std_map{
      std::make_pair(42, 12.21), std::make_pair(3, 21.12),
      std::make_pair(33, 66.66), std::make_pair(3, 1.1)};
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (my_iter != my_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }

  ASSERT_TRUE(std_iter == std_map.end());

  s21::map<int, double> my_map2(my_map);
  std::map<int, double> std_map2(std_map);

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
//    std::cout << (*my_iter).first << " " << (*my_iter).second << " orig: " << (*std_iter).first << " " <<  (*std_iter).second << std::endl;
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());

  s21::map<int, double> my_map3 = std::move(my_map2);
  std::map<int, double> std_map3 = std::move(std_map2);

  my_iter = my_map3.begin();
  std_iter = std_map3.begin();

  while (std_iter != std_map3.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(Map, Constructor2) {
  s21::map<int, char> A;
  s21::map<int, int> B;
  const s21::map<int, int> C;
  const s21::map<char, int> D;
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
  EXPECT_EQ(C.size(), 0);
  EXPECT_EQ(D.size(), 0);
}

TEST(Map, Constructor3) {
  s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 30), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 30), std::pair(3, 30)});
  auto j = B.begin();
  for (auto i : A) {
    // std::cout << i.first << i.second << "orig: " << (*j).first << (*j).second
    // << std::endl;
    EXPECT_EQ(i.second, (*j).second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(Map, Constructor4) {
  s21::map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
  it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).first, (*it2).first);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Constructor5) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.size(), m2.size());
  m1.insert({1, 1});
  m2.insert({1, 1});
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Constructor6) {
  s21::map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto m11 = m1;
  auto m22 = m2;
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    EXPECT_EQ((*it1).second, (*it2).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
}

TEST(Map, Constructor7) {
  s21::map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto m11 = std::move(m1);
  auto m22 = std::move(m2);
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    EXPECT_EQ((*it1).second, (*it2).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
}

TEST(Map, Constructor8) {
  s21::map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11;
  std::map<int, int> m22;
  m11 = std::move(m1);
  m22 = std::move(m2);
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it2++, it1++)
    EXPECT_EQ((*it1).second, (*it2).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
}

TEST(Map, Empty1) {
  s21::map<int, std::string> new_map;
  ASSERT_TRUE(new_map.empty() == true);

  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_TRUE(my_map.empty() == false);
}

TEST(Map, Empty2) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  std::pair<int, int> pair = {1, 1};
  m1.insert(pair);
  m2.insert(pair);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Empty3) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Empty4) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Empty5) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Map, Empty6) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Map, Size) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(Map, Clear1) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(Map, Clear2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Map, Clear3) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Map, Clear4) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(Map, Insert1) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert(1, "one");
  std_map.insert({1, "one"});
  my_map.insert(2, "two");
  std_map.insert({2, "two"});
  my_map.insert(22, "twotwo");
  std_map.insert({22, "twotwo"});
  my_map.insert(-22, "-twotwo");
  std_map.insert({-22, "-twotwo"});
  my_map.insert(22, "three");
  std_map.insert({22, "three"});
  my_map.insert(22234, "two3two");
  std_map.insert({22234, "two3two"});
  my_map.insert(12, "onetwo");
  std_map.insert({12, "onetwo"});
  my_map.insert(-12, "-onetwo");
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(Map, Insert2) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert({1, "one"});
  std_map.insert({1, "one"});
  my_map.insert({2, "two"});
  std_map.insert({2, "two"});
  my_map.insert({22, "twotwo"});
  std_map.insert({22, "twotwo"});
  my_map.insert({-22, "-twotwo"});
  std_map.insert({-22, "-twotwo"});
  my_map.insert({22, "three"});
  std_map.insert({22, "three"});
  my_map.insert({22234, "two3two"});
  std_map.insert({22234, "two3two"});
  my_map.insert({12, "onetwo"});
  std_map.insert({12, "onetwo"});
  my_map.insert({-12, "-onetwo"});
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(Map, Insert3) {
  s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  // A.print();
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto ans = A.insert(std::pair(4, 40));
  // A.print();
  auto original_ans = B.insert(std::pair(4, 40));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(4, 40));
  original_ans = B.insert(std::pair(4, 40));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(5, 50));
  original_ans = B.insert(std::pair(5, 50));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(5, 50));
  original_ans = B.insert(std::pair(5, 50));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(6, 60));
  original_ans = B.insert(std::pair(6, 60));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  ans = A.insert(std::pair(6, 60));
  original_ans = B.insert(std::pair(6, 60));
  EXPECT_EQ((*(ans.first)).first, (*(original_ans.first)).first);
  EXPECT_EQ((*(ans.first)).second, (*(original_ans.first)).second);
  EXPECT_EQ(ans.second, original_ans.second);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(Map, Insert4) {
  s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));

  A.insert(6, 60);
  B.insert(std::pair(6, 60));
  A.insert(6, 60);
  B.insert(std::pair(6, 60));
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(Map, Insert5) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Insert6) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Insert7) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(3, 1).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Insert8) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(3, 1).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Insert9) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(Map, Erase1) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(Map, Erase2) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  // my_map.print();
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();
  // my_map.print();
  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(Map, Erase3) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(Map, Erase4) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Swap1) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Swap2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  std::map<int, int> m22 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Swap3) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  s21::map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Swap4) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.swap(my_map2);
  std_map.swap(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());
}

TEST(Map, Merge1) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.merge(my_map2);
  std_map.merge(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(Map, Merge2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  std::map<int, int> m22 = {
      {389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12}};
  m1.merge(m11);
  m2.merge(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Merge3) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m22 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.merge(m11);
  m2.merge(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Merge4) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> m11 = {{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                            {11, 12},  {1, 1},     {2, 2},    {100, 3},
                            {4, 4},    {5, 5}};
  std::map<int, int> m22 = {{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                            {11, 12},  {1, 1},     {2, 2},    {100, 3},
                            {4, 4},    {5, 5}};
  m1.merge(m11);
  m2.merge(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Iterator1) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(Map, Iterator2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.end();
  auto it2 = m2.end();
  it1--, it2--;
  EXPECT_EQ((*it2).second, (*it1).second);
}

TEST(Map, Contains1) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.contains(1), true);
}

TEST(Map, Contains2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.contains(0), false);
}

TEST(Map, Contains3) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_EQ(my_map.contains(42), true);
  ASSERT_EQ(my_map.contains(42342), false);
  ASSERT_EQ(my_map.contains(33), true);
  ASSERT_EQ(my_map.contains(0), false);
}

TEST(Map, Contains4) {
  s21::map<int, int> a{{3, 7}, {8, 3}, {1, 9}};
  EXPECT_EQ(a.contains(8), true);
  EXPECT_EQ(a.contains(5), false);
}

TEST(Map, At1) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  for (size_t i = 1; i < m1.size(); i++) EXPECT_EQ(m1.at(i), m2.at(i));
}

TEST(Map, At2) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_ANY_THROW(m1.at(0));
  EXPECT_ANY_THROW(m2.at(0));
}

TEST(Map, At3) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.at(100), m2.at(100));
}

TEST(Map, At4) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map.at(33);
  auto std_ans = std_map.at(33);
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map.at(3);
  std_ans = std_map.at(3);
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(Map, At5) {
  s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  EXPECT_EQ(A.at(1), B.at(1));
  EXPECT_EQ(A.at(2), B.at(2));
  EXPECT_EQ(A.at(3), B.at(3));
  A.at(3) = 200;
  B.at(3) = 200;
  EXPECT_EQ(A.at(3), B.at(3));

  const s21::map<int, int> AA(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  const std::map<int, int> BB(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  EXPECT_EQ(AA.at(1), BB.at(1));
  EXPECT_EQ(AA.at(2), BB.at(2));
  EXPECT_EQ(AA.at(3), BB.at(3));
}

TEST(Map, OperatorSquareBrackets1) {
  s21::map<int, int> A({std::pair(1, 10)});
  std::map<int, int> B({std::pair(1, 10)});
  EXPECT_EQ(A[1], B[1]);
  A[2] = 20;
  B[2] = 20;
  B[4] = 999;
  A[4] = 999;
  EXPECT_EQ(A[4], B[4]);
  EXPECT_EQ(A[2], B[2]);
}

TEST(Map, OperatorSquareBrackets2) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map[33];
  auto std_ans = std_map[33];
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map[3];
  std_ans = std_map[3];
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(Map, OperatorSquareBrackets3) {
  s21::map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1[100], m2[100]);
  EXPECT_NO_THROW(m1[-2] = 3);
  EXPECT_NO_THROW(m2[-2] = 3);
  EXPECT_NO_THROW(m1.at(-2) = 5);
  EXPECT_NO_THROW(m2.at(-2) = 5);
  EXPECT_EQ(m1.at(-2), m2.at(-2));
}

TEST(Map, InsertOrAssign1) {
  s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  A.insert_or_assign(3, 60);
  B.insert_or_assign(3, 60);
  A.insert_or_assign(4, 60);
  B.insert_or_assign(4, 60);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(Map, InsertOrAssign2) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert_or_assign(1, "one");
  std_map.insert_or_assign(1, "one");
  my_map.insert_or_assign(2, "two");
  std_map.insert_or_assign(2, "two");
  my_map.insert_or_assign(22, "twotwo");
  std_map.insert_or_assign(22, "twotwo");
  my_map.insert_or_assign(-22, "-twotwo");
  std_map.insert_or_assign(-22, "-twotwo");
  my_map.insert_or_assign(22, "three");
  std_map.insert_or_assign(22, "three");
  my_map.insert_or_assign(22234, "two3two");
  std_map.insert_or_assign(22234, "two3two");
  my_map.insert_or_assign(12, "onetwo");
  std_map.insert_or_assign(12, "onetwo");
  my_map.insert_or_assign(-12, "-onetwo");
  std_map.insert_or_assign(-12, "-onetwo");

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(Map, Iterator9000) {
  const s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  const std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto it = A.end();
  auto it_std = B.end();
  it--, it_std--;
  EXPECT_EQ((*it).first, (*it_std).first);
}

TEST(Map, Begin9000) {
  const s21::map<int, int> A(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  const std::map<int, int> B(
      {std::pair(1, 10), std::pair(2, 20), std::pair(2, 20), std::pair(3, 30)});
  auto it = A.begin();
  auto it_std = B.begin();
  it++, it_std++;
  EXPECT_EQ((*it).first, (*it_std).first);
}


