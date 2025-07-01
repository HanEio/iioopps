#ifndef _SHUDU_COMMON_H_
#define _SHUDU_COMMON_H_

// 代表一个坐标点
struct point_t
{
    int x;
    int y;
};

// 代表一个格子的状态和值
struct point_value_t
{
    int value; // 格子里的数字 (0代表未填)
    enum class State { INITED, ERASED }; // INITED: 初始数字, ERASED: 被挖掉的
    State state;
    bool is_error; // 是否有冲突
};

const int UNSELECTED = 0; // 用0代表未选择或空格子

enum class Difficulty { EASY = 1, NORMAL, HARD };

#endif 