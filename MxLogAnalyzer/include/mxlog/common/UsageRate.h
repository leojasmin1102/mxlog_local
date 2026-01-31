#pragma once
#ifndef USAGE_RATE__H
#define USAGE_RATE__H

#include <vector>
#include <set>
#include <utility>
#include <mxlog/parsing/transAtomic.h>

using namespace std;

// 使用率统计模块
class UsageRate
{
public:
    UsageRate();
    ~UsageRate();

    // 主入口
    double CalcUsageRate(const vector<LogEvnetAtomic>& atoms);

private:
    // 是否工作日
    bool IsWorkday(int yyyymmdd) const;

    // 是否关键操作
    bool IsKeyOperation(const LogEvnetAtomic& a) const;

    // 获取工作日总小时数
    double GetWorkdayTotalHours(int yyyymm) const;

private:
    //(date,slot30min)
    set<pair<int, int>> m_validSlots;
};

#endif
