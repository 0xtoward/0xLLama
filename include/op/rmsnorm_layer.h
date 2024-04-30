#ifndef LC_INCLUDE_OP_RMSNORM_LAYER_H_
#define LC_INCLUDE_OP_RMSNORM_LAYER_H_
#include "layer.h"
namespace op {
class RmsNormLayer : public LayerFp32Param {
 public:
  explicit RmsNormLayer(int32_t dim);

  base::Status check() override;

  base::Status forward() override;
 private:
  int32_t dim_ = 0;
};
}  // namespace op
#endif  // LC_INCLUDE_OP_RMSNORM_LAYER_H_
