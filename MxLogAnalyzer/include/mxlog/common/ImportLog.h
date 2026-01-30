#ifndef IMPORT_LOG_H
#define IMPORT_LOG_H

#include <string>
#include <vector>

using namespace std;

//  输出示例：
//  [时间 星期] [用户ip 用户mac地址] [软件名称 软件版本] [日志级别] [操作类型] 操作结果
//  [2026 - 01 - 26 15:20 : 26 MO][192.168.8.196 50 - EB - F4 - B5 - 6F - F7][MxSim.Mechanical.GUI V2.0][INFO][SET_PROPERTY] SUCCESS

// =======================
// 一条日志事件（最简单版本）
// =======================
//struct LogEvent
//{
//
//};


struct LogEvent
{
    string timestamp;   // 时间戳
    string content;     // 原始内容
};

// =======================
// ImportLog 类
// =======================
class ImportLog
{
public:
    ImportLog();
    ~ImportLog();

    // 对外接口：导入日志目录
    void ImportDirectory(const string& dirPath);

    // 获取解析后的日志
    const vector<LogEvent>& GetEvents() const;

private:
    // 扫描目录
    void ScanDirectory(const string& dirPath);

    // 解析单个 log 文件
    void ParseLogFile(const string& filePath);

    // 解析一行日志
    LogEvent ParseLine(const string& line);

private:
    vector<string> m_logFiles;   // 所有 log 文件路径
    vector<LogEvent>    m_events;     // 解析后的日志事件
};

#endif // IMPORT_LOG_H
