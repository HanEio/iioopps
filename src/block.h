#ifndef _SHUDU_BLOCK_H_
#define _SHUDU_BLOCK_H_

#include "common.h"

// 代表一个行政区域（行、列或九宫格）
class CBlock
{
    static const int MAX_COUNT = 9;

  public:
    CBlock();
    bool isValid() const; // 检查这个区域是否合法（无重复数字）
    void push_back(point_value_t *point); // 将一个格子的指针添加到本区域
    void print(int cur_point_col = -1) const; // (这是为show()重构准备的)
    point_value_t *_numbers[MAX_COUNT]; // 指向9个格子的指针数组
  private:
    int _count; // 当前已添加的格子数量
};

#endif 