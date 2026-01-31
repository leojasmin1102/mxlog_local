#include <mxlog/parsing/transAtomic.h>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

TransAtomic::TransAtomic() {}
TransAtomic::~TransAtomic(){}

void TransAtomic::Transform(const vector<LogEvent>& events)
{
    logato.clear();
    logato.reserve(events.size());

    for (const auto& e : events)
    {
        logato.push_back(ParseAgain(e));
    }
}

const vector<LogEvnetAtomic>& TransAtomic::GetAto() const
{
    return logato;
}

static int SafeToInt(const string& s)
{
    try { return stoi(s); }
    catch (...) { return 0; }
}

// ======================
// 二次解析
// ======================
LogEvnetAtomic TransAtomic::ParseAgain(const LogEvent& e)
{
    LogEvnetAtomic a;

    // ========= userId =========
    a.userId = e.userId.strUserId;

    // ========= 时间解析 =========
    // 格式：2026 - 01 - 26 15:20 : 26
    int Y = 0, M = 0, D = 0, h = 0, m = 0, s = 0;

    sscanf(e.timestamp.strepochMs.c_str(),
        "%d - %d - %d %d:%d : %d",
        &Y, &M, &D, &h, &m, &s);

    a.tsm.date = Y * 10000 + M * 100 + D;
    a.tsh.date = a.tsm.date;

    // ========= 30分钟槽 =========
    a.tsm.slot_id = h * 2 + (m >= 30 ? 1 : 0);

    // ========= 2小时槽 =========
    a.tsh.slot_id = h / 2;

    // ========= solver结束判断 =========
    // 你以后可改为配置驱动
    a.isSolverEnd = (e.operateType == "SOLVER_END");

    // ========= duration 接口保留 =========
    a.duration = 0;

    return a;

    //ParseDuration()
    //ParseUserHash()
    //ParseWorkday()
    //ParseSolverSession()
}
