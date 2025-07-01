#include "block.h"
#include <cassert>

CBlock::CBlock() : _count(0) {}

void CBlock::push_back(point_value_t *point)
{
    assert(nullptr != point && _count < MAX_COUNT);
    _numbers[_count++] = point;
}

bool CBlock::isValid() const
{
    // 遍历所有数字对，检查是否有重复
    for (int i = 0; i < _count - 1; ++i)
    {
        if (UNSELECTED == _numbers[i]->value) continue;
        for (int j = i + 1; j < _count; ++j)
        {
            if (UNSELECTED == _numbers[j]->value) continue;
            if (_numbers[i]->value == _numbers[j]->value) return false;
        }
    }
    return true;
} 