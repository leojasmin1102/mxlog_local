#include <mxlog/parsing/ImportLog.h>

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

        LogEvent event = ParseLineSpace(line);
        m_events.push_back(event);
    }
}

// =======================
// 提取下一个 [] 字段的小工具函数（接口级）
// =======================
static bool ExtractBracketField(const string& line, size_t& pos, string& out)
{
    size_t l = line.find('[', pos);
    if (l == string::npos) return false;

    size_t r = line.find(']', l + 1);
    if (r == string::npos) return false;

    out = line.substr(l + 1, r - l - 1);
    pos = r + 1;
    return true;
}

// 解析一行日志 方法一（标准内容解析）
LogEvent ImportLog::ParseLine(const string& line)
{
    LogEvent event;

    size_t pos = 0;
    string field;

    // 时间戳
    if (ExtractBracketField(line, pos, field))
    {
        auto posA = field.find(' ');
        string tempEpochMs = field.substr(0, posA);
        string tempWeekday;
        if (posA == string::npos) {
            tempWeekday="";
        }
        else
        {
            tempWeekday = field.substr(posA + 1);
        }
        int a = 1;
        //event.timestamp.epochMs = ;
    }

    // 2️⃣ 用户标识（ip + mac）
    if (ExtractBracketField(line, pos, field))
        event.userId.ip= field;

    // 3️⃣ 软件名称 + 版本
    if (ExtractBracketField(line, pos, field))
        event.product.productName = field;

    // 4️⃣ 日志级别
    if (ExtractBracketField(line, pos, field))
        event.logLevel = field;

    // 5️⃣ 操作类型
    if (ExtractBracketField(line, pos, field))
        event.operateType = field;

    // 6️⃣ 剩余部分 = 操作结果
    if (pos < line.size())
    {
        // 去掉前导空格
        size_t start = line.find_first_not_of(' ', pos);
        if (start != string::npos)
            event.operateResult = line.substr(start);
    }

    return event;
}

// 解析一行日志 方法二（大括号之间带空格解析）
LogEvent ImportLog::ParseLineSpace(const string& line)
{
    LogEvent event;

    vector<string> fields;
    size_t pos = 0;

    // 顺序提取 [] 中的字段
    while (true)
    {
        size_t l = line.find('[', pos);
        if (l == string::npos) break;

        size_t r = line.find(']', l + 1);
        if (r == string::npos) break;

        fields.push_back(line.substr(l + 1, r - l - 1));
        pos = r + 1;
    }

    // 按顺序赋值（做长度保护）
    if (fields.size() > 0) event.timestamp.weekday = fields[0];
    if (fields.size() > 1) event.userId.ip = fields[1];
    if (fields.size() > 2) event.product.productName = fields[2];
    if (fields.size() > 3) event.operateType = fields[3];

    // 最后一个 ] 后面的内容 = 操作结果
    if (pos < line.size())
    {
        size_t start = line.find_first_not_of(' ', pos);
        if (start != string::npos)
            event.operateResult = line.substr(start);
    }

    return event;
}

