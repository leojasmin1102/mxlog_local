#include <mxlog/common/UsageRate.h>

UsageRate::UsageRate() {}
UsageRate::~UsageRate() {}

double UsageRate::CalcUsageRate(
    const vector<LogEvnetAtomic>& atoms)
{
    m_validSlots.clear();

    if (atoms.empty())
        return 0.0;

    // 收集有效slot
    for (const auto& a : atoms)
    {
        int date = a.tsm.date;
        int slot = a.tsm.slot_id;

        if (!IsWorkday(date))
            continue;

        if (!IsKeyOperation(a))
            continue;

        m_validSlots.insert({ date, slot });
    }

    // 有效时长
    double validHours =
        (double)m_validSlots.size() * 0.5; // 每slot=30分钟

    // 月份
    int anyDate = atoms.front().tsm.date;
    int yyyymm = anyDate / 100;

    double totalHours = GetWorkdayTotalHours(yyyymm);
    if (totalHours <= 0.0)
        return 0.0;

    return validHours / totalHours;
}

bool UsageRate::IsWorkday(int yyyymmdd) const
{
    return true;
}

bool UsageRate::IsKeyOperation(
    const LogEvnetAtomic& a) const
{
    // 导入解析/模型调试/ 求解
    if (a.isSolverEnd)
        return true;
    if (a.duration > 0)
        return true;
    return false;
}

double UsageRate::GetWorkdayTotalHours(int yyyymm) const
{
    return 22.0 * 8.0;
}



