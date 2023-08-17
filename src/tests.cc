#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>

#include "s21_containers.h"

TEST(MapTest, DefaultConstructor) {
  s21::Map<int, char> map;
  EXPECT_TRUE(map.Empty());
  EXPECT_EQ(map.Size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 3);

  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_TRUE(map.Contains(3));
}

TEST(MapTest, CopyConstructor) {
  std::pair<int, char> a = {1, 'a'};
  std::pair<int, char> b = {2, 'b'};
  std::pair<int, char> c = {3, 'c'};
  s21::Map<int, char> map1 = {a, b, c};
  s21::Map<int, char> map2(map1);

  EXPECT_TRUE(map2.Contains(1));
  EXPECT_TRUE(map2.Contains(2));
  EXPECT_TRUE(map2.Contains(3));
  std::pair<int, char> d = {4, 'd'};
  map1.Insert(d);
  EXPECT_FALSE(map2.Contains(4));
}

TEST(MapTest, MoveConstructor) {
  std::pair<int, char> a = {1, 'a'};
  std::pair<int, char> b = {2, 'b'};
  std::pair<int, char> c = {3, 'c'};
  s21::Map<int, char> map1 = {a, b, c};
  s21::Map<int, char> map2(std::move(map1));

  EXPECT_TRUE(map2.Contains(1));
  EXPECT_TRUE(map2.Contains(2));
  EXPECT_TRUE(map2.Contains(3));

  EXPECT_FALSE(map2.Empty());
  EXPECT_EQ(map2.Size(), 3);

  EXPECT_TRUE(map1.Empty());
  EXPECT_EQ(map1.Size(), 0);
}

TEST(MapTest, MoveAssignmentOperator) {
  std::pair<int, float> a = {1, 1.11};
  std::pair<int, float> b = {2, 2.22};
  std::pair<int, float> c = {3, 3.33};
  s21::Map<int, float> map1 = {a, b, c};
  s21::Map<int, float> map2;

  map2 = std::move(map1);

  EXPECT_TRUE(map2.Contains(1));
  EXPECT_TRUE(map2.Contains(2));
  EXPECT_TRUE(map2.Contains(3));

  EXPECT_TRUE(map1.Empty());
  EXPECT_EQ(map1.Size(), 0);
}

TEST(MapTest, AssignmentOperatorCopy) {
  s21::Set<int> source_set;
  source_set.Insert(1);
  source_set.Insert(2);
  source_set.Insert(3);

  s21::Set<int> target_set;
  target_set = source_set;

  EXPECT_EQ(target_set.Size(), source_set.Size());

  auto source_it = source_set.Begin();
  auto target_it = target_set.Begin();
  while (source_it != source_set.End() && target_it != target_set.End()) {
    EXPECT_EQ(source_it.GetKey(), target_it.GetKey());
    ++source_it;
    ++target_it;
  }
}

TEST(MapTest, Begin) {
  std::pair<int, char> a = {'a', 1};
  std::pair<int, char> b = {'b', 2};
  std::pair<int, char> c = {'c', 3};
  s21::Map<char, int> map1 = {a, b, c};
  auto it = map1.Begin();

  EXPECT_EQ(it.GetKey(), 'a');
  EXPECT_EQ(it.GetVal(), 1);
  ++it;
  EXPECT_EQ(it.GetKey(), 'b');
  EXPECT_EQ(it.GetVal(), 2);
  --it;
  EXPECT_EQ(it.GetKey(), 'a');
  EXPECT_EQ(it.GetVal(), 1);
  ++it;
  EXPECT_EQ(it.GetKey(), 'b');
  EXPECT_EQ(it.GetVal(), 2);
  ++it;
  EXPECT_EQ(it.GetKey(), 'c');
  EXPECT_EQ(it.GetVal(), 3);
}

TEST(MapTest, End) {
  std::pair<int, char> a = {'a', 1};
  std::pair<int, char> b = {'b', 2};
  std::pair<int, char> c = {'c', 3};
  s21::Map<char, int> map1 = {a, b, c};
  auto it = map1.End();

  --it;
  EXPECT_EQ(it.GetKey(), 'c');
  EXPECT_EQ(it.GetVal(), 3);
  --it;
  EXPECT_EQ(it.GetKey(), 'b');
  EXPECT_EQ(it.GetVal(), 2);
  ++it;
  EXPECT_EQ(it.GetKey(), 'c');
  EXPECT_EQ(it.GetVal(), 3);
  --it;
  EXPECT_EQ(it.GetKey(), 'b');
  EXPECT_EQ(it.GetVal(), 2);
  --it;
  EXPECT_EQ(it.GetKey(), 'a');
  EXPECT_EQ(it.GetVal(), 1);
}

TEST(MapTest, CBegin) {
  s21::Map<int, int> constSet;

  constSet.Insert(1, 11);
  constSet.Insert(2, 22);
  constSet.Insert(3, 33);

  auto const_iter = constSet.CBegin();
  EXPECT_EQ(const_iter.GetKey(), 1);
  EXPECT_EQ(const_iter.GetVal(), 11);

  auto const_iter_2 = const_iter;
  ++const_iter_2;
  EXPECT_EQ(const_iter_2.GetKey(), 2);
  EXPECT_EQ(const_iter_2.GetVal(), 22);

  auto const_iter_3 = const_iter_2;
  --const_iter_3;
  EXPECT_EQ(const_iter_3.GetKey(), 1);
  EXPECT_EQ(const_iter_3.GetVal(), 11);
}

TEST(MapTest, CEnd) {
  s21::Map<int, int> constSet;

  constSet.Insert(1, 11);
  constSet.Insert(2, 22);
  constSet.Insert(3, 33);

  auto const_iter = constSet.CEnd();

  --const_iter;

  EXPECT_EQ(const_iter.GetKey(), 3);
  EXPECT_EQ(const_iter.GetVal(), 33);

  auto const_iter_2 = const_iter;
  --const_iter_2;
  EXPECT_EQ(const_iter_2.GetKey(), 2);
  EXPECT_EQ(const_iter_2.GetVal(), 22);

  auto const_iter_3 = const_iter_2;
  --const_iter_3;
  EXPECT_EQ(const_iter_3.GetKey(), 1);
  EXPECT_EQ(const_iter_3.GetVal(), 11);
}

TEST(MapTest, Empty) {
  s21::Map<int, float> map1;
  EXPECT_TRUE(map1.Empty());
  std::pair<int, char> a = {55, 1.1};
  map1.Insert(a);
  EXPECT_FALSE(map1.Empty());
  auto it = map1.Find(5);
  map1.Erase(it);
  EXPECT_TRUE(map1.Empty());
}

TEST(MapTest, Insert) {
  s21::Map<int, int> map;
  std::pair<int, int> a = {1, 111};
  auto result = map.Insert(a);

  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), 1);
  EXPECT_EQ(result.first.GetVal(), 111);
  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 1);

  result = map.Insert(a);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first.GetKey(), 1);
  EXPECT_EQ(result.first.GetVal(), 111);
  EXPECT_EQ(map.Size(), 1);

  std::pair<int, int> b = {5, 555};

  result = map.Insert(b);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), 5);
  EXPECT_EQ(result.first.GetVal(), 555);
  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 2);

  std::pair<int, int> c = {-66, -12};

  result = map.Insert(c);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), -66);
  EXPECT_EQ(result.first.GetVal(), -12);
  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 3);
}

TEST(MapTest, Insert2) {
  s21::Map<int, std::string> map;
  s21::Map<int, std::string> m;
  auto result1 = map.Insert(1, "one");
  auto result2 = map.Insert(2, "two");
  auto result3 = map.Insert(2, "four");

  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_FALSE(result3.second);

  EXPECT_EQ(result1.first.GetKey(), 1);
  EXPECT_EQ(result1.first.GetVal(), "one");
  EXPECT_EQ(result2.first.GetKey(), 2);
  EXPECT_EQ(result2.first.GetVal(), "two");

  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.At(1), "one");
  EXPECT_EQ(map.At(2), "two");
}

TEST(MapTest, InsertOrAssign) {
  s21::Map<int, std::string> map;
  auto result1 = map.insert_or_assign(1, "one");
  EXPECT_EQ(result1.first.GetKey(), 1);
  EXPECT_EQ(result1.first.GetVal(), "one");

  auto result2 = map.insert_or_assign(2, "two");
  EXPECT_EQ(result2.first.GetKey(), 2);
  EXPECT_EQ(result2.first.GetVal(), "two");

  auto result3 = map.insert_or_assign(1, "one");

  auto result4 = map.insert_or_assign(1, "new one");
  EXPECT_EQ(result3.first.GetKey(), 1);
  EXPECT_EQ(result3.first.GetVal(), "new one");

  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_FALSE(result3.second);
  EXPECT_TRUE(result4.second);

  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.At(1), "new one");
  EXPECT_EQ(map.At(2), "two");
}

TEST(MapTest, Erase) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map.Begin();
  ++it;
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));

  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());

  it = map.Begin();
  map.Erase(it);

  EXPECT_FALSE(map.Contains(1));

  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_FALSE(map.Empty());

  it = map.End();
  --it;
  map.Erase(it);

  EXPECT_FALSE(map.Contains(3));
  EXPECT_EQ(map.Size(), 0);
  EXPECT_TRUE(map.Empty());
}

TEST(MapTest, Swap1) {
  s21::Map<int, int> map1 = {{1, 11}, {2, 22}, {3, 33}};
  s21::Map<int, int> map2 = {{4, 44}, {5, 55}, {6, 66}, {7, 77}};
  map1.Swap(map2);
  EXPECT_FALSE(map1.Contains(1));
  EXPECT_FALSE(map1.Contains(2));
  EXPECT_FALSE(map1.Contains(3));

  EXPECT_TRUE(map1.Contains(4));
  EXPECT_TRUE(map1.Contains(5));
  EXPECT_TRUE(map1.Contains(6));
  EXPECT_TRUE(map1.Contains(7));
  EXPECT_EQ(4, map1.Size());

  EXPECT_TRUE(map2.Contains(1));
  EXPECT_TRUE(map2.Contains(2));
  EXPECT_TRUE(map2.Contains(3));
  EXPECT_EQ(3, map2.Size());

  EXPECT_FALSE(map2.Contains(4));
  EXPECT_FALSE(map2.Contains(5));
  EXPECT_FALSE(map2.Contains(6));
  EXPECT_FALSE(map2.Contains(7));
}

TEST(MapTest, Swap2) {
  s21::Map<int, int> map1 = {{1, 11}, {2, 22}, {3, 33}};

  map1.Swap(map1);
  EXPECT_TRUE(map1.Contains(1));
  EXPECT_TRUE(map1.Contains(2));
  EXPECT_TRUE(map1.Contains(3));
}

TEST(MapTest, Merge1) {
  s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'd'}};
  s21::Map<int, char> map2 = {{3, 'c'}, {4, 'k'}, {5, 'm'}};
  map1.Merge(map2);
  EXPECT_TRUE(map1.Contains(1));
  EXPECT_EQ(map1.At(1), 'a');
  EXPECT_TRUE(map1.Contains(2));
  EXPECT_EQ(map1.At(2), 'b');
  EXPECT_TRUE(map1.Contains(3));
  EXPECT_EQ(map1.At(3), 'd');

  EXPECT_TRUE(map1.Contains(4));
  EXPECT_EQ(map1.At(4), 'k');
  EXPECT_TRUE(map1.Contains(5));
  EXPECT_EQ(map1.At(5), 'm');

  EXPECT_EQ(map1.Size(), 5);
  EXPECT_FALSE(map2.Empty());
  EXPECT_EQ(map2.Size(), 1);
}

