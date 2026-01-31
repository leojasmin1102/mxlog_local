#include <iostream>
#include <cassert>
#include <mxlog/parsing/ImportLog.h>

using  namespace std;

int main() {
    ImportLog IL;
    string dir = "D:\\DemoCode\\mxlog_local\\MxLogAnalyzer\\tests";

    IL.ImportDirectory(dir);
    const auto& res = IL.GetEvents();

    // 是否读到日志
    if (res.empty()) {
        cout << "没有读取到日志事件" << endl;
        return 1;
    }

    cout << "读取到事件数: " << res.size() << "\n" << endl;

    // 打印前5条检查解析是否正确
    for (size_t i = 0; i < std::min<size_t>(25, res.size()); ++i)
    {
        const auto& e = res[i];

        cout << "---- 事件 " << i << " ----" << endl;
        cout << "时间戳 " << e.timestamp.weekday << endl;
        cout << "用户唯一ID：" << e.userId.ip << endl;
        cout << "产品名以及版本：" << e.product.productName << endl;
        cout << "操作类型:" << e.operateType << endl;

        // 简单字段有效性检查
        assert(!e.timestamp.weekday.empty());
    }

    cout << "\n基本解析看起来正常" << endl;
}
