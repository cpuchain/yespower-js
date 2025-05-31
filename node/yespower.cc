#include <nan.h>

extern "C" {
    #include "../yespower-c/yespower.h"
}

NAN_METHOD(yespower) {
    if (info.Length() < 1 || !node::Buffer::HasInstance(info[0])) {
        return Nan::ThrowTypeError("First argument must be a Buffer");
    }

    // Input buffer
    char* input = node::Buffer::Data(info[0]);
    uint32_t input_len = node::Buffer::Length(info[0]);

    // Optional N (default: 2048)
    uint32_t N = 2048;

    if (info.Length() > 1 && info[1]->IsUint32()) {
        N = Nan::To<uint32_t>(info[1]).FromJust();
    }

    // Optional r (default: 32)
    uint32_t r = 32;

    if (info.Length() > 2 && info[2]->IsUint32()) {
        r = Nan::To<uint32_t>(info[2]).FromJust();
    }

    // Optional pers (default: null)
    char* pers = nullptr;
    uint32_t pers_len = 0;

    if (info.Length() > 3 && info[3]->IsString()) {
        pers = (char*)*Nan::Utf8String(info[3]);
        pers_len = strlen(pers);
    }

    char output[32];

    yespower_hash(input, input_len, N, r, pers, pers_len, output);

    info.GetReturnValue().Set(Nan::CopyBuffer(output, 32).ToLocalChecked());
}

NAN_MODULE_INIT(init) {
    Nan::Export(target, "yespower", yespower);
}

NODE_MODULE(yespower, init)