TEST(MapTest, Merge2) {
  s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> map2 = {{4, 'k'}, {5, 'm'}, {6, 'm'}, {7, 'l'}};
  map1.Merge(map2);
  EXPECT_TRUE(map1.Contains(1));
  EXPECT_EQ(map1.At(1), 'a');
  EXPECT_TRUE(map1.Contains(2));
  EXPECT_EQ(map1.At(2), 'b');
  EXPECT_TRUE(map1.Contains(3));
  EXPECT_EQ(map1.At(3), 'c');
  EXPECT_TRUE(map1.Contains(4));
  EXPECT_EQ(map1.At(4), 'k');
  EXPECT_TRUE(map1.Contains(5));
  EXPECT_EQ(map1.At(5), 'm');
  EXPECT_TRUE(map1.Contains(6));
  EXPECT_EQ(map1.At(6), 'm');
  EXPECT_TRUE(map1.Contains(7));
  EXPECT_EQ(map1.At(7), 'l');
  EXPECT_EQ(map1.Size(), 7);
  EXPECT_TRUE(map2.Empty());
  EXPECT_EQ(map2.Size(), 0);
}

TEST(MapTest, Merge3) {
  s21::Map<int, char> map1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map1.Merge(map1);
  EXPECT_TRUE(map1.Contains(1));
  EXPECT_EQ(map1.At(1), 'a');
  EXPECT_TRUE(map1.Contains(2));
  EXPECT_EQ(map1.At(2), 'b');
  EXPECT_TRUE(map1.Contains(3));
  EXPECT_EQ(map1.At(3), 'c');
  EXPECT_EQ(map1.Size(), 3);
  EXPECT_FALSE(map1.Empty());
}

TEST(MapTest, Find) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

  auto it = map.Find(2);
  EXPECT_EQ(it.GetKey(), 2);
  EXPECT_EQ(it.GetVal(), 'b');

  it = map.Find(4);
  EXPECT_EQ(it, map.End());
}

TEST(MapTest, Contains) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_TRUE(map.Contains(1));
  EXPECT_EQ(map.At(1), 'a');
  EXPECT_TRUE(map.Contains(2));
  EXPECT_EQ(map.At(2), 'b');
  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map.At(3), 'c');
  EXPECT_FALSE(map.Contains(4));
}

TEST(MapTest, Clear) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  map.Clear();
  EXPECT_TRUE(map.Empty());
  EXPECT_EQ(map.Size(), 0);
}

TEST(MapTest, AccessOrInsertSpecifiedElement) {
  s21::Map<int, char> map;
  map[1] = 'a';
  EXPECT_EQ(map[1], 'a');
  map[1] = 'h';
  EXPECT_EQ(map[1], 'h');
  map[4] = 'o';
  EXPECT_TRUE(map.Contains(4));
  EXPECT_EQ(map[4], 'o');
  EXPECT_EQ(map.Size(), 2);
}

TEST(MapTest, EraseNonEmpty) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map.Begin();
  ++it;
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));
  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFirstElement) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map.Begin();
  map.Erase(it);
  EXPECT_FALSE(map.Contains(1));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_TRUE(map.Contains(3));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseLastElement) {
  s21::Map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = map.End();
  --it;
  map.Erase(it);
  EXPECT_FALSE(map.Contains(3));
  EXPECT_TRUE(map.Contains(1));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseEmpty) {
  s21::Map<int, char> map;
  auto it = map.Begin();
  map.Erase(it);
  EXPECT_TRUE(map.Empty());
}

TEST(MapTest, EraseFixupCase1) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto it = map.Find(4);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(4));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupCase2) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto it = map.Find(2);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupCase3LeftChild) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto it = map.Find(1);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(1));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupCase3RightChild) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  auto it = map.Find(5);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(5));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupCase4LeftChild) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'},
                             {4, 'd'}, {5, 'e'}, {6, 'f'}};
  auto it = map.Find(1);
  map.Erase(it);
  it = map.Find(2);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(1));
  EXPECT_FALSE(map.Contains(2));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupCase4RightChild) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'},
                             {4, 'd'}, {5, 'e'}, {6, 'f'}};
  auto it = map.Find(5);
  map.Erase(it);
  it = map.Find(6);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(5));
  EXPECT_FALSE(map.Contains(6));
  EXPECT_EQ(map.Size(), 4);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupRootCase1) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}};
  auto it = map.Find(2);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupRootCase2) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}, {3, 'c'}};
  auto it = map.Find(3);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(3));
  EXPECT_EQ(map.Size(), 2);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupRootCase3) {
  s21::Map<int, char> map = {{2, 'a'}, {1, 'b'}};
  auto it = map.Find(2);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupRootCase4) {
  s21::Map<int, char> map = {{2, 'a'}, {3, 'b'}};
  auto it = map.Find(2);
  map.Erase(it);
  EXPECT_FALSE(map.Contains(2));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_FALSE(map.Empty());
}

TEST(MapTest, EraseFixupTest1) {
  s21::Map<int, int> map;
  map.Insert(std::make_pair(10, 10));
  map.Insert(std::make_pair(5, 5));
  map.Insert(std::make_pair(15, 15));
  map.Insert(std::make_pair(2, 2));
  map.Insert(std::make_pair(7, 7));
  map.Insert(std::make_pair(13, 13));
  map.Insert(std::make_pair(20, 20));

  auto it = map.Find(5);
  map.Erase(it);

  EXPECT_FALSE(map.Contains(5));
  EXPECT_TRUE(map.Contains(2));
  EXPECT_TRUE(map.Contains(7));
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(13));
  EXPECT_TRUE(map.Contains(15));
  EXPECT_TRUE(map.Contains(20));
  EXPECT_EQ(map.Size(), 6);
}

TEST(MapTest, EraseFixupTest2) {
  s21::Map<int, int> map;
  map.Insert(std::make_pair(10, 10));
  map.Insert(std::make_pair(5, 5));
  map.Insert(std::make_pair(15, 15));
  map.Insert(std::make_pair(2, 2));
  map.Insert(std::make_pair(7, 7));
  map.Insert(std::make_pair(13, 13));
  map.Insert(std::make_pair(20, 20));

  auto it = map.Find(2);
  map.Erase(it);

  EXPECT_FALSE(map.Contains(2));
  EXPECT_TRUE(map.Contains(5));
  EXPECT_TRUE(map.Contains(7));
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(13));
  EXPECT_TRUE(map.Contains(15));
  EXPECT_TRUE(map.Contains(20));
  EXPECT_EQ(map.Size(), 6);
}

TEST(MapTest, EraseFixupTest3) {
  s21::Map<int, int> map;
  map.Insert(std::make_pair(10, 10));
  map.Insert(std::make_pair(5, 5));
  map.Insert(std::make_pair(15, 15));
  map.Insert(std::make_pair(13, 13));
  map.Insert(std::make_pair(20, 20));
  map.Insert(std::make_pair(25, 25));

  auto it = map.Find(5);
  map.Erase(it);

  EXPECT_FALSE(map.Contains(5));
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(13));
  EXPECT_TRUE(map.Contains(15));
  EXPECT_TRUE(map.Contains(20));
  EXPECT_TRUE(map.Contains(25));
  EXPECT_EQ(map.Size(), 5);
}

TEST(MapTest, EraseFixupTest4) {
  s21::Map<int, int> map;
  map.Insert(std::make_pair(10, 10));
  map.Insert(std::make_pair(5, 5));
  map.Insert(std::make_pair(15, 15));
  map.Insert(std::make_pair(13, 13));
  map.Insert(std::make_pair(20, 20));

  auto it = map.Find(13);
  map.Erase(it);

  EXPECT_FALSE(map.Contains(13));
  EXPECT_TRUE(map.Contains(5));
  EXPECT_TRUE(map.Contains(10));
  EXPECT_TRUE(map.Contains(15));
  EXPECT_TRUE(map.Contains(20));
  EXPECT_EQ(map.Size(), 4);
}

TEST(MapTest, MaxSize) {
  s21::Map<int, int> map;

  EXPECT_EQ(map.MaxSize(), 230584300921369395);
}

/////////////////////////////////////////////////////

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> set;
  EXPECT_TRUE(set.Empty());
  EXPECT_EQ(set.Size(), 0);
}

TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> set = {1, 2, 3, 4, 5};
  EXPECT_FALSE(set.Empty());
  EXPECT_EQ(set.Size(), 5);

  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_TRUE(set.Contains(3));
  EXPECT_TRUE(set.Contains(4));
  EXPECT_TRUE(set.Contains(5));
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2(set1);

  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_TRUE(set2.Contains(3));

  set1.Insert(4);
  EXPECT_FALSE(set2.Contains(4));
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2(std::move(set1));

  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_TRUE(set2.Contains(3));

  EXPECT_FALSE(set2.Empty());
  EXPECT_EQ(set2.Size(), 3);

  EXPECT_TRUE(set1.Empty());
  EXPECT_EQ(set1.Size(), 0);
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2;
  set2 = std::move(set1);

  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_TRUE(set2.Contains(3));

  EXPECT_TRUE(set1.Empty());
  EXPECT_EQ(set1.Size(), 0);
}

TEST(SetTest, AssignmentOperatorCopy) {
  s21::Set<int> source_set;
  source_set.Insert(1);
  source_set.Insert(2);
  source_set.Insert(3);

  s21::Set<int> target_set;
  target_set = source_set;
  EXPECT_EQ(target_set.Size(), source_set.Size());

  auto source_it = source_set.Begin();
  auto target_it = target_set.Begin();
  while (source_it != source_set.End() && target_it != target_set.End()) {
    EXPECT_EQ(source_it.GetKey(), target_it.GetKey());
    ++source_it;
    ++target_it;
  }
}

TEST(SetTest, Begin) {
  s21::Set<int> set1 = {1, 2, 3};
  auto it = set1.Begin();
  EXPECT_EQ(it.GetKey(), 1);
  ++it;
  EXPECT_EQ(it.GetKey(), 2);
  --it;
  EXPECT_EQ(it.GetKey(), 1);
  ++it;
  EXPECT_EQ(it.GetKey(), 2);
  ++it;
  EXPECT_EQ(it.GetKey(), 3);
}

TEST(SetTest, end_) {
  s21::Set<int> set1 = {1, 2, 3};
  auto it = set1.End();
  --it;
  EXPECT_EQ(it.GetKey(), 3);
  --it;
  EXPECT_EQ(it.GetKey(), 2);
  ++it;
  EXPECT_EQ(it.GetKey(), 3);
  --it;
  EXPECT_EQ(it.GetKey(), 2);
  --it;
  EXPECT_EQ(it.GetKey(), 1);
}

