#include "main.h"

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  s21::queue<int> my_queue_empty_{};
  s21::queue<int> my_queue_full_{2, 5, 7, 10};
  struct new_type {
    char a_char = 'd';
    double a_double = 2.3;
  };
  new_type buff;
};

TEST_F(QueueTest, default_constructor) {
  ASSERT_EQ(my_queue_empty_.size(), 0);
  ASSERT_TRUE(my_queue_empty_.empty());
}

TEST_F(QueueTest, list_constructor) {
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.size(), 4);
  ASSERT_EQ(my_queue_full_.front(), 2); 
}

TEST_F(QueueTest, copy_constructor) {
  s21::queue<int> new_queue(my_queue_full_);
  ASSERT_FALSE(new_queue.empty());
  ASSERT_EQ(new_queue.size(), 4);
  ASSERT_EQ(new_queue.front(), 2); 
  new_queue.pop();
  ASSERT_EQ(new_queue.size(), 3);
  ASSERT_EQ(new_queue.front(), 5); 
}

TEST_F(QueueTest, move_constructor) {
  s21::queue<int> new_queue(std::move(my_queue_full_));
  ASSERT_EQ(new_queue.front(), 2); 
  ASSERT_EQ(new_queue.size(), 4);
  ASSERT_FALSE(new_queue.empty());
  s21::queue<int> new_queue_empty(std::move(my_queue_empty_));
  ASSERT_TRUE(new_queue_empty.empty());
  ASSERT_EQ(new_queue_empty.size(), 0);
}

TEST_F(QueueTest, over_operator_move) {
  s21::queue<int> new_queue_empty;
  new_queue_empty = std::move(my_queue_full_);
  ASSERT_EQ(new_queue_empty.size(), 4);
  ASSERT_FALSE(new_queue_empty.empty());
  ASSERT_EQ(new_queue_empty.front(), 2); 
  s21::queue<int> temp_queue{1, 2, 3, 4, 5};
  new_queue_empty = std::move(temp_queue);
  ASSERT_EQ(new_queue_empty.size(), 5);
  ASSERT_FALSE(new_queue_empty.empty());
  ASSERT_EQ(new_queue_empty.front(), 1);
  new_queue_empty = std::move(my_queue_empty_);
  ASSERT_EQ(new_queue_empty.size(), 0);
  ASSERT_TRUE(new_queue_empty.empty());
}

TEST_F(QueueTest, over_operator_copy) {
  my_queue_full_ = my_queue_full_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 2); 
  ASSERT_EQ(my_queue_full_.size(), 4);
  s21::queue<int> new_queue_full{10, 20, 30};
  new_queue_full = my_queue_full_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 2); 
  ASSERT_EQ(my_queue_full_.size(), 4);
  new_queue_full = my_queue_empty_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 2); 
  ASSERT_EQ(my_queue_full_.size(), 4);

}

TEST_F(QueueTest, empty_function) {
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_TRUE(my_queue_empty_.empty());
}

TEST_F(QueueTest, size_function) {
  ASSERT_EQ(my_queue_full_.size(), 4);
  ASSERT_EQ(my_queue_empty_.size(), 0);
}

TEST_F(QueueTest, push_function) {
  my_queue_full_.push(32);
  my_queue_empty_.push(2);
  ASSERT_EQ(my_queue_full_.front(), 2); 
  ASSERT_EQ(my_queue_empty_.front(), 2);
}

TEST_F(QueueTest, pop_function) {
  ASSERT_THROW(my_queue_empty_.pop(), std::out_of_range); 
  my_queue_full_.pop();
  ASSERT_EQ(my_queue_full_.front(), 5); 
  my_queue_full_.pop();
  ASSERT_EQ(my_queue_full_.front(), 7); 
}

TEST_F(QueueTest, swap_function) {
  new_type buff_1;
  buff_1.a_char = 's';
  buff_1.a_double = 100.12;
  s21::queue<new_type> buff_queue{buff, buff};
  s21::queue<new_type> buff_queue_1{buff_1, buff_1, buff_1};
  buff_queue.swap(buff_queue_1);
  ASSERT_EQ(buff_queue.front().a_double, 100.12);
  ASSERT_EQ(buff_queue.front().a_char, 's');
  ASSERT_EQ(buff_queue_1.front().a_double, 2.3);
  ASSERT_EQ(buff_queue_1.front().a_char, 'd');
}

 
TEST_F(QueueTest, clear_function) {
  my_queue_full_.clear();
  ASSERT_TRUE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.size(), 0);

  ASSERT_THROW(my_queue_full_.front(), std::out_of_range);
  ASSERT_THROW(my_queue_full_.back(), std::out_of_range);
}

TEST_F(QueueTest, front_and_back_functions) {
  ASSERT_EQ(my_queue_full_.front(), 2); 
  ASSERT_EQ(my_queue_full_.back(), 10); 
  my_queue_full_.push(15);
  ASSERT_EQ(my_queue_full_.front(), 2);
  ASSERT_EQ(my_queue_full_.back(), 15); 

  ASSERT_THROW(my_queue_empty_.front(), std::out_of_range);
  ASSERT_THROW(my_queue_empty_.back(), std::out_of_range);
}
