#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <nan.h>

extern "C" {
    #include "../yespower-c/yespower.h"
}

using namespace node;
using namespace Nan;
using namespace v8;

NAN_METHOD(yespower) {
    if(info.Length() < 1) {
        Nan::ThrowError("You must provide at least one argument.");
        return;
    }

    Local<Object> target = Nan::To<Object>(info[0]).ToLocalChecked();

    if(!node::Buffer::HasInstance(target)) {
        Nan::ThrowError("Argument should be a buffer object.");
        return;
    }

    char* input = node::Buffer::Data(target);
    uint32_t input_len = node::Buffer::Length(target);

    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();

    uint32_t N = 2048;

    if (info[1]->IsNumber()) {
        v8::Maybe<uint32_t> maybe_uint = info[1]->Uint32Value(context);
        if (maybe_uint.IsJust()) {
            N = maybe_uint.FromJust();
        }
    }

    uint32_t r = 32;

    if (info[2]->IsNumber()) {
        v8::Maybe<uint32_t> maybe_uint = info[2]->Uint32Value(context);
        if (maybe_uint.IsJust()) {
            r = maybe_uint.FromJust();
        }
    }

    char *pers;
    uint32_t pers_len = 0;

    if (info[3]->IsString()) {
        pers = (char*)*Nan::Utf8String(info[3]);
        pers_len = strlen(pers);
    }

    char output[32];

    yespower_hash(input, input_len, N, r, pers, pers_len, output);

    info.GetReturnValue().Set(Nan::CopyBuffer(output, 32).ToLocalChecked());
}

NAN_MODULE_INIT(init)
{
    NAN_EXPORT(target, yespower);
}

NAN_MODULE_WORKER_ENABLED(yespower, init);