TEST(SetTest, Empty) {
  s21::Set<int> set1;
  EXPECT_TRUE(set1.Empty());
  set1.Insert(5);
  EXPECT_FALSE(set1.Empty());
  auto it = set1.Find(5);
  set1.Erase(it);
  EXPECT_TRUE(set1.Empty());
}

TEST(SetTest, Insert) {
  s21::Set<int> set;

  auto result = set.Insert(1);

  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), 1);
  EXPECT_FALSE(set.Empty());
  EXPECT_EQ(set.Size(), 1);

  result = set.Insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first.GetKey(), 1);
  EXPECT_EQ(set.Size(), 1);

  result = set.Insert(55);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), 55);
  EXPECT_FALSE(set.Empty());
  EXPECT_EQ(set.Size(), 2);

  result = set.Insert(-3);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first.GetKey(), -3);
  EXPECT_FALSE(set.Empty());
  EXPECT_EQ(set.Size(), 3);
}

TEST(SetTest, Insert2) {
  s21::Set<int> set;

  set.Insert(1);
  EXPECT_EQ(set.GetRoot()->key_, 1);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);
  EXPECT_TRUE(set.GetRoot()->right_->end_);
  EXPECT_TRUE(set.GetRoot()->left_->end_);

  set.Insert(2);
  EXPECT_EQ(set.GetRoot()->right_->key_, 2);
  EXPECT_EQ(set.GetRoot()->right_->color_, RED);
  EXPECT_TRUE(set.GetRoot()->left_->end_);
  EXPECT_TRUE(set.GetRoot()->right_->right_->end_);
  EXPECT_TRUE(set.GetRoot()->right_->left_->end_);

  set.Insert(3);
  EXPECT_EQ(set.GetRoot()->key_, 2);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->right_->key_, 3);
  EXPECT_EQ(set.GetRoot()->right_->color_, RED);
  EXPECT_EQ(set.GetRoot()->left_->key_, 1);
  EXPECT_EQ(set.GetRoot()->left_->color_, RED);

  EXPECT_TRUE(set.GetRoot()->right_->right_->end_);
  EXPECT_TRUE(set.GetRoot()->right_->left_->end_);

  EXPECT_TRUE(set.GetRoot()->left_->right_->end_);
  EXPECT_TRUE(set.GetRoot()->left_->left_->end_);

  set.Insert(4);
  EXPECT_EQ(set.GetRoot()->key_, 2);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->right_->key_, 3);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->left_->key_, 1);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->key_, 4);
  EXPECT_EQ(set.GetRoot()->right_->right_->color_, RED);

  set.Insert(5);
  EXPECT_EQ(set.GetRoot()->key_, 2);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->right_->key_, 4);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->left_->key_, 1);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->key_, 5);
  EXPECT_EQ(set.GetRoot()->right_->right_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 3);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, RED);

  set.Insert(6);
  EXPECT_EQ(set.GetRoot()->key_, 2);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);
  EXPECT_EQ(set.GetRoot()->right_->key_, 4);
  EXPECT_EQ(set.GetRoot()->right_->color_, RED);
  EXPECT_EQ(set.GetRoot()->left_->key_, 1);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->key_, 5);
  EXPECT_EQ(set.GetRoot()->right_->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 3);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->right_->key_, 6);
  EXPECT_EQ(set.GetRoot()->right_->right_->right_->color_, RED);
}

TEST(SetTest, InsertLeftLeft) {
  s21::Set<int> set = {10, 5, 2};
  set.Insert(1);

  EXPECT_EQ(set.GetRoot()->key_, 5);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 2);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 10);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->left_->key_, 1);
  EXPECT_EQ(set.GetRoot()->left_->left_->color_, RED);
}

TEST(SetTest, InsertLeftRight) {
  s21::Set<int> set = {10, 5, 8};
  set.Insert(7);

  EXPECT_EQ(set.GetRoot()->key_, 8);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 5);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 10);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->right_->key_, 7);
  EXPECT_EQ(set.GetRoot()->left_->right_->color_, RED);
}

TEST(SetTest, InsertRightRight) {
  s21::Set<int> set = {5, 10, 15, 20, 25, 30};
  set.Insert(35);

  EXPECT_EQ(set.GetRoot()->key_, 10);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 5);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 20);
  EXPECT_EQ(set.GetRoot()->right_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 15);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->key_, 30);
  EXPECT_EQ(set.GetRoot()->right_->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->right_->left_->key_, 25);
  EXPECT_EQ(set.GetRoot()->right_->right_->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->right_->right_->key_, 35);
  EXPECT_EQ(set.GetRoot()->right_->right_->right_->color_, RED);
}

TEST(SetTest, RotateRight1) {
  s21::Set<int> set = {10, 5, 15, 3};
  set.Insert(2);

  EXPECT_EQ(set.GetRoot()->key_, 10);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 3);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->left_->key_, 2);
  EXPECT_EQ(set.GetRoot()->left_->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->left_->right_->key_, 5);
  EXPECT_EQ(set.GetRoot()->left_->right_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->key_, 15);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);
}

TEST(SetTest, RotateRight2) {
  s21::Set<int> set;
  set.Insert(10);
  set.Insert(5);
  set.Insert(15);
  set.Insert(8);
  set.Insert(7);

  EXPECT_EQ(set.GetRoot()->key_, 10);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 7);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->left_->key_, 5);
  EXPECT_EQ(set.GetRoot()->left_->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->left_->right_->key_, 8);
  EXPECT_EQ(set.GetRoot()->left_->right_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->key_, 15);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);
}

TEST(SetTest, InsertRightLeft) {
  s21::Set<int> set = {10, 5, 8};
  set.Insert(9);

  EXPECT_EQ(set.GetRoot()->key_, 8);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 5);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 10);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 9);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, RED);
}

TEST(SetTest, Erase) {
  s21::Set<int> set = {1, 2, 3, 4};
  auto it = set.Begin();
  ++it;
  set.Erase(it);
  EXPECT_FALSE(set.Contains(2));

  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(3));
  EXPECT_TRUE(set.Contains(4));
  EXPECT_EQ(set.Size(), 3);
  EXPECT_FALSE(set.Empty());

  it = set.Begin();
  set.Erase(it);

  EXPECT_FALSE(set.Contains(1));

  EXPECT_TRUE(set.Contains(3));
  EXPECT_TRUE(set.Contains(4));
  EXPECT_EQ(set.Size(), 2);
  EXPECT_FALSE(set.Empty());

  it = set.End();
  --it;
  set.Erase(it);

  EXPECT_FALSE(set.Contains(4));
  EXPECT_TRUE(set.Contains(3));
  EXPECT_EQ(set.Size(), 1);
  EXPECT_FALSE(set.Empty());

  it = set.Begin();
  set.Erase(it);

  EXPECT_FALSE(set.Contains(3));
  EXPECT_EQ(set.Size(), 0);
  EXPECT_TRUE(set.Empty());
}

TEST(SetTest, Swap1) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {4, 5, 6, 7};
  set1.Swap(set2);
  EXPECT_FALSE(set1.Contains(1));
  EXPECT_FALSE(set1.Contains(2));
  EXPECT_FALSE(set1.Contains(3));

  EXPECT_TRUE(set1.Contains(4));
  EXPECT_TRUE(set1.Contains(5));
  EXPECT_TRUE(set1.Contains(6));
  EXPECT_TRUE(set1.Contains(7));
  EXPECT_EQ(4, set1.Size());

  EXPECT_TRUE(set2.Contains(1));
  EXPECT_TRUE(set2.Contains(2));
  EXPECT_TRUE(set2.Contains(3));
  EXPECT_EQ(3, set2.Size());

  EXPECT_FALSE(set2.Contains(4));
  EXPECT_FALSE(set2.Contains(5));
  EXPECT_FALSE(set2.Contains(6));
  EXPECT_FALSE(set2.Contains(7));
}

TEST(SetTest, Swap2) {
  s21::Set<int> set1 = {1, 2, 3};

  set1.Swap(set1);
  EXPECT_TRUE(set1.Contains(1));
  EXPECT_TRUE(set1.Contains(2));
  EXPECT_TRUE(set1.Contains(3));
}

TEST(SetTest, Merge1) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {3, 4, 5};
  set1.Merge(set2);
  EXPECT_TRUE(set1.Contains(1));
  EXPECT_TRUE(set1.Contains(2));
  EXPECT_TRUE(set1.Contains(3));
  EXPECT_TRUE(set1.Contains(4));
  EXPECT_TRUE(set1.Contains(5));
  EXPECT_EQ(set1.Size(), 5);
  EXPECT_FALSE(set2.Empty());
  EXPECT_EQ(set2.Size(), 1);
}

TEST(SetTest, Merge2) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = {4, 5, 6, 7};
  set1.Merge(set2);
  EXPECT_TRUE(set1.Contains(1));
  EXPECT_TRUE(set1.Contains(2));
  EXPECT_TRUE(set1.Contains(3));
  EXPECT_TRUE(set1.Contains(4));
  EXPECT_TRUE(set1.Contains(5));
  EXPECT_TRUE(set1.Contains(6));
  EXPECT_TRUE(set1.Contains(7));
  EXPECT_EQ(set1.Size(), 7);
  EXPECT_TRUE(set2.Empty());
  EXPECT_EQ(set2.Size(), 0);
}

TEST(SetTest, Merge3) {
  s21::Set<int> set1 = {1, 2, 3};
  set1.Merge(set1);
  EXPECT_TRUE(set1.Contains(1));
  EXPECT_TRUE(set1.Contains(2));
  EXPECT_TRUE(set1.Contains(3));
  EXPECT_EQ(set1.Size(), 3);
}

TEST(SetTest, Find) {
  s21::Set<int> set = {1, 2, 3};

  auto it = set.Find(2);
  EXPECT_EQ(it.GetKey(), 2);

  it = set.Find(4);
  EXPECT_EQ(it, set.End());
}

TEST(SetTest, Contains) {
  s21::Set<int> set = {1, 2, 3};
  EXPECT_TRUE(set.Contains(1));
  EXPECT_TRUE(set.Contains(2));
  EXPECT_TRUE(set.Contains(3));
  EXPECT_FALSE(set.Contains(4));
}

TEST(SetTest, Clear) {
  s21::Set<int> set = {1, 2, 3};
  set.Clear();
  EXPECT_TRUE(set.Empty());
  EXPECT_EQ(set.Size(), 0);
}

TEST(SetTest, EraseTwoRightDum1) {
  s21::Set<int> set = {50, 111, 25, 14, 43, 12};
  auto it = set.Find(111);
  set.Erase(it);
  EXPECT_EQ(set.GetRoot()->key_, 25);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 14);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->left_->key_, 12);
  EXPECT_EQ(set.GetRoot()->left_->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->key_, 50);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 43);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, RED);
}

TEST(SetTest, EraseTwoRightDum2) {
  s21::Set<int> set = {55, 25, 123, 12, 35};
  auto it = set.Find(123);
  set.Erase(it);

  EXPECT_EQ(set.GetRoot()->key_, 25);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 12);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 55);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 35);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, RED);
}

