#ifndef MONTHLY_ACTIVE_H
#define MONTHLY_ACTIVE_H

#include <vector>
#include <set>
#include <cstdint>
#include <mxlog/parsing/transAtomic.h>

using namespace std;

// 月活率统计模块
class MonthlyActiveCalculator
{
public:
    MonthlyActiveCalculator();
    ~MonthlyActiveCalculator();

    // 主入口
    double CalcMonthlyActiveRate(const vector<LogEvnetAtomic>& atoms);

private:
    // 判断是否工作日
    bool IsWorkday(int yyyymmdd) const;

    // 判断是否为有效操作
    bool IsEffectiveOperation(const LogEvnetAtomic& a) const;

    // 获取当月所有工作日数量
    int GetMonthWorkdayCount(int yyyymm) const;

private:
    // yyyyMMdd
    set<int> m_effectiveDays;
};

#endif
