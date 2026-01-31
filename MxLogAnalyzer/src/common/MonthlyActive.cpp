#include "mxlog/common/MonthlyActive.h"

MonthlyActiveCalculator::MonthlyActiveCalculator() {}
MonthlyActiveCalculator::~MonthlyActiveCalculator() {}

double MonthlyActiveCalculator::CalcMonthlyActiveRate(
    const vector<LogEvnetAtomic>& atoms)
{
    m_effectiveDays.clear();

    if (atoms.empty())
        return 0.0;

    for (const auto& a : atoms)
    {
        int date = a.tsh.date;   

        if (!IsWorkday(date))
            continue;

        if (!IsEffectiveOperation(a))
            continue;

        m_effectiveDays.insert(date);
    }

    // 获取月份
    int anyDate = atoms.front().tsh.date;
    int yyyymm = anyDate / 100;

    int totalWorkdays = GetMonthWorkdayCount(yyyymm);
    if (totalWorkdays == 0)
        return 0.0;

    double rate =
        (double)m_effectiveDays.size()
        / (double)totalWorkdays
        * 100.0;

    return rate;
}