TEST(SetTest, EraseTwoRightDum3) {
  s21::Set<int> set;
  set.Insert(50);
  set.Insert(25);
  set.Insert(75);
  set.Insert(10);
  set.Insert(40);
  set.Insert(60);
  set.Insert(90);
  set.Insert(11);
  auto it = set.Find(40);
  set.Erase(it);

  EXPECT_EQ(set.GetRoot()->key_, 50);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 11);
  EXPECT_EQ(set.GetRoot()->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->key_, 75);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->left_->key_, 60);
  EXPECT_EQ(set.GetRoot()->right_->left_->color_, RED);

  EXPECT_EQ(set.GetRoot()->right_->right_->key_, 90);
  EXPECT_EQ(set.GetRoot()->right_->right_->color_, RED);

  EXPECT_EQ(set.GetRoot()->left_->left_->key_, 10);
  EXPECT_EQ(set.GetRoot()->left_->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->right_->key_, 25);
  EXPECT_EQ(set.GetRoot()->left_->right_->color_, BLACK);
}

TEST(SetTest, EraseTwoRightDum4) {
  s21::Set<int> set;
  set.Insert(50);
  set.Insert(25);
  set.Insert(75);
  set.Insert(60);

  auto it = set.Find(25);
  set.Erase(it);

  EXPECT_EQ(set.GetRoot()->key_, 60);
  EXPECT_EQ(set.GetRoot()->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->left_->key_, 50);
  EXPECT_EQ(set.GetRoot()->left_->color_, BLACK);

  EXPECT_EQ(set.GetRoot()->right_->key_, 75);
  EXPECT_EQ(set.GetRoot()->right_->color_, BLACK);
}

TEST(SetTest, MaxSize) {
  s21::Set<int> set;

  EXPECT_EQ(set.MaxSize(), 230584300921369395);
}

/////////////////////////////

TEST(IterTest, IteratorDecrement) {
  s21::Container<int, int> tree;
  tree.Insert(std::make_pair(50, 500));
  tree.Insert(std::make_pair(30, 300));
  tree.Insert(std::make_pair(70, 700));
  tree.Insert(std::make_pair(20, 200));
  tree.Insert(std::make_pair(40, 400));

  auto it50 = tree.Find(50);
  auto it30 = tree.Find(30);
  auto it70 = tree.Find(70);
  auto it20 = tree.Find(20);
  auto it40 = tree.Find(40);

  --it50;
  --it30;
  --it70;
  --it20;
  --it40;

  EXPECT_EQ(it50.GetKey(), 40);
  EXPECT_EQ(it30.GetKey(), 20);
  EXPECT_EQ(it70.GetKey(), 50);
  EXPECT_EQ(it20.GetKey(), 20);
  EXPECT_EQ(it40.GetKey(), 30);
}

TEST(IterTest, IteratorIncrement) {
  s21::Container<int, int> tree;

  auto it = tree.Find(123);
  ++it;
  EXPECT_EQ(it.GetKey(), 0);
}

TEST(ConstIterTest, DefaultConstructor) {
  s21::ConstIter<int, int> const_iter;
  EXPECT_EQ(const_iter.getCurrent(), nullptr);
}

TEST(ConstIterTest, ConstructorWithNode) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(1, 10));
  s21::ConstIter<int, int> const_iter(node.GetRoot());
  EXPECT_EQ(const_iter.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter.GetKey(), 1);
  EXPECT_EQ(const_iter.GetVal(), 10);
}

TEST(ConstIterTest, CopyConstructor) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(2, 20));
  s21::ConstIter<int, int> const_iter1(node.GetRoot());
  s21::ConstIter<int, int> const_iter2(const_iter1);
  EXPECT_EQ(const_iter2.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter2.GetKey(), 2);
  EXPECT_EQ(const_iter2.GetVal(), 20);
}

TEST(ConstIterTest, MoveConstructor) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(3, 30));
  s21::ConstIter<int, int> const_iter1(node.GetRoot());
  s21::ConstIter<int, int> const_iter2(std::move(const_iter1));
  EXPECT_EQ(const_iter2.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter2.GetKey(), 3);
  EXPECT_EQ(const_iter2.GetVal(), 30);
  EXPECT_EQ(const_iter1.getCurrent(), nullptr);
}

TEST(ConstIterTest, CopyAssignmentOperator) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(4, 40));
  s21::ConstIter<int, int> const_iter1(node.GetRoot());
  s21::ConstIter<int, int> const_iter2;
  const_iter2 = const_iter1;
  EXPECT_EQ(const_iter2.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter2.GetKey(), 4);
  EXPECT_EQ(const_iter2.GetVal(), 40);
}

TEST(ConstIterTest, MoveAssignmentOperator) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(5, 50));
  s21::ConstIter<int, int> const_iter1(node.GetRoot());
  s21::ConstIter<int, int> const_iter2;
  const_iter2 = std::move(const_iter1);
  EXPECT_EQ(const_iter2.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter2.GetKey(), 5);
  EXPECT_EQ(const_iter2.GetVal(), 50);
  EXPECT_EQ(const_iter1.getCurrent(), nullptr);
}

TEST(ConstIterTest, PrefixIncrementOperator) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(6, 60));
  node.Insert(std::make_pair(7, 70));
  s21::ConstIter<int, int> const_iter(node.GetRoot());
  ++const_iter;
  EXPECT_EQ(const_iter.getCurrent(), node.GetRoot()->right_);
}

TEST(ConstIterTest, PrefixDecrementOperator) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(7, 70));
  node.Insert(std::make_pair(8, 80));

  s21::ConstIter<int, int> const_iter(node.GetRoot()->right_);
  --const_iter;
  EXPECT_EQ(const_iter.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter.GetKey(), 7);
  EXPECT_EQ(const_iter.GetVal(), 70);
}

TEST(ConstIterTest, AssignmentOperatorWithNode) {
  s21::Map<int, int> node;
  node.Insert(std::make_pair(9, 90));
  s21::ConstIter<int, int> const_iter;
  const_iter = node.GetRoot();
  EXPECT_EQ(const_iter.getCurrent(), node.GetRoot());
  EXPECT_EQ(const_iter.GetKey(), 9);
  EXPECT_EQ(const_iter.GetVal(), 90);
}

TEST(ConstIterTest, InequalityOperator) {
  s21::Map<int, int> node1;
  node1.Insert(std::make_pair(10, 100));
  s21::Map<int, int> node2;
  node2.Insert(std::make_pair(11, 110));

  s21::ConstIter<int, int> const_iter1(node1.GetRoot());
  s21::ConstIter<int, int> const_iter2(node2.GetRoot());
  EXPECT_NE(const_iter1, const_iter2);
}

//////////////////////////////////

TEST(NodeTest, DefaultConstructor) {
  s21::Node<int, int> node;
  EXPECT_EQ(node.key_, 0);
  EXPECT_EQ(node.val_, 0);
  EXPECT_EQ(node.left_, nullptr);
  EXPECT_EQ(node.right_, nullptr);
  EXPECT_EQ(node.parent_, nullptr);
  EXPECT_EQ(node.color_, RED);
  EXPECT_FALSE(node.end_);
}

TEST(NodeTest, CopyConstructor) {
  s21::Node<int, int> original;
  original.key_ = 42;
  original.val_ = 100;
  original.color_ = BLACK;
  original.end_ = true;

  s21::Node<int, int> copied(original);
  EXPECT_EQ(copied.key_, 42);
  EXPECT_EQ(copied.val_, 100);
  EXPECT_EQ(copied.left_, nullptr);
  EXPECT_EQ(copied.right_, nullptr);
  EXPECT_EQ(copied.parent_, nullptr);
  EXPECT_EQ(copied.color_, BLACK);
  EXPECT_TRUE(copied.end_);
}

TEST(NodeTest, MoveConstructor) {
  s21::Node<int, int> original;
  original.key_ = 42;
  original.val_ = 100;
  original.color_ = BLACK;
  original.end_ = true;

  s21::Node<int, int> moved(std::move(original));
  EXPECT_EQ(moved.key_, 42);
  EXPECT_EQ(moved.val_, 100);
  EXPECT_EQ(moved.left_, nullptr);
  EXPECT_EQ(moved.right_, nullptr);
  EXPECT_EQ(moved.parent_, nullptr);
  EXPECT_EQ(moved.color_, BLACK);
  EXPECT_TRUE(moved.end_);

  EXPECT_EQ(original.key_, 0);
  EXPECT_EQ(original.val_, 0);
  EXPECT_EQ(original.left_, nullptr);
  EXPECT_EQ(original.right_, nullptr);
  EXPECT_EQ(original.parent_, nullptr);
  EXPECT_EQ(original.color_, RED);
  EXPECT_FALSE(original.end_);
}

TEST(NodeTest, CopyAssignmentOperator) {
  s21::Node<int, int> original;
  original.key_ = 42;
  original.val_ = 100;
  original.color_ = BLACK;
  original.end_ = true;

  s21::Node<int, int> copied;
  copied = original;
  EXPECT_EQ(copied.key_, 42);
  EXPECT_EQ(copied.val_, 100);
  EXPECT_EQ(copied.left_, nullptr);
  EXPECT_EQ(copied.right_, nullptr);
  EXPECT_EQ(copied.parent_, nullptr);
  EXPECT_EQ(copied.color_, BLACK);
  EXPECT_TRUE(copied.end_);
}

TEST(NodeTest, MoveAssignmentOperator) {
  s21::Node<int, int> original;
  original.key_ = 42;
  original.val_ = 100;
  original.color_ = BLACK;
  original.end_ = true;

  s21::Node<int, int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.key_, 42);
  EXPECT_EQ(moved.val_, 100);
  EXPECT_EQ(moved.left_, nullptr);
  EXPECT_EQ(moved.right_, nullptr);
  EXPECT_EQ(moved.parent_, nullptr);
  EXPECT_EQ(moved.color_, BLACK);
  EXPECT_TRUE(moved.end_);

  EXPECT_EQ(original.key_, 0);
  EXPECT_EQ(original.val_, 0);
  EXPECT_EQ(original.left_, nullptr);
  EXPECT_EQ(original.right_, nullptr);
  EXPECT_EQ(original.parent_, nullptr);
  EXPECT_EQ(original.color_, RED);
  EXPECT_FALSE(original.end_);
}

///////////////////////////////

TEST(StackTest, Constructor_default) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
}

TEST(StackTest, Constructor_initializer_list_1) {
  s21::Stack<int> s21_stack{1, 2, 4};
  EXPECT_EQ((int)s21_stack.Size(), 3);
  EXPECT_EQ(s21_stack.Top(), 4);
}

TEST(StackTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::Stack<int> s21_stack{b};
  std::stack<int> std_stack{b};

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
}

TEST(StackTest, Constructor_copy_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_copy{s21_stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_copy{std_stack};
  EXPECT_EQ(s21_stack_copy.Size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.Top(), std_stack_copy.top());
}

TEST(StackTest, Constructor_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_move{s21_stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(s21_stack_move.Size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.Top(), std_stack_move.top());
}

TEST(StackTest, Opertator_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Opertator_move_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Opertator_move_3) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Top_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};

  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Top_2_throw) {
  std::initializer_list<int> il1;

  s21::Stack<int> s21_stack{il1};

  EXPECT_THROW(s21_stack.Top(), std::out_of_range);
}

TEST(StackTest, empty_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
}

TEST(StackTest, empty_2) {
  std::initializer_list<int> il1;

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
}

