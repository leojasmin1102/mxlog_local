#include <mxlog/parsing/ImportLog.h>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

ImportLog::ImportLog()
{
    // 目前不需要初始化内容
}

ImportLog::~ImportLog()
{
    // vector 会自动释放，不需要手动 delete
}

// 对外接口：导入目录
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

// 获取日志事件
const vector<LogEvent>& ImportLog::GetEvents() const
{
    return m_events;
}

// 扫描目录，找 .log 文件
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

// 解析单个 log 文件
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
    if (fields.size() > 0) 
    {
        auto posA = fields[0].rfind(' ');
        event.timestamp.strepochMs = fields[0].substr(0, posA);
        string tempWeekday = "";
        if (posA == string::npos) {
            tempWeekday = "";
        }
        else
        {
            tempWeekday = fields[0].substr(posA + 1);
        }
        event.timestamp.weekday = tempWeekday;
    }
    //event.timestamp.weekday = fields[0];
    if (fields.size() > 1) 
    {
        event.userId.strUserId = fields[1];
    }

    //event.userId.ip = fields[1];
    if (fields.size() > 2) 
    {
        auto posB = fields[2].find(' ');
        event.product.productName = fields[0].substr(0, posB);
        string tempVersion = "";
        if (posB == string::npos) {
            tempVersion = "";
        }
        else
        {
            tempVersion = fields[2].substr(posB + 1);
        }
        event.product.productVersion = tempVersion;
    }
    if (fields.size() > 3) event.operateType = fields[3];

    // 操作结果
    if (pos < line.size())
    {
        size_t start = line.find_first_not_of(' ', pos);
        if (start != string::npos)
            event.operateResult = line.substr(start);
    }

    return event;
}

