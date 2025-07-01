#include "scene.h"
#include <iostream>
#include <memory.h> // for memset
#include <vector>
#include <numeric>   // for std::iota
#include <random>    // for std::mt19937
#include <algorithm> // for std::shuffle
#include <cassert>
#include <conio.h> // for _getch()
#include "color.h"
#include "block.h"


CScene::CScene()
{
    // 构造函数中初始化棋盘，所有格子都设为0
    memset(_map, 0, sizeof(_map));
    _cur_point = {0, 0}; // 光标初始位置在左上角
    init();
}

void CScene::init()
{
    for(int row = 0; row < 9; ++row)
    {
        for(int col = 0; col < 9; ++col)
        {
            point_value_t* current_cell = &_map[row * 9 + col];
            _row_block[row].push_back(current_cell);
            _column_block[col].push_back(current_cell);
            _xy_block[row / 3][col / 3].push_back(current_cell);
        }
    }
}

void CScene::show() const
{
    system("cls"); // 清屏，让每次显示都干净
    for (int r = 0; r < 9; ++r)
    {
        if (r % 3 == 0) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
        std::cout << "| ";
        for (int c = 0; c < 9; ++c)
        {
            bool is_cursor = (r == _cur_point.y && c == _cur_point.x);
            bool is_err = _map[r * 9 + c].is_error;
            if (is_cursor) { std::cout << Color::Modifier(Color::BG_BLUE); }
            if (is_err) { std::cout << Color::Modifier(Color::FG_RED); }
            int value = _map[r * 9 + c].value;
            if (value == UNSELECTED) {
                std::cout << ". ";
            } else {
                std::cout << value << " ";
            }
            if (is_err) { std::cout << Color::Modifier(Color::FG_DEFAULT); }
            if (is_cursor) { std::cout << Color::Modifier(Color::BG_DEFAULT); }
            if ((c + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
} 


// --- 辅助函数：生成一个1-9的随机序列 ---
std::vector<int> get_shuffled_unit() {
    std::vector<int> unit(9);
    std::iota(unit.begin(), unit.end(), 1); // 填充1, 2, ..., 9
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(unit.begin(), unit.end(), g); // 随机打乱
    return unit;
}

// --- 辅助函数：检查在(row, col)位置放数字num是否合法 ---
bool is_safe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // 检查行
    for (int x = 0; x < 9; ++x)
        if (board[row][x] == num) return false;
    // 检查列
    for (int y = 0; y < 9; ++y)
        if (board[y][col] == num) return false;
    // 检查3x3九宫格
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i + startRow][j + startCol] == num) return false;
    return true;
}

// --- 核心回溯算法 ---
bool solve_sudoku(std::vector<std::vector<int>>& board, int row, int col) {
    if (row == 8 && col == 9) return true; // 成功填满
    if (col == 9) { // 一行结束，换到下一行
        row++;
        col = 0;
    }

    if (board[row][col] > 0) return solve_sudoku(board, row, col + 1); // 如果已填，跳到下一个

    for (int num : get_shuffled_unit()) { // 尝试1-9的随机排列
        if (is_safe(board, row, col, num)) {
            board[row][col] = num;
            if (solve_sudoku(board, row, col + 1)) return true; // 如果后续成功，返回true
            board[row][col] = 0; // 否则，回溯，擦除数字
        }
    }
    return false; // 1-9都试过不行，返回false
}

void CScene::generate()
{
    // 1. 创建一个临时的二维vector来执行算法
    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));

    // 2. 调用回溯函数填充它
    solve_sudoku(board, 0, 0);

    // 3. 将结果复制回我们的_map
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            _map[r * 9 + c].value = board[r][c];
            _map[r * 9 + c].state = point_value_t::State::INITED; // 标记为初始数字
        }
    }
}

void CScene::eraseRandomGrids(const int count)
{
    // 1. 创建一个包含0-80索引的vector
    std::vector<int> indices(81);
    std::iota(indices.begin(), indices.end(), 0);

    // 2. 随机打乱索引
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    // 3. 根据count，挖掉前count个格子
    for (int i = 0; i < count; ++i) {
        int grid_index = indices[i];
        _map[grid_index].value = UNSELECTED;
        _map[grid_index].state = point_value_t::State::ERASED; // 标记为被挖掉的
    }
}

void CScene::setValue(const point_t& p, int value)
{
    _map[p.y * 9 + p.x].value = value;
}

void CScene::setValue(int value)
{
    setValue(_cur_point, value);
}

bool CScene::isComplete()
{
    for(const auto& cell : _map) {
        if (cell.value == UNSELECTED) return false;
    }
    for(int i = 0; i < 9; ++i) {
        if (!_row_block[i].isValid() || !_column_block[i].isValid()) return false;
    }
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if (!_xy_block[i][j].isValid()) return false;
        }
    }
    return true;
}

void CScene::updateErrorStatus()
{
    for (auto& cell : _map) { cell.is_error = false; }
    auto check_and_flag_errors = [&](CBlock& block) {
        int freq[10] = {};
        for (int i = 0; i < 9; ++i) {
            int val = block._numbers[i]->value;
            if (val != 0) freq[val]++;
        }
        for (int i = 0; i < 9; ++i) {
            int val = block._numbers[i]->value;
            if (val != 0 && freq[val] > 1) {
                block._numbers[i]->is_error = true;
            }
        }
    };
    for(int i=0; i<9; ++i) {
        check_and_flag_errors(_row_block[i]);
        check_and_flag_errors(_column_block[i]);
    }
    for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) check_and_flag_errors(_xy_block[i][j]);
}

void CScene::play()
{
    int last_value = 0;
    while (true)
    {
        show();
        if (isComplete()) {
            std::cout << "Congratulation! You Win!" << std::endl;
            break;
        }
        char ch = _getch();
        if (ch >= '1' && ch <= '9') {
            if (_map[_cur_point.y * 9 + _cur_point.x].state != point_value_t::State::ERASED) {
                std::cout << "This number cannot be modified." << std::endl;
                _getch();
            } else {
                setValue(ch - '0');
                updateErrorStatus();
            }
        } else {
            switch (ch) {
                case 'w': case 'W': _cur_point.y = std::max(0, _cur_point.y - 1); break;
                case 's': case 'S': _cur_point.y = std::min(8, _cur_point.y + 1); break;
                case 'a': case 'A': _cur_point.x = std::max(0, _cur_point.x - 1); break;
                case 'd': case 'D': _cur_point.x = std::min(8, _cur_point.x + 1); break;
                case 27: return; // ESC退出
                case '\r': case '\n': // 回车键
                    updateErrorStatus();
                    if (isComplete()) {
                        show();
                        std::cout << "Congratulation! You Win!" << std::endl;
                        _getch();
                        return;
                    } else {
                        show();
                        std::cout << "Not complete or has errors!" << std::endl;
                        _getch();
                    }
                    break;
            }
        }
    }
}