TEST(StackTest, size_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
}

TEST(StackTest, size_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
}

TEST(StackTest, Push_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.Push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Push_2) {
  std::initializer_list<int> il1;

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.Push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, Pop_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.Pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(StackTest, swap_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.Top(), std_stack_swap.top());
}

TEST(StackTest, swap_2) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.Top(), std_stack_swap.top());
}

TEST(StackTest, swap_3) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2;

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
}

TEST(StackTest, swap_4) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
}

TEST(StackTest, swap_5) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2;

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
}

TEST(StackTest, swap_6) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::Stack<int> s21_stack{il1};
  s21::Stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.Swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.Size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.Top(), std_stack_swap.top());
}

TEST(StackTest, Move) {
  s21::Stack<int> s1{1, 2, 3, 4, 5, 6};
  s21::Stack<int> s2{6, 5, 4, 3, 2, 1};
  s2 = (std::move(s1));

  EXPECT_EQ(s2.Top(), 6);
  s2.Pop();
  EXPECT_EQ(s2.Top(), 5);
  s2.Pop();
  EXPECT_EQ(s2.Top(), 4);
  s2.Pop();
  EXPECT_EQ((int)s1.Size(), 0);

  s21::Stack<int> s3{1, 2, 3, 4, 5, 6};
  s21::Stack<int> s4(std::move(s1));
}

///////////////////////////

// Test default constructor
TEST(StackTest, Constructor_Default) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_TRUE(s21_stack.Empty());
}

// Test constructor with initializer List
TEST(StackTest, Constructor_InitializerList) {
  s21::Stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

// Test copy constructor
TEST(StackTest, Constructor_Copy) {
  s21::Stack<int> s21_stack{1, 2, 3};
  s21::Stack<int> s21_stack_copy(s21_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_copy(std_stack);
  EXPECT_EQ(s21_stack_copy.Size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.Top(), std_stack_copy.top());
}

// Test move constructor
TEST(StackTest, Constructor_Move) {
  s21::Stack<int> s21_stack{1, 2, 3};
  s21::Stack<int> s21_stack_move(std::move(s21_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_move(std::move(std_stack));
  EXPECT_EQ(s21_stack_move.Size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.Top(), std_stack_move.top());
}

TEST(StackTest, Destructor) {
  s21::Stack<int>* s21_stack = new s21::Stack<int>{1, 2, 3};
  delete s21_stack;

  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  // If there are no crashes or errors, the test is considered passed
}

// Test move assignment operator
TEST(StackTest, AssignmentOperator_Move) {
  s21::Stack<int> s21_stack{1, 2, 3};
  s21::Stack<int> s21_stack_move;
  s21_stack_move = std::move(s21_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_move;
  std_stack_move = std::move(std_stack);
  EXPECT_EQ(s21_stack_move.Size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.Top(), std_stack_move.top());
}

// Test top() method
TEST(StackTest, Top) {
  s21::Stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

// Test empty() method
TEST(StackTest, empty) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
  s21_stack.Push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
}

// Test size() method
TEST(StackTest, size) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
  s21_stack.Push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.Size(), std_stack.size());
}

// Test push() and pop() methods
TEST(StackTest, PushPop) {
  s21::Stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.Push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
  s21_stack.Push(2);
  std_stack.push(2);
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
  s21_stack.Pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

// Test swap() method
TEST(StackTest, swap) {
  s21::Stack<int> s21_stack1{1, 2, 3};
  s21::Stack<int> s21_stack2{4, 5};
  std::stack<int> std_stack1;
  std::stack<int> std_stack2;
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);
  std_stack2.push(4);
  std_stack2.push(5);
  s21_stack1.Swap(s21_stack2);
  std_stack1.swap(std_stack2);
  EXPECT_EQ(s21_stack1.Size(), std_stack1.size());
  EXPECT_EQ(s21_stack1.Top(), std_stack1.top());
  EXPECT_EQ(s21_stack2.Size(), std_stack2.size());
  EXPECT_EQ(s21_stack2.Top(), std_stack2.top());
}

TEST(QueueTest, CopyConstructor) {
  s21::Queue<int> queue1;
  queue1.Push(10);
  queue1.Push(20);
  queue1.Push(30);

  s21::Queue<int> queue2(queue1);

  EXPECT_EQ(queue2.Front(), 10);
  EXPECT_EQ(queue2.Size(), queue1.Size());
}

TEST(QueueTest, MoveConstructor) {
  s21::Queue<int> queue1;
  queue1.Push(10);
  queue1.Push(20);
  queue1.Push(30);

  s21::Queue<int> queue2(std::move(queue1));

  EXPECT_EQ(queue2.Front(), 10);
  EXPECT_TRUE(queue1.Empty());
}
// Тестирование методов empty() и size() на пустой очереди
TEST(QueueTest, emptyAndsizeOnemptyQueue) {
  s21::Queue<int> queue;
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<std::size_t>(0));
}

// Тестирование методов push() и size() на непустой очереди
TEST(QueueTest, PushAndsizeOnNonemptyQueue) {
  s21::Queue<int> queue;
  queue.Push(10);
  queue.Push(20);
  queue.Push(30);

  EXPECT_FALSE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<std::size_t>(3));
}

// Тестирование методов front() и pop()
TEST(QueueTest, FrontAndPop) {
  s21::Queue<int> queue;
  queue.Push(10);
  queue.Push(20);
  queue.Push(30);

  EXPECT_EQ(queue.Front(), 10);
  queue.Pop();
  EXPECT_EQ(queue.Front(), 20);
  queue.Pop();
  EXPECT_EQ(queue.Front(), 30);
  queue.Pop();

  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<std::size_t>(0));
}

TEST(QueueTest, swap) {
  std::initializer_list<int> q1 = {4, 5, 6, 7};
  std::initializer_list<int> q2 = {1, 2, 3};

  s21::Queue<int> s21_queue{q1};
  s21::Queue<int> s21_queue_swap{q2};
  std::queue<int> std_queue{q1};
  std::queue<int> std_queue_swap{q2};
  s21_queue.Swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);

  EXPECT_EQ(s21_queue.Size(), std_queue.size());
  EXPECT_EQ(s21_queue.Front(), std_queue.front());
  // EXPECT_EQ(s21_queue.back(), std_queue.back());

  EXPECT_EQ(s21_queue_swap.Size(), std_queue_swap.size());
  EXPECT_EQ(s21_queue_swap.Front(), std_queue_swap.front());
  // EXPECT_EQ(s21_queue_swap.back(), std_queue_swap.back());
}
TEST(ListTest, default_constructor1) {
  s21::List<int> s21list;
  std::list<int> stdlist;
  ASSERT_EQ(s21list.Empty(), stdlist.empty());
  ASSERT_EQ(s21list.Size(), stdlist.size());
}

TEST(ListTest, size_constructor) {
  s21::List<int> s21list(5);
  std::list<int> stdlist(5);
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, init_constructor1) {
  s21::List<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, init_char_constructor) {
  s21::List<char> s21list{'a', 'b', 'c'};
  std::list<char> stdlist{'a', 'b', 'c'};
  s21::List<char>::iterator s21it = s21list.Begin();
  std::list<char>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, init_string_constructor) {
  s21::List<std::string> s21list{"just", "string", "constructor"};
  std::list<std::string> stdlist{"just", "string", "constructor"};
  s21::List<std::string>::iterator s21it = s21list.Begin();
  std::list<std::string>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, move_constructor_test) {
  s21::List<int> s21list{1, 2, 0, 123};
  std::list<int> stdlist{1, 2, 0, 123};
  s21::List<int> s21list2(std::move(s21list));
  std::list<int> stdlist2(std::move(stdlist));
  s21::List<int>::iterator s21it = s21list2.Begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.Size(), stdlist2.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, List_constructor) {
  s21::List<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::List<int> s21list2 = std::move(s21list);
  std::list<int> stdlist2 = std::move(stdlist);
  s21::List<int>::iterator s21it = s21list2.Begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.Size(), stdlist2.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, front_back) {
  s21::List<int> s21list;
  std::list<int> stdlist;
  s21list.PushFront(77);
  s21list.PushBack(66);
  s21list.PushBack(11111);
  stdlist.push_front(77);
  stdlist.push_back(66);
  stdlist.push_back(11111);
  ASSERT_EQ(s21list.Front(), stdlist.front());
  ASSERT_EQ(s21list.Back(), stdlist.back());
}

TEST(ListTest, empty_clear) {
  s21::List<int> s21list;
  std::list<int> stdlist;
  s21list.PushFront(77);
  s21list.PushBack(66);
  s21list.PushBack(11111);
  stdlist.push_front(77);
  stdlist.push_back(66);
  stdlist.push_back(11111);
  s21list.Clear();
  stdlist.clear();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  ASSERT_EQ(s21list.Empty(), stdlist.empty());
}

TEST(ListTest, push) {
  s21::List<int> s21list;
  std::list<int> stdlist;
  s21list.PushFront(77);
  s21list.PushBack(66);
  s21list.PushBack(11111);
  stdlist.push_front(77);
  stdlist.push_back(66);
  stdlist.push_back(11111);
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, pop) {
  s21::List<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21list.PopBack();
  stdlist.pop_back();
  ASSERT_EQ(s21list.Front(), stdlist.front());
  ASSERT_EQ(s21list.Back(), stdlist.back());
  s21list.PopFront();
  stdlist.pop_front();
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  s21list.Clear();
  stdlist.clear();
  ASSERT_EQ(s21list.Empty(), stdlist.empty());
}

