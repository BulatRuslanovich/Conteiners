#include "gtest/gtest.h"
#include "test.h"

class ArrayTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  s21::array<int, 0> my_queue_empty_;
  s21::array<int, 3> base_int{1, 2, 3};
  std::array<int, 3> base_same_int = {1, 2, 3};
  s21::array<double, 3> base_double{3124.123, 123.123, 0234.123};
  struct new_type {
    char a_char = 'd';
    double a_double = 2.3;
    int a_int = 11;
  };
  new_type buff;
};

TEST_F(ArrayTest, constructors_base_copy) {
  s21::array<int, 3> temp_1 = base_int;
  s21::array<int, 3> temp_2;
  temp_2 = temp_1;
  s21::array<int, 3> temp_3(temp_2);
  for (size_t i = 0; i != base_int.size(); ++i) {
    ASSERT_EQ(base_int[i], temp_1[i]);
    ASSERT_EQ(temp_1[i], temp_2[i]);
    ASSERT_EQ(temp_2[i], base_same_int[i]);
    ASSERT_EQ(temp_3[i], base_same_int[i]);
  }
  ASSERT_FALSE(base_int.empty());
  ASSERT_TRUE(my_queue_empty_.empty());
}

TEST_F(ArrayTest, move_constructor) {
  s21::array<double, 3> temp_2(std::move(base_double));
  std::array<double, 3> result_1{3124.123, 123.123, 0234.123};
  std::array<double, 3> result_2(std::move(result_1));
  for (size_t i = 0; i != base_double.size(); ++i) {
    ASSERT_EQ(base_double[i], temp_2[i]);
    ASSERT_EQ(result_2[i], temp_2[i]);
  }
}

TEST_F(ArrayTest, operator_copy_move) {
  s21::array<double, 3> temp_2;
  temp_2 = base_double;
  std::array<double, 3> result_1{3124.123, 123.123, 0234.123};
  std::array<double, 3> result_2;
  result_2 = std::move(result_1);
  for (size_t i = 0; i != base_double.size(); ++i) {
    ASSERT_EQ(base_double[i], temp_2[i]);
    ASSERT_EQ(result_2[i], temp_2[i]);
  }
}

TEST_F(ArrayTest, reference_index_access) {
  for (size_t i = 0; i < base_int.size(); ++i) ASSERT_EQ(base_int[i], i + 1);
  ASSERT_ANY_THROW(base_int[4]);
  ASSERT_EQ(base_int[2], *(base_int.end() - 1));
  ASSERT_EQ(base_int[0], *base_int.begin());
  ASSERT_EQ(base_int[0], *base_int.data());
}

TEST_F(ArrayTest, swap) {
  s21::array<int, 3> base_int_s21{1, 2, 3};
  std::array<int, 3> base_int_std{1, 2, 3};
  s21::array<int, 3> result_int_s21{4, 5, 6};
  std::array<int, 3> result_int_std{4, 5, 6};
  base_int_s21.swap(result_int_s21);
  base_int_std.swap(result_int_std);
  for (size_t i = 0; i < base_int_s21.size(); ++i) {
    ASSERT_EQ(base_int_s21[i], base_int_std[i]);
    ASSERT_EQ(result_int_s21[i], result_int_std[i]);
  }
}

TEST_F(ArrayTest, fill) {
  s21::array<int, 11> base_int_s21;
  std::array<int, 11> base_int_std;
  new_type temp;
  base_int_s21.fill(temp.a_int);
  base_int_std.fill(temp.a_int);
  for (size_t i = 0; i < base_int_s21.size(); ++i) {
    ASSERT_EQ(base_int_s21[i], base_int_std[i]);
  }
}

TEST_F(ArrayTest, value) {
  s21::array<int, 5> base_int_s21{1, 2, 3, 4, 5};
  EXPECT_EQ(base_int_s21[0], 1);
  EXPECT_EQ(base_int_s21.front(), 1);
  EXPECT_EQ(base_int_s21.back(), 5);
  EXPECT_EQ(*base_int_s21.data(), base_int_s21[0]);
  EXPECT_EQ(*base_int_s21.begin(), base_int_s21[0]);
  EXPECT_EQ(*(base_int_s21.end() - 1), base_int_s21[4]);
  EXPECT_EQ(base_int_s21.max_size(), 5);
}

TEST_F(ArrayTest, addition) {
  s21::array<int, 5> base_int_s21{1, 2, 3, 4, 5};
  EXPECT_EQ(base_int_s21.front(), 1);
  EXPECT_EQ(base_int_s21.back(), 5);
}

TEST_F(ArrayTest, move_operator) {
  s21::array<int, 5> base_int_s21{1, 2, 3, 4, 5};
  s21::array<int, 5> base_int_s21_1{5, 123, 123, 43, 4};
  s21::array<int, 5> base_int_s21_2{5, 123, 123, 43, 4};
  base_int_s21 = std::move(base_int_s21_1);
  for (int i = 0; i < 5; ++i) EXPECT_EQ(base_int_s21.at(i), base_int_s21_2[i]);
}
