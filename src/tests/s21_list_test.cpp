#include <list>
#include "gtest/gtest.h"
#include "test.h"
    
TEST(list, Create) {
  std::list<int> stdList;
  s21::List<int> ourList;

  EXPECT_EQ(stdList.empty(), ourList.empty());
}

TEST(list, size) {
  std::list<int> stdList = {1, 2, 3};
  s21::List<int> ourList = {1, 2 ,3};

  EXPECT_EQ(stdList.size(), ourList.size());
}

TEST(list, push) {
  std::list<int> stdList = {1};
  s21::List<int> ourList = {1};

  stdList.push_front(2);
  ourList.push_front(2);
  stdList.push_back(4);
  ourList.push_back(4);

  EXPECT_EQ(stdList.front(), ourList.front());
  EXPECT_EQ(stdList.back(), ourList.back());
}

TEST(list, pop) {
  std::list<int> stdList = {1, 2, 3};
  s21::List<int> ourList = {1, 2 ,3};

  stdList.pop_front();
  ourList.pop_front();
  stdList.pop_back();
  ourList.pop_back();

  EXPECT_EQ(stdList.front(), ourList.front());
  EXPECT_EQ(stdList.back(), ourList.back());
}

TEST(list, front_back) {
  std::list<int> const stdListConst = {1, 2, 3};
  s21::List<int> const ourListConst = {1, 2 ,3};
  std::list<int> stdList = {1, 2, 3};
  s21::List<int> ourList = {1, 2 ,3};

  EXPECT_EQ(stdListConst.front(), ourListConst.front());
  EXPECT_EQ(stdListConst.back(), ourListConst.back());
  EXPECT_EQ(stdList.front(), ourList.front());
  EXPECT_EQ(stdList.back(), ourList.back());
}

TEST(list, max_size) {
  std::list<int> stdList = {1, 2, 3};
  s21::List<int> ourList = {1, 2 ,3};

  EXPECT_EQ(stdList.max_size(), ourList.max_size() + 1);
}

TEST(list, sort) {
  std::list<int> stdList = {45, 3, 54, 46, 56, 3, 5, 53, 4, 5};
  s21::List<int> ourList = {45, 3, 54, 46, 56, 3, 5, 53, 4, 5};

  stdList.sort();
  ourList.sort();

  auto stdIt = stdList.begin();
  for (auto it = ourList.begin(); it != ourList.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }
}

TEST(list, constructor) {
  std::list<int> stdList = std::list<int>(10);
  std::list<int> ourList = std::list<int>(10);
  EXPECT_EQ(stdList.size(), ourList.size());
}

TEST(list, constructor2) {
  std::list<int> stdList = {1, 3, 4};
  std::list<int> ourList = {1, 3, 4};
  std::list<int> stdListCopy = std::list<int>(stdList);
  std::list<int> ourListCopy = std::list<int>(ourList);
  EXPECT_EQ(stdListCopy.size(), ourListCopy.size());
}

TEST(list, equals) {
  std::list<int> const stdList = {1, 3, 4};
  std::list<int> const ourList = {1, 3, 4};
  std::list<int> stdListCopy = stdList;
  std::list<int> ourListCopy = ourList;

  EXPECT_EQ(stdListCopy.size(), ourListCopy.size());
}

TEST(list, swap) {
  std::list<int> stdList = {1, 3, 4};
  std::list<int> stdListForSwap = {3, 4, 4, 4};
  std::list<int> ourList = {1, 3, 4};
  std::list<int> ourListForSwap = {3, 4, 4, 4};

  stdList.swap(stdListForSwap);
  ourList.swap(ourListForSwap);

  EXPECT_EQ(stdList.size(), ourList.size());
}

TEST(list, merge) {
  std::list<int> stdList = {1, 3, 4};
  std::list<int> stdListForMerge = {3, 4, 4, 4};
  std::list<int> ourList = {1, 3, 4};
  std::list<int> ourListForMerge = {3, 4, 4, 4};

  stdList.merge(stdListForMerge);
  ourList.merge(ourListForMerge);

  auto stdIt = stdList.begin();
  for (auto it = ourList.begin(); it != ourList.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }
}

TEST(list, unique) {
  std::list<int> stdList = {1, 3, 4, 4};
  std::list<int> ourList = {1, 3, 4, 4};

  stdList.unique();
  ourList.unique();

  auto stdIt = stdList.begin();
  for (auto it = ourList.begin(); it != ourList.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }
}

TEST(list, reverse) {
  std::list<int> stdList = {1, 3, 4, 4};
  std::list<int> ourList = {1, 3, 4, 4};

  stdList.reverse();
  ourList.reverse();

  auto stdIt = stdList.begin();
  for (auto it = ourList.begin(); it != ourList.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }
}

TEST(list, emplace) {
  std::list<int> stdList = {1, 3, 4, 4};
  std::list<int> ourList = {1, 3, 4, 4};

  stdList.emplace(stdList.begin(), 24);

  ourList.emplace(ourList.begin(), 24);

  auto stdIt = stdList.begin();
  for (auto it = ourList.begin(); it != ourList.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }
}