TEST(ListTest, insert) {
  s21::List<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.Insert(s21it, 77);
  stdlist.insert(stdit, 77);
  s21it = s21list.End();
  stdit = stdlist.end();
  s21list.Insert(s21it, 66);
  stdlist.insert(stdit, 66);
  ASSERT_EQ(s21list.Front(), stdlist.front());
  s21list.Insert(s21it, 1111);
  stdlist.insert(stdit, 1111);
  s21it = s21list.Begin();
  stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, erase) {
  s21::List<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.Erase(s21it);
  stdlist.erase(stdit);
  ASSERT_EQ(s21list.Front(), stdlist.front());
  s21it = s21list.Begin();
  stdit = stdlist.begin();
  ++s21it;
  ++stdit;
  s21list.Erase(s21it);
  stdlist.erase(stdit);
  s21it = s21list.Begin();
  stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, swap) {
  s21::List<int> s21list{77, 55, 0, 87, 1111};
  s21::List<int> s21list2{5, 3};
  std::list<int> stdlist{77, 55, 0, 87, 1111};
  std::list<int> stdlist2{5, 3};
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.Swap(s21list2);
  stdlist.swap(stdlist2);
  ASSERT_EQ(s21list.Size(), stdlist.size());
  ASSERT_EQ(s21list2.Size(), stdlist2.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, splice) {
  s21::List<int> s21list{77, 55, 0, 87, 1111};
  s21::List<int> s21list2{5, 3};
  std::list<int> stdlist{77, 55, 0, 87, 1111};
  std::list<int> stdlist2{5, 3};
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.Splice(s21it, s21list2);
  stdlist.splice(stdit, stdlist2);
  ASSERT_EQ(s21list.Size(), stdlist.size());
  ASSERT_EQ(s21list2.Size(), stdlist2.size());
  s21it = s21list.Begin();
  stdit = stdlist.begin();
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  ASSERT_EQ(s21list2.Empty(), stdlist2.empty());
}
// 2 пустых списка
TEST(ListTest, empty_lists) {
  s21::List<int> list1;
  s21::List<int> list2;

  s21::List<int>::iterator it = list1.Begin();
  list1.Splice(it, list2);

  ASSERT_TRUE(list1.Empty());
  ASSERT_TRUE(list2.Empty());
}

TEST(ListTest, reverse) {
  s21::List<int> s21list{77, 55, 0, 87, 1111};
  std::list<int> stdlist{77, 55, 0, 87, 1111};
  s21list.Reverse();
  stdlist.reverse();
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(ListTest, EmptyList) {
  s21::List<int> list;

  list.Reverse();

  ASSERT_TRUE(list.Empty());
}

TEST(ListTest, unique) {
  s21::List<int> s21list{1, 1, 1, 1, 222, 222, 2, 33, 3, 3};
  s21::List<int> res{1, 222, 2, 33, 3};
  // std::list<int> stdlist{1, 1, 1, 1, 222, 222, 2, 33, 3, 3};
  s21list.Unique();
  // stdlist.unique();
  s21::List<int>::iterator s21it = s21list.Begin();
  s21::List<int>::iterator resit = res.Begin();
  // std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), res.Size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *resit);
    ++s21it;
    ++resit;
  }
}

TEST(ListTest, EmptyList2) {
  s21::List<int> list;

  list.Unique();

  ASSERT_TRUE(list.Empty());
}

TEST(ListTest, sort) {
  s21::List<double> s21lone{7.19};
  s21lone.Sort();
  s21::List<int> s21list{77, 55, 0, 87, 1111};
  std::list<int> stdlist{77, 55, 0, 87, 1111};
  s21list.Sort();
  stdlist.sort();
  s21::List<int>::iterator s21it = s21list.Begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.Size(), stdlist.size());
  for (size_t i = 0; i < s21list.Size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

class TestList {
 public:
  s21::List<int> s21_list_empty;
  s21::List<int> s21_list_three{1, 2, 3};
  s21::List<int> s21_list_test{123, 1, 2, 3, 123456789, 1, 911};
  s21::List<char> s21_char_list{'L', 'I', 'S', 'T'};
  s21::List<int> s21_list{1, 2, 3, 5, 9, 10};
  s21::List<int> s21_list_unique{111, 111, 111, 3, 4, 5, 6, 666, 666};

  std::list<int> std_list_empty;
  std::list<int> std_list_three{1, 2, 3};
  std::list<int> std_list_test{123, 1, 2, 3, 123456789, 1, 911};
  std::list<char> std_char_list{'L', 'I', 'S', 'T'};
  std::list<int> std_list_ten{1, 2, 3, 5, 9, 10};
  std::list<int> std_list_unique{111, 111, 111, 3, 4, 5, 6, 666, 666};
};

TEST(ListTest, default_constructor) {
  TestList tester;
  EXPECT_EQ(tester.s21_list_empty.Size(), tester.std_list_empty.size());
  EXPECT_EQ(tester.s21_list_empty.Empty(), tester.std_list_empty.empty());
}

TEST(ListTest, init_constructor2) {
  TestList tester;
  s21::List<int> a(3);
  std::list<int> b(3);
  s21::List<int>::iterator s21_it = a.Begin();
  std::list<int>::iterator std_it = b.begin();
  while (s21_it != a.End()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(ListTest, initializer_constructor) {
  TestList tester;
  s21::List<int>::iterator s21_iter = tester.s21_list_three.Begin();
  std::list<int>::iterator std_iter = tester.std_list_three.begin();
  while (s21_iter != tester.s21_list_three.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
  EXPECT_EQ(tester.s21_list_three.Size(), tester.std_list_three.size());
  EXPECT_EQ(tester.s21_list_three.Empty(), tester.std_list_three.empty());
}

TEST(ListTest, copy_constructor) {
  TestList tester;
  s21::List<int> s21_list_copy(tester.s21_list_three);
  std::list<int> std_list_copy(tester.std_list_three);
  s21::List<int>::iterator s21_iter = s21_list_copy.Begin();
  std::list<int>::iterator std_iter = std_list_copy.begin();
  while (s21_iter != s21_list_copy.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
  EXPECT_EQ(s21_list_copy.Size(), std_list_copy.size());
  EXPECT_EQ(s21_list_copy.Empty(), std_list_copy.empty());
}

TEST(ListTest, move_constructor_test2) {
  TestList tester;
  s21::List<int> s21_list_move(std::move(tester.s21_list_three));
  std::list<int> std_list_move(std::move(tester.std_list_three));
  s21::List<int>::iterator s21_iter = s21_list_move.Begin();
  std::list<int>::iterator std_iter = std_list_move.begin();
  while (s21_iter != s21_list_move.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
  EXPECT_EQ(s21_list_move.Size(), std_list_move.size());
  EXPECT_EQ(s21_list_move.Empty(), std_list_move.empty());
  s21_iter = tester.s21_list_three.Begin();
  std_iter = tester.std_list_three.begin();
  while (s21_iter != tester.s21_list_three.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
  EXPECT_EQ(tester.s21_list_three.Size(), tester.std_list_three.size());
  EXPECT_EQ(tester.s21_list_three.Empty(), tester.std_list_three.empty());
}

TEST(ListTest, move_assigment) {
  TestList tester;
  s21::List<int> s21_list_move{1, 2};
  std::list<int> std_list_move{1, 2};
  s21_list_move = std::move(tester.s21_list_test);
  std_list_move = std::move(tester.std_list_test);
  s21::List<int>::iterator s21_iter = s21_list_move.Begin();
  std::list<int>::iterator std_iter = std_list_move.begin();
  while (s21_iter != s21_list_move.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
  EXPECT_EQ(s21_list_move.Size(), std_list_move.size());
  EXPECT_EQ(s21_list_move.Empty(), std_list_move.empty());
}

TEST(ListTest, function_front) {
  TestList tester;
  EXPECT_EQ(tester.s21_char_list.Front(), tester.std_char_list.front());
}
// TEST(ListTest, function_front_empty) {
//   s21::List<int> my_list;
//   try {
//     my_list.Front();
//   } catch (const std::exception& ex) {
//     EXPECT_STREQ("List is empty", ex.what());
//   }
// }

TEST(ListTest, function_back) {
  TestList tester;
  EXPECT_EQ(tester.s21_char_list.Back(), tester.std_char_list.back());
}

TEST(ListTest, iterator_access) {
  TestList tester;
  s21::List<char>::iterator s21_iter = tester.s21_char_list.Begin();
  std::list<char>::iterator std_iter = tester.std_char_list.begin();
  while (s21_iter != tester.s21_char_list.End()) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }
}

TEST(ListTest, const_iterator_access) {
  TestList tester;
  s21::List<char>::const_iterator s21_const_iter = tester.s21_char_list.Begin();
  std::list<char>::const_iterator std_const_iter = tester.std_char_list.begin();
  while (s21_const_iter != tester.s21_char_list.End()) {
    EXPECT_EQ(*s21_const_iter, *std_const_iter);
    ++s21_const_iter;
    ++std_const_iter;
  }
}

TEST(ListTest, function_empty) {
  TestList tester;
  EXPECT_EQ(tester.s21_list_empty.Empty(), tester.std_list_empty.empty());
  EXPECT_EQ(tester.s21_list_three.Empty(), tester.std_list_three.empty());
}

TEST(ListTest, function_size) {
  TestList tester;
  EXPECT_EQ(tester.s21_list_three.Size(), tester.std_list_three.size());
  EXPECT_EQ(tester.s21_list_empty.Size(), tester.std_list_empty.size());
}

TEST(ListTest, function_max_size) {
  TestList tester;
  EXPECT_EQ(static_cast<long>(tester.s21_list_empty.MaxSize()),
            384307168202282325);
}

TEST(ListTest, function_clear) {
  TestList tester;
  tester.s21_list_three.Clear();
  tester.std_list_three.clear();
  EXPECT_EQ(tester.s21_list_three.Size(), tester.std_list_three.size());
}

TEST(ListTest, function_insert_begin) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list_empty.Begin();
  std::list<int>::iterator std_it = tester.std_list_empty.begin();
  s21_it = tester.s21_list_empty.Insert(s21_it, 666);
  std_it = tester.std_list_empty.insert(std_it, 666);
  ASSERT_EQ(*s21_it, *std_it);
  s21_it = tester.s21_list_empty.Begin();
  std_it = tester.std_list_empty.begin();
  while (s21_it != tester.s21_list_empty.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_empty.Size(), tester.std_list_empty.size());
  EXPECT_EQ(tester.s21_list_empty.Empty(), tester.std_list_empty.empty());
}

TEST(ListTest, function_insert_mid) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_it = tester.s21_list.Insert(s21_it, 666);
  std_it = tester.std_list_ten.insert(std_it, 666);
  ASSERT_EQ(*s21_it, *std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_insert_end) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.End();
  std::list<int>::iterator std_it = tester.std_list_ten.end();
  s21_it = tester.s21_list.Insert(s21_it, 666);
  std_it = tester.std_list_ten.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_insert_multi) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  s21_it = tester.s21_list.Insert(s21_it, 666);
  std_it = tester.std_list_ten.insert(std_it, 666);
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  s21_it = tester.s21_list.Insert(s21_it, 666);
  std_it = tester.std_list_ten.insert(std_it, 666);
  EXPECT_EQ(*s21_it, *std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_erase_begin) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  tester.s21_list.Erase(s21_it);
  tester.std_list_ten.erase(std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_erase_mid) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  tester.s21_list.Erase(s21_it);
  tester.std_list_ten.erase(std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_erase_end) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.End();
  std::list<int>::iterator std_it = tester.std_list_ten.end();
  --s21_it;
  --std_it;
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_erase_multi) {
  TestList tester;
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  ++s21_it;
  ++std_it;
  tester.s21_list.Erase(s21_it);
  tester.std_list_ten.erase(std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  tester.s21_list.Erase(s21_it);
  tester.std_list_ten.erase(std_it);
  s21_it = tester.s21_list.Begin();
  std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_push_back) {
  TestList tester;
  tester.s21_list_three.PushBack(666);
  tester.std_list_three.push_back(666);
  tester.s21_list_three.PushBack(123);
  tester.std_list_three.push_back(123);
  s21::List<int>::iterator s21_it = tester.s21_list_three.Begin();
  std::list<int>::iterator std_it = tester.std_list_three.begin();
  while (s21_it != tester.s21_list_three.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_three.Size(), tester.std_list_three.size());
  EXPECT_EQ(tester.s21_list_three.Empty(), tester.std_list_three.empty());
}

TEST(ListTest, function_pop_back) {
  TestList tester;
  tester.s21_list.PopBack();
  tester.std_list_ten.pop_back();
  tester.s21_list.PopBack();
  tester.std_list_ten.pop_back();
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_push_front) {
  TestList tester;
  tester.s21_list.PushFront(666);
  tester.std_list_ten.push_front(666);
  tester.s21_list.PushFront(123);
  tester.std_list_ten.push_front(123);
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_pop_front) {
  TestList tester;
  tester.s21_list.PopFront();
  tester.std_list_ten.pop_front();
  tester.s21_list.PopFront();
  tester.std_list_ten.pop_front();
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_swap) {
  TestList tester;
  s21::List<int> s21_list_swap{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> std_list_swap{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  tester.s21_list_test.Swap(s21_list_swap);
  tester.std_list_test.swap(std_list_swap);
  s21::List<int>::iterator s21_it = s21_list_swap.Begin();
  std::list<int>::iterator std_it = std_list_swap.begin();
  while (s21_it != s21_list_swap.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(s21_list_swap.Size(), std_list_swap.size());
  EXPECT_EQ(s21_list_swap.Empty(), std_list_swap.empty());
  s21_it = tester.s21_list_test.Begin();
  std_it = tester.std_list_test.begin();
  while (s21_it != tester.s21_list_test.End()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_test.Size(), tester.std_list_test.size());
  EXPECT_EQ(tester.s21_list_test.Empty(), tester.std_list_test.empty());
}

TEST(ListTest, function_merge_nonsorted) {
  TestList tester;
  s21::List<int> s21_list_merge{77, 125890, 430235, -236, 32858, 7457};
  std::list<int> std_list_merge{77, 125890, 430235, -236, 32858, 7457};
  tester.s21_list_test.Merge(s21_list_merge);
  tester.std_list_test.merge(std_list_merge);
  s21::List<int>::iterator s21_it = s21_list_merge.Begin();
  std::list<int>::iterator std_it = std_list_merge.begin();
  while (s21_it != s21_list_merge.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(s21_list_merge.Size(), std_list_merge.size());
  EXPECT_EQ(s21_list_merge.Empty(), std_list_merge.empty());
  s21_it = tester.s21_list_test.Begin();
  std_it = tester.std_list_test.begin();
  while (s21_it != tester.s21_list_test.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_test.Size(), tester.std_list_test.size());
  EXPECT_EQ(tester.s21_list_test.Empty(), tester.std_list_test.empty());
}

TEST(ListTest, function_merge_sorted) {
  TestList tester;
  s21::List<int> s21_list_merge{77, 125890, 430235, -236, 32858, 7457};
  std::list<int> std_list_merge{77, 125890, 430235, -236, 32858, 7457};
  tester.s21_list_test.Sort();
  tester.std_list_test.sort();
  tester.s21_list_test.Merge(s21_list_merge);
  tester.std_list_test.merge(std_list_merge);
  s21::List<int>::iterator s21_it = s21_list_merge.Begin();
  std::list<int>::iterator std_it = std_list_merge.begin();
  while (s21_it != s21_list_merge.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(s21_list_merge.Size(), std_list_merge.size());
  EXPECT_EQ(s21_list_merge.Empty(), std_list_merge.empty());
}

TEST(ListTest, function_reverse) {
  TestList tester;
  tester.s21_list.Reverse();
  tester.std_list_ten.reverse();
  s21::List<int>::iterator s21_it = tester.s21_list.Begin();
  std::list<int>::iterator std_it = tester.std_list_ten.begin();
  while (s21_it != tester.s21_list.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list.Size(), tester.std_list_ten.size());
  EXPECT_EQ(tester.s21_list.Empty(), tester.std_list_ten.empty());
}

TEST(ListTest, function_unique) {
  TestList tester;
  tester.s21_list_unique.Unique();
  tester.std_list_unique.unique();
  s21::List<int>::iterator s21_it = tester.s21_list_unique.Begin();
  std::list<int>::iterator std_it = tester.std_list_unique.begin();
  while (s21_it != tester.s21_list_unique.End()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_unique.Size(), tester.std_list_unique.size());
  EXPECT_EQ(tester.s21_list_unique.Empty(), tester.std_list_unique.empty());
}

TEST(ListTest, function_sort) {
  TestList tester;
  tester.s21_list_test.Sort();
  tester.std_list_test.sort();
  s21::List<int>::iterator s21_it = tester.s21_list_test.Begin();
  std::list<int>::iterator std_it = tester.std_list_test.begin();
  while (s21_it != tester.s21_list_test.End()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
  EXPECT_EQ(tester.s21_list_test.Size(), tester.std_list_test.size());
  EXPECT_EQ(tester.s21_list_test.Empty(), tester.std_list_test.empty());
}

TEST(ListTest, size_test) {
  s21::List<int> A = {};
  std::list<int> B = {};

  size_t a = A.Size();
  size_t b = B.size();
  ASSERT_EQ(a, b);
}

TEST(ListTest, TEST_2) {
  s21::List<int> A = {1, 2,  3,      4,   5,    6,    7,   8,
                      9, 10, 456545, 987, 5423, 3454, 3673};
  std::list<int> B = {1, 2,  3,      4,   5,    6,    7,   8,
                      9, 10, 456545, 987, 5423, 3454, 3673};

  size_t a = A.Size();
  size_t b = B.size();
  ASSERT_EQ(a, b);

  s21::List<int>::iterator iterA = A.Begin();
  std::list<int>::iterator iterB = B.begin();
  ASSERT_EQ(*iterA, *iterB);

  iterA = A.End();
  iterB = B.end();
  --iterA;
  --iterB;

  ASSERT_EQ(*iterA, *iterB);
}

TEST(ListTest, size_begin_test) {
  s21::List<double> A{77.987654};
  std::list<double> B{77.987654};

  size_t a = A.Size();
  size_t b = B.size();
  ASSERT_EQ(a, b);
  s21::List<double>::iterator iterA = A.Begin();
  std::list<double>::iterator iterB = B.begin();
  ASSERT_EQ(*iterA, *iterB);
}

TEST(ListTest, TEST_1) {
  s21::List<int> A = {1, 4, 6, 4, 8};
  s21::List<int> B(std::move(A));

  EXPECT_EQ((int)A.Size(), 0);

  EXPECT_EQ((int)B.Size(), 5);

  s21::List<int>::iterator iterB = B.Begin();
  EXPECT_EQ(*iterB, 1);
  iterB = B.End();
  --iterB;
  EXPECT_EQ(*iterB, 8);
}

TEST(ListTest, TEST_) {
  s21::List<int> A{0, 0, 0, 0, 0, 0, 0};
  s21::List<int>::iterator it = A.Begin();
  A.Insert(it, -999);
  it = A.Begin();

  std::list<int> original{0, 0, 0, 0, 0, 0, 0};
  std::list<int>::iterator it_orig = original.begin();
  original.insert(it_orig, -999);
  original.begin();
  for (it_orig = original.begin(); it_orig != original.end(); ++it_orig) {
    EXPECT_EQ(*it, *it_orig);
    ++it;
  }
}

TEST(ListTest, insert_test_list) {
  s21::List<int> A{0, 0, 0, 0, 0, 0, 0};
  s21::List<int>::iterator it = A.Begin();
  A.Insert(it, -999);
  A.Insert(it, -999);
  A.Insert(it, -999);
  A.Insert(it, -999);

  ++it;
  ++it;
  A.Insert(it, -999);
  it = A.Begin();

  std::list<int> original{0, 0, 0, 0, 0, 0, 0};
  std::list<int>::iterator it_orig = original.begin();
  original.insert(it_orig, -999);
  original.insert(it_orig, -999);
  original.insert(it_orig, -999);
  original.insert(it_orig, -999);
  ++it_orig;
  ++it_orig;
  original.insert(it_orig, -999);

  for (it_orig = original.begin(); it_orig != original.end(); ++it_orig) {
    EXPECT_EQ(*it, *it_orig);
    ++it;
  }
}

TEST(empty, TEST_1) {
  s21::List<int> A;
  std::list<int> original;
  bool A_ = A.Empty();
  bool B = original.empty();
  EXPECT_EQ(B, A_);
}

TEST(empty, TEST_2) {
  s21::List<int> A(30);
  std::list<int> original(30);
  bool A_ = A.Empty();
  bool B = original.empty();
  EXPECT_EQ(B, A_);
}

TEST(empty, TEST_3) {
  s21::List<int> A{1, 1, 1, 1};
  std::list<int> original{1, 1, 1, 1};
  bool A_ = A.Empty();
  bool B = original.empty();
  EXPECT_EQ(B, A_);
}

TEST(empty, TEST_4) {
  s21::List<int> A{1, 1, 1, 1};
  A.Clear();
  std::list<int> original{1, 1, 1, 1};
  original.clear();
  bool A_ = A.Empty();
  bool B = original.empty();
  EXPECT_EQ(B, A_);
}

TEST(const_reference_front_back, TEST_2) {
  std::list<int> A{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 10};
  int result = A.front();
  s21::List<int> B{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 10};
  int result_s21 = B.Front();
  EXPECT_EQ(result, result_s21);

  result = A.back();
  result_s21 = B.Back();
  EXPECT_EQ(result, result_s21);
}

TEST(const_reference_front_back, TEST_3) {
  std::list<int> A(20);
  int result = A.front();
  s21::List<int> B(20);
  int result_s21 = B.Front();
  EXPECT_EQ(result, result_s21);

  result = A.back();
  result_s21 = B.Back();
  EXPECT_EQ(result, result_s21);
}

TEST(PushBack_front_test, TEST_4) {
  std::list<char> A;
  A.push_back('I');
  A.push_front('G');
  A.push_back('\'');
  A.push_front('G');
  A.push_back('m');
  A.push_back(' ');
  A.push_front('s');
  A.push_back('D');
  A.push_front('!');
  A.push_front('!');
  s21::List<char> B;
  B.PushBack('I');
  B.PushFront('G');
  B.PushBack('\'');
  B.PushFront('G');
  B.PushBack('m');
  B.PushBack(' ');
  B.PushFront('s');
  B.PushBack('D');
  B.PushFront('!');
  B.PushFront('!');

  size_t s21_res = B.Size();
  size_t original = A.size();
  EXPECT_EQ(s21_res, original);
  std::list<char>::iterator it = A.begin();
  s21::List<char>::iterator it_mine = B.Begin();
  for (; it != A.end(); ++it) {
    EXPECT_EQ(*it, *it_mine);
    ++it_mine;
  }
}

TEST(ListTest, begin_1) {
  s21::List<int> my_list1{500, 15000, 30000};
  s21::List<int>::iterator first = my_list1.Begin();
  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*first, *std_list2.begin());
}

TEST(ListTest, end_1) {
  s21::List<int> my_list1{500, 15000, 30000};
  std::list<int> std_list2{500, 15000, 30000};

  EXPECT_EQ(std_list2.back(), my_list1.Back());
}

TEST(vector_constructor, case1) {
  s21::Vector<int> s21_vec_int;
  s21::Vector<double> s21_vec_double;
  s21::Vector<std::string> s21_vec_string;

  EXPECT_EQ(s21_vec_int.Size(), 0U);
  EXPECT_EQ(s21_vec_int.Capacity(), 0U);
  EXPECT_EQ(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.Size(), 0U);
  EXPECT_EQ(s21_vec_double.Capacity(), 0U);
  EXPECT_EQ(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.Size(), 0U);
  EXPECT_EQ(s21_vec_string.Capacity(), 0U);
  EXPECT_EQ(&s21_vec_string[0], nullptr);
}

TEST(vector_constructor, case2) {
  s21::Vector<int> s21_vec_int(5);
  s21::Vector<double> s21_vec_double(5);
  s21::Vector<std::string> s21_vec_string(5);

  EXPECT_EQ(s21_vec_int.Size(), 5U);
  EXPECT_EQ(s21_vec_int.Capacity(), 5U);
  EXPECT_NE(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.Size(), 5U);
  EXPECT_EQ(s21_vec_double.Capacity(), 5U);
  EXPECT_NE(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.Size(), 5U);
  EXPECT_EQ(s21_vec_string.Capacity(), 5U);
  EXPECT_NE(&s21_vec_string[0], nullptr);
}

TEST(vector_constructor, case3) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};

  EXPECT_EQ(s21_vec_int.Size(), 4U);
  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_int[3], 9);

  EXPECT_EQ(s21_vec_double.Size(), 4U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_double[3], 9.1);
}

TEST(vector_at, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.At(0), 1);
  EXPECT_EQ(s21_vec_double.At(0), 1.4);
  EXPECT_EQ(s21_vec_string.At(0), "Hello");
}

TEST(vector_at, case2) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_vec_int.At(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.At(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.At(5), std::out_of_range);
}

TEST(vector_at, case3) {
  s21::Vector<int> s21_vec_int;
  s21::Vector<double> s21_vec_double;
  s21::Vector<std::string> s21_vec_string;

  EXPECT_THROW(s21_vec_int.At(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.At(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.At(5), std::out_of_range);
}

TEST(vector_square_braces, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int[3], 9);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(vector_front, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Front(), 1);
  EXPECT_EQ(s21_vec_double.Front(), 1.4);
  EXPECT_EQ(s21_vec_string.Front(), "Hello");
}

TEST(vector_back, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Back(), 9);
  EXPECT_EQ(s21_vec_double.Back(), 9.1);
  EXPECT_EQ(s21_vec_string.Back(), "!");
}

TEST(vector_data, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Data(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.Data(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.Data(), &s21_vec_string[0]);
}

TEST(vector_empty, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Empty(), 0);
  EXPECT_EQ(s21_vec_double.Empty(), 0);
  EXPECT_EQ(s21_vec_string.Empty(), 0);
}

TEST(vector_empty, case2) {
  s21::Vector<int> s21_vec_int{};
  s21::Vector<double> s21_vec_double{};
  s21::Vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.Empty(), 1);
  EXPECT_EQ(s21_vec_double.Empty(), 1);
  EXPECT_EQ(s21_vec_string.Empty(), 1);
}

TEST(vector_size, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Size(), 4U);
  EXPECT_EQ(s21_vec_double.Size(), 4U);
  EXPECT_EQ(s21_vec_string.Size(), 4U);
}

TEST(vector_size, case2) {
  s21::Vector<int> s21_vec_int{};
  s21::Vector<double> s21_vec_double{};
  s21::Vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.Size(), 0U);
  EXPECT_EQ(s21_vec_double.Size(), 0U);
  EXPECT_EQ(s21_vec_string.Size(), 0U);
}

TEST(vector_max_size, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  std::vector<int> std_vec_int{1, 4, 8, 9};

  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  std::vector<double> std_vec_double{1.4, 4.8, 8.9, 9.1};

  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};
  std::vector<std::string> std_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(static_cast<long>(s21_vec_int.MaxSize()), std_vec_int.max_size());
  EXPECT_EQ(static_cast<long>(s21_vec_double.MaxSize()),
            std_vec_double.max_size());
  EXPECT_EQ(static_cast<long>(s21_vec_string.MaxSize()),
            std_vec_string.max_size());
}

TEST(vector_reserve, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.Reserve(20);
  s21_vec_double.Reserve(20);
  s21_vec_string.Reserve(20);

  EXPECT_EQ(s21_vec_int.Capacity(), 20U);
  EXPECT_EQ(s21_vec_double.Capacity(), 20U);
  EXPECT_EQ(s21_vec_string.Capacity(), 20U);
}

TEST(vector_reserve, case2) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.Reserve(2);
  s21_vec_double.Reserve(2);
  s21_vec_string.Reserve(2);

  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_string.Capacity(), 4U);
}

TEST(vector_capacity, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_string.Capacity(), 4U);
}

