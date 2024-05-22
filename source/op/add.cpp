#include "op/add.h"
#include "op/layer.h"
namespace op {
VecAddLayer::VecAddLayer() : Layer(LayerType::kLayerAdd, "Add") {
}

base::Status VecAddLayer::check() const {
  auto status = check_inout(2, 1, base::DeviceType::kDeviceCPU, base::DataType::kDataTypeFp32);
  if (get_input(0).size() != get_input(1).size()) {
    return base::error::InternalError("The input size of two tensors are not match.");
  }
  if (get_input(0).size() != get_output(0).size()) {
    return base::error::InternalError("The input and output size are not match.");
  }
  return base::error::Success();
}

base::Status VecAddLayer::base_forward() {
  auto status = this->check();
  if (!status) {
    return status;
  }
  auto input1 = this->get_input(0);
  auto input2 = this->get_input(1);
  auto output = this->get_output(0);
  arma::fvec input_vec1(input1.ptr<float>(), input1.size(), false, true);
  arma::fvec input_vec2(input2.ptr<float>(), input2.size(), false, true);
  arma::fvec output_vec(output.ptr<float>(), output.size(), false, true);

  output_vec = input_vec1 + input_vec2;
  return base::error::Success();
}

}  // namespace op