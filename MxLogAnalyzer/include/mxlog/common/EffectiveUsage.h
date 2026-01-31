#pragma once
#ifndef EFFECTIVE_USAGE_H
#define EFFECTIVE_USAGE_H

#include <vector>
#include <set>
#include <utility>
#include <mxlog/parsing/transAtomic.h>

using namespace std;

// 有效使用时长统计模块
class EffectiveUsageCalculator
{
public:
    EffectiveUsageCalculator();
    ~EffectiveUsageCalculator();

    // 计算有效使用时长（小时）
    double CalcEffectiveUsageHours(const vector<LogEvnetAtomic>& atoms);

private:
    // 判断是否工作日
    bool IsWorkday(int yyyymmdd) const;

    // 判断是否关键操作
    bool IsKeyOperation(const LogEvnetAtomic& a) const;

private:
    // 用来去重slot(date,slot30min)
    set<pair<int, int>> m_validSlots;
};

#endif
