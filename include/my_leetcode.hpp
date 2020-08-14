///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////
/// Copyright (c) 2019,2020 Lijiancong. All rights reserved.
///
/// Use of this source code is governed by a MIT license
/// that can be found in the License file.
///
/// @file   my_leetcode.hpp
/// @brief  我的leetcode题解
///
/// @author lijiancong, pipinstall@163.com
/// @date   2020-07-23 20:13:41
///////// ///////// ///////// ///////// ///////// ///////// ///////// /////////

#ifndef INCLUDE_MY_LEETCODE_HPP_
#define INCLUDE_MY_LEETCODE_HPP_

#include <string>
#include <unordered_map>
#include <vector>

namespace lee {
inline namespace leetcode {
/// 8. 字符串转换整数 (atoi)
/// 请你来实现一个 atoi 函数，使其能将字符串转换成整数。
///
/// 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。接下来的转化规则如下：
///
/// 如果第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字字符组合起来，形成一个有符号整数。
/// 假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成一个整数。
/// 该字符串在有效的整数部分之后也可能会存在多余的字符，那么这些字符可以被忽略，它们对函数不应该造成影响。
/// 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换，即无法进行有效转换。
///
/// 在任何情况下，若函数不能进行有效的转换时，请返回 0 。
///
/// 提示：
///
/// 本题中的空白字符只包括空格字符 ' ' 。
/// 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 −
/// 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。  
///
/// 示例 1:
///
/// 输入: "42"
/// 输出: 42
/// 示例 2:
///
/// 输入: "   -42"
/// 输出: -42
/// 解释: 第一个非空白字符为 '-', 它是一个负号。
///      我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42 。
/// 示例 3:
///
/// 输入: "4193 with words"
/// 输出: 4193
/// 解释: 转换截止于数字 '3' ，因为它的下一个字符不为数字。
/// 示例 4:
///
/// 输入: "words and 987"
/// 输出: 0
/// 解释: 第一个非空字符是 'w', 但它不是数字或正、负号。
///      因此无法执行有效的转换。
/// 示例 5:
///
/// 输入: "-91283472332"
/// 输出: -2147483648
/// 解释: 数字 "-91283472332" 超过 32 位有符号整数范围。
///      因此返回 INT_MIN (−231) 。
int myAtoi(std::string str) {
  str.erase(0, str.find_first_not_of(' '));
  if (str.front() == '+') {
    if (std::isdigit(*std::next(str.begin()))) {
      str.erase(str.begin());
    } else {
      return 0;
    }
  }
  int flag = 1;
  if (str.front() == '-') {
    if (!std::isdigit(*std::next(str.begin()))) {
      return 0;
    } else {
      str.erase(str.begin());
      flag = -1;
    }
  }
  auto it_end = str.end();
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (!std::isdigit(*it)) {
      it_end = it;
      break;
    }
  }

  std::string num(str.begin(), it_end);
  if (num.empty()) {
    return 0;
  }
  long long result = 0;
  for (int i = 0; i < num.size(); ++i) {
    result += num.at(i) - '0';

    if (result > INT_MAX && (flag == 1)) {
      return INT_MAX;
    }
    if (result * flag < INT_MIN && (flag == -1)) {
      return INT_MIN;
    }
    if (i == num.size() - 1) {
      break;
    }
    result *= 10;
  }
  return static_cast<int>(result * flag);
}

class Automaton {
  std::string state = "start";
  std::unordered_map<std::string, std::vector<std::string>> table = {
      {"start", {"start", "signed", "in_number", "end"}},
      {"signed", {"end", "end", "in_number", "end"}},
      {"in_number", {"end", "end", "in_number", "end"}},
      {"end", {"end", "end", "end", "end"}}};

  int get_col(char c) {
    if (isspace(c)) return 0;
    if (c == '+' || c == '-') return 1;
    if (isdigit(c)) return 2;
    return 3;
  }

 public:
  int sign = 1;
  long long ans = 0;

  void get(char c) {
#undef min
    state = table[state][get_col(c)];
    if (state == "in_number") {
      ans = ans * 10 + c - '0';
      ans = sign == 1 ? std::min(ans, (long long)INT_MAX)
                      : std::min(ans, -(long long)INT_MIN);
    } else if (state == "signed")
      sign = c == '+' ? 1 : -1;
  }
};

int myAtoi_offical(std::string str) {
  Automaton automaton;
  for (char c : str) automaton.get(c);
  return automaton.sign * automaton.ans;
}

/// 15. 三数之和
/// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c
/// ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
///
/// 注意：答案中不可以包含重复的三元组。
///
/// 示例：
///
/// 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
///
/// 满足要求的三元组集合为：
/// [
///   [-1, 0, 1],
///   [-1, -1, 2]
/// ]
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {}

/// 字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。
/// 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。 示例 1:
/// 输入:
/// first = "pale"
/// second = "ple"
/// 输出: True
///
/// 示例 2:
/// 输入:
/// first = "pales"
/// second = "pal"
/// 输出: False
bool oneEditAway(std::string first, std::string second) {}
}  // namespace leetcode
}  // namespace lee

#endif  // INCLUDE_MY_LEETCODE_HPP_