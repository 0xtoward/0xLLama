#include <glog/logging.h>
#include <iostream>
#include <memory>
#include "base/alloc.h"
#include "base/buffer.h"
#include "model/llama2.h"
#include "tensor/tensor.h"

int main() {
  std::shared_ptr<base::CPUDeviceAllocator> alloc = std::make_shared<base::CPUDeviceAllocator>();
  //  Tensor tensor(DataType::kDataTypeFp32, 1, 2, 3, 4);
  //  tensor.allocate(alloc);
  //  tensor.allocate(alloc);
  //
  //  tensor.reset(DataType::kDataTypeFp32, {4, 5, 6});
  //  tensor.allocate(alloc);
  //
  //  tensor.reshape({11, 12, 13});
  //  const auto& strides = tensor.strides();

  char* checkpoint_path = "/home/fss/big_model/llama2_7b.bin";  // e.g. out/model.bin
  char* tokenizer_path = "/home/fss/big_model/tokenizer.model";
  model::LLama2Model model(tokenizer_path, checkpoint_path);
  model.init(base::DeviceType::kDeviceCPU);
  std::string sentence = "Hi everyone";
  const auto& tokens = model.encode(sentence);
  const auto s = model.forward(tokens, 0);

  LOG(INFO) << s;
  return 0;
}