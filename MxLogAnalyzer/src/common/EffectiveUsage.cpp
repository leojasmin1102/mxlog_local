#include <mxlog/common/EffectiveUsage.h>

EffectiveUsageCalculator::EffectiveUsageCalculator() {}
EffectiveUsageCalculator::~EffectiveUsageCalculator() {}

double EffectiveUsageCalculator::CalcEffectiveUsageHours(const vector<LogEvnetAtomic>& atoms)
{
    m_validSlots.clear();

    if (atoms.empty())
        return 0.0;

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

    // 每个slot=30分钟=0.5小时
    double totalHours = m_validSlots.size() * 0.5;

    return totalHours;
}

// 判断是否工作日
bool EffectiveUsageCalculator::IsWorkday(int yyyymmdd) const
{
    return true;
}

// 判断是否关键操作
bool EffectiveUsageCalculator::IsKeyOperation(
    const LogEvnetAtomic& a) const
{
    return true;
}

