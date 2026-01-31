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
        cout << "毫秒时间戳 " << e.timestamp.strepochMs << endl;
        cout << "星期 " << e.timestamp.weekday << endl;
        cout << "用户唯一ID：" << e.userId.strUserId << endl;
        cout << "产品名：" << e.product.productName << endl;
        cout << "产品版本：" << e.product.productVersion << endl;
        cout << "操作类型:" << e.operateType << endl;

        // 简单字段有效性检查
        assert(!e.timestamp.strepochMs.empty());
    }

    cout << "\n基本解析正常" << endl;
}
