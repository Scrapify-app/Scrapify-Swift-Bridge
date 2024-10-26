#include <node.h>
#include <main.h>

namespace Bridge {
    void SearchProcessByPid(const v8::FunctionCallbackInfo<v8::Value> &args) {
        v8::Isolate *isolate = args.GetIsolate();
        const v8::Local<v8::Context> context = isolate->GetCurrentContext();

        const v8::Local<v8::Int32> pid = v8::Local<v8::Int32>::Cast(args[0]);
        const v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[1]);

        const auto processIcon = main::searchProcessIconByPid(pid->Value());

        v8::Local<v8::Value> argv[1] = {
            processIcon.isNone()
                ? static_cast<v8::Local<v8::Value>>(Null(isolate))
                : static_cast<v8::Local<v8::Value>>(v8::String::NewFromUtf8(
                    isolate, std::string(processIcon.get()).c_str()).ToLocalChecked())
        };

        cb->Call(context, Null(isolate), 2, argv).ToLocalChecked();
    }

    void Init(const v8::Local<v8::Object> exports) {
        NODE_SET_METHOD(exports, "searchProcessByPid", SearchProcessByPid);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Init);
}
