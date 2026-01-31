#pragma once
#include <string>
#include <vector>
#include "ImportLog.h"

//using namespace std;

struct TimeSlot30Min {
	int date;       // YYYYMMDD
	int slot_id;    // 0~47
};

struct TimeSlot2Hour {
	int date;       // YYYYMMDD
	int slot_id;    // 0~11
};

// 对一条日志事件再次拆分
struct LogEvnetAtomic
{
	string userId;	//后续再考虑是否用hash;
	TimeSlot30Min tsm;
	TimeSlot2Hour tsh;
	bool isSolverEnd;
	int64_t duration = 0;
	bool isSolverStart;
};

class TransAtomic
{
public:
	TransAtomic();
	~TransAtomic();
	void Transform(const vector<LogEvent>& events);
	const vector<LogEvnetAtomic>& GetAto() const;

private:
	LogEvnetAtomic ParseAgain(const LogEvent& e);

private:
	vector<LogEvnetAtomic> logato;
};
