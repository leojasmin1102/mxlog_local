#include <iostream>
#include <mxlog/common/ImportLog.h>

using namespace std;

int main() {
	ImportLog IL;
	string dir = "D:\\DemoCode\\mxlog_local\\MxLogAnalyzer\\tests";
	IL.ImportDirectory(dir);
	const std::vector<LogEvent>& res = IL.GetEvents();
	for (auto& e : res)
	{
		cout << "前23个字符内容：" << e.timestamp << endl;
		cout << "这一行的内容：" << e.content << endl;
	}
}