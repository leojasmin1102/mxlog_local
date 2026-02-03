#include <drogon/drogon.h>

int main() {
    drogon::app()
        .registerHandler("/", [](const drogon::HttpRequestPtr&,
                                 std::function<void(const drogon::HttpResponsePtr&)>&& cb) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setBody("Hello Drogon + VS!");
            cb(resp);
        })
        .addListener("0.0.0.0", 8080)
        .run();
}