TEST(vector_capacity, case2) {
  s21::Vector<int> s21_vec_int{};
  s21::Vector<double> s21_vec_double{};
  s21::Vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.Capacity(), 0U);
  EXPECT_EQ(s21_vec_double.Capacity(), 0U);
  EXPECT_EQ(s21_vec_string.Capacity(), 0U);
}

TEST(vector_shrink_to_fit, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.Reserve(20);
  s21_vec_double.Reserve(20);
  s21_vec_string.Reserve(20);

  s21_vec_int.ShrinkToFit();
  s21_vec_double.ShrinkToFit();
  s21_vec_string.ShrinkToFit();

  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_string.Capacity(), 4U);
}

TEST(vector_shrink_to_fit, case2) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.ShrinkToFit();
  s21_vec_double.ShrinkToFit();
  s21_vec_string.ShrinkToFit();

  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_string.Capacity(), 4U);
}

TEST(vector_clear, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.Clear();
  s21_vec_double.Clear();
  s21_vec_string.Clear();

  EXPECT_EQ(static_cast<int>(s21_vec_int.Size()), 0);
  EXPECT_EQ(static_cast<int>(s21_vec_double.Size()), 0);
  EXPECT_EQ(static_cast<int>(s21_vec_string.Size()), 0);
}

TEST(vector_insert, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.Begin() + 2;
  auto pos_double = s21_vec_double.Begin() + 2;
  auto pos_string = s21_vec_string.Begin() + 2;

  s21_vec_int.Insert(pos_int, 2);
  s21_vec_double.Insert(pos_double, 2.0);
  s21_vec_string.Insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[2], 2);
  EXPECT_EQ(s21_vec_double[2], 2.0);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(vector_insert, case2) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.Begin();
  auto pos_double = s21_vec_double.Begin();
  auto pos_string = s21_vec_string.Begin();

  s21_vec_int.Insert(pos_int, 2);
  s21_vec_double.Insert(pos_double, 2.0);
  s21_vec_string.Insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_string[0], "world");
}

