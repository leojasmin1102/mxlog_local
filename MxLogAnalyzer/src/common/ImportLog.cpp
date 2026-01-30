#include <mxlog/common/ImportLog.h>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

// =======================
// 构造函数
// =======================
ImportLog::ImportLog()
{
    // 目前不需要初始化内容
}

// =======================
// 析构函数
// =======================
ImportLog::~ImportLog()
{
    // vector 会自动释放，不需要手动 delete
}

// =======================
// 对外接口：导入目录
// =======================
void ImportLog::ImportDirectory(const string& dirPath)
{
    m_logFiles.clear();
    m_events.clear();

    ScanDirectory(dirPath);

    for (const auto& file : m_logFiles)
    {
        ParseLogFile(file);
    }
}

// =======================
// 获取日志事件
// =======================
const vector<LogEvent>& ImportLog::GetEvents() const
{
    return m_events;
}

// =======================
// 扫描目录，找 .log 文件
// =======================
void ImportLog::ScanDirectory(const string& dirPath)
{
    if (!fs::exists(dirPath))
    {
        cout << "Directory not exist: " << dirPath << endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(dirPath))
    {
        if (!entry.is_regular_file())
            continue;

        if (entry.path().extension() == ".log")
        {
            m_logFiles.push_back(entry.path().string());
        }
    }
}

// =======================
// 解析单个 log 文件
// =======================
void ImportLog::ParseLogFile(const string& filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "这个路径下的文件夹打开失败: " << filePath << std::endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        LogEvent event = ParseLine(line);
        m_events.push_back(event);
    }
}

// =======================
// 解析一行日志（最简单版本）
// =======================
LogEvent ImportLog::ParseLine(const string& line)
{
    LogEvent event;
    event.content = line;

    // 简单处理：前 23 个字符当作时间戳
    // 例如：2026-01-21 14:35:20.123
    if (line.size() >= 23)
    {
        event.timestamp = line.substr(0, 23);
    }
    else
    {
        event.timestamp = "未知";
    }

    return event;
}