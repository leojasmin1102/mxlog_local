#include <iostream>
#include <cassert>
#include <mxlog/parsing/ImportLog.h>
#include <mxlog/parsing/transAtomic.h>

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

    TransAtomic ta;
    ta.Transform(res);

    const auto& atoms = ta.GetAto();
    cout << "原子事件数: " << atoms.size() << "\n" << endl;

    for (size_t i = 0; i < std::min<size_t>(5, atoms.size()); ++i)
    {
        const auto& e = atoms[i];

        cout << "---- 原子事件 " << i << " ----" << endl;
        cout << "用户: " << e.userId << endl;
        cout << "2h槽 " << e.tsh.slot_id << endl;
        cout << "是否为求解器完成计算" << e.isSolverEnd << endl;
    }
}