TEST(vector_insert, case3) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.End();
  auto pos_double = s21_vec_double.End();
  auto pos_string = s21_vec_string.End();

  s21_vec_int.Insert(pos_int, 2);
  s21_vec_double.Insert(pos_double, 2.0);
  s21_vec_string.Insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[4], 2);
  EXPECT_EQ(s21_vec_double[4], 2.0);
  EXPECT_EQ(s21_vec_string[4], "world");
}

TEST(vector_erase, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 1, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 1.0, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "", "world", "!"};

  auto pos_int = s21_vec_int.Begin() + 2;
  auto pos_double = s21_vec_double.Begin() + 2;
  auto pos_string = s21_vec_string.Begin() + 2;

  s21_vec_int.Erase(pos_int);
  s21_vec_double.Erase(pos_double);
  s21_vec_string.Erase(pos_string);

  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(vector_erase, case2) {
  s21::Vector<int> s21_vec_int{1, 1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.0, 1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"", "Hello", ",", "world", "!"};

  auto pos_int = s21_vec_int.Begin();
  auto pos_double = s21_vec_double.Begin();
  auto pos_string = s21_vec_string.Begin();

  s21_vec_int.Erase(pos_int);
  s21_vec_double.Erase(pos_double);
  s21_vec_string.Erase(pos_string);

  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(vector_push_back, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.PushBack(10);
  s21_vec_double.PushBack(10.0);
  s21_vec_string.PushBack("!!");

  EXPECT_EQ(*(s21_vec_int.End() - 1), 10);
  EXPECT_EQ(*(s21_vec_double.End() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.End() - 1), "!!");
}

TEST(vector_push_back, case2) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.Reserve(20);
  s21_vec_double.Reserve(20);
  s21_vec_string.Reserve(20);

  s21_vec_int.PushBack(10);
  s21_vec_double.PushBack(10.0);
  s21_vec_string.PushBack("!!");

  EXPECT_EQ(*(s21_vec_int.End() - 1), 10);
  EXPECT_EQ(*(s21_vec_double.End() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.End() - 1), "!!");
}

TEST(vector_pop_back, case1) {
  s21::Vector<int> s21_vec_int{1, 4, 8, 9};
  s21::Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.PopBack();
  s21_vec_double.PopBack();
  s21_vec_string.PopBack();

  EXPECT_EQ(s21_vec_int.Size(), 3U);
  EXPECT_EQ(s21_vec_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_double.Size(), 3U);
  EXPECT_EQ(s21_vec_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_string.Size(), 3U);
  EXPECT_EQ(s21_vec_string.Capacity(), 4U);
}

TEST(vector_swap, case1) {
  s21::Vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::Vector<int> s21_vec_res_int{0, 0, 0};

  s21::Vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::Vector<double> s21_vec_res_double{0.0, 0.0, 0.0};

  s21::Vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::Vector<std::string> s21_vec_res_string{"", "", ""};

  s21_vec_ref_int.Swap(s21_vec_res_int);
  s21_vec_ref_double.Swap(s21_vec_res_double);
  s21_vec_ref_string.Swap(s21_vec_res_string);

  EXPECT_EQ(s21_vec_res_int.Size(), 4U);
  EXPECT_EQ(s21_vec_res_int.Capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[2], 8);

  EXPECT_EQ(s21_vec_res_double.Size(), 4U);
  EXPECT_EQ(s21_vec_res_double.Capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);

  EXPECT_EQ(s21_vec_res_string.Size(), 4U);
  EXPECT_EQ(s21_vec_res_string.Capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[2], "world");
}
TEST(VectorTest, MoveAssignment) {
  s21::Vector<int> source_vector;
  for (int i = 1; i <= 5; ++i) {
    source_vector.PushBack(i);
  }

  s21::Vector<int> target_vector = std::move(source_vector);

  EXPECT_EQ(static_cast<int>(target_vector.Size()), 5);

  EXPECT_EQ(static_cast<int>(source_vector.Size()), 0);
  EXPECT_EQ(static_cast<int>(source_vector.Capacity()), 0);
  EXPECT_TRUE(source_vector.Empty());

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(static_cast<int>(target_vector[i]), i + 1);
  }
}
TEST(VectorTest, CopyConstructor) {
  s21::Vector<int> source_vector;
  for (int i = 1; i <= 5; ++i) {
    source_vector.PushBack(i);
  }

  s21::Vector<int> target_vector(source_vector);

  EXPECT_EQ(static_cast<int>(target_vector.Size()), 5);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(static_cast<int>(target_vector[i]), i + 1);
  }
}
TEST(QueueTest, MoveAssignmentOperator) {
  s21::Queue<int> q1;
  q1.Push(1);
  q1.Push(2);
  q1.Push(3);

  s21::Queue<int> q2;
  q2.Push(4);
  q2.Push(5);

  q1 = std::move(q2);

  ASSERT_TRUE(q2.Empty());
  ASSERT_EQ(q1.Front(), 4);
  q1.Pop();
  ASSERT_EQ(q1.Front(), 5);
  q1.Pop();

  ASSERT_TRUE(q1.Empty());
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
