#ifndef _SHUDU_SCENE_H_
#define _SHUDU_SCENE_H_

#include "common.h"
#include "block.h"

class CScene
{
  public:
    CScene();
    void show() const;
    void generate();   // 生成数独终盘
    void eraseRandomGrids(const int count); //擦除指定数量的格子
    void play();
    bool isComplete();
    void updateErrorStatus();
  private:
    void init();
    point_value_t _map[81]; // 9x9的棋盘数据
    point_t _cur_point; // 当前选中的格子
    CBlock _row_block[9];    // 9个行Block
    CBlock _column_block[9]; // 9个列Block
    CBlock _xy_block[3][3];  // 3x3的九宫格Block
    void setValue(const point_t& p, int value);
    void setValue(int value);
};

#endif 