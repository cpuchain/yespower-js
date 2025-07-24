#include <napi.h>

extern "C" {
    #include "../yespower-c/yespower.h"
}

Napi::Value YespowerFunc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Check input buffer
    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "First argument must be a Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    // Input buffer
    char* input = reinterpret_cast<char*>(info[0].As<Napi::Buffer<char>>().Data());
    uint32_t input_len = info[0].As<Napi::Buffer<char>>().Length();

    // Optional N (default: 2048)
    uint32_t N = 2048;
    if (info.Length() > 1 && info[1].IsNumber()) {
        N = info[1].As<Napi::Number>().Uint32Value();
    }

    // Optional r (default: 32)
    uint32_t r = 32;
    if (info.Length() > 2 && info[2].IsNumber()) {
        r = info[2].As<Napi::Number>().Uint32Value();
    }

    // Optional pers (default: null)
    char* pers = nullptr;
    uint32_t pers_len = 0;
    if (info.Length() > 3 && info[3].IsString()) {
        std::string jsStr = info[3].As<Napi::String>();

        pers = (char*)std::malloc(jsStr.length() + 1);
        std::strcpy(pers, jsStr.c_str());
        pers_len = jsStr.size();
    }

    const char* output = yespower_wasm(input, input_len, N, r, pers, pers_len);

    return Napi::Buffer<char>::Copy(env, output, 32);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("yespower", Napi::Function::New(env, YespowerFunc));
    return exports;
}

NODE_API_MODULE(yespower, Init)
