#ifndef KUIPER_INCLUDE_MODEL_LLAMA_H_
#define KUIPER_INCLUDE_MODEL_LLAMA_H_
#include <map>
#include "model.h"
#include "op/add.h"
#include "op/embedding.h"
#include "op/rope.h"
#include "op/swiglu.h"
namespace model {

struct EmbeddingOutput {
  tensor::Tensor input_tokens;
  tensor::Tensor input_embeddings;
  tensor::Tensor input_token_num;
};

class LLama2Model : public Model {
 public:
  explicit LLama2Model(std::string token_path, std::string model_path);

  base::Status init(base::DeviceType device_type) override;

  base::Status forward(const std::vector<int>& tokens, int32_t total_steps) override;

  std::vector<int32_t> encode(const std::string& sentence) override;

  std::pair<tensor::Tensor, tensor::Tensor> slice_kv_cache(int32_t layer_idx,
                                                           int32_t token_pos) override;

 private:
  void init_mem() override;

  base::Status create_layers() override;

  void create_rope_layer();

  void create_add_layer();

  void create_mha_layers();

  void create_rmsnorm_layers();

  void create_embedding_layer();

  void create_matmul_layers();

  void create_swiglu_layer();

  void attention_mha_o(int32_t layer_idx, int32_t pos);

  EmbeddingOutput prepare_input(const std::vector<int>& tokens);

  void attn_rmsnorm(const tensor::Tensor& input, int32_t layer_idx);

  void feed_forward(const tensor::Tensor& input, int32_t layer_idx);

  void fill_input(int32_t pos, int32_t next, const std::vector<int32_t>& tokens,
                  tensor::Tensor& input, const EmbeddingOutput& embedding_output);

  void attention_qkv(int32_t layer_idx, int32_t pos, const tensor::Tensor& pos_tensor);

 private:
  std::shared_ptr<op::VecAddLayer> add_layer_;
  std::shared_ptr<op::RoPELayer> rope_layer_;
  std::shared_ptr<op::SwiGLULayer> swiglu_layer_;

  std::vector<std::shared_ptr<op::MultiHeadAttention>> mha_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> wq_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> wk_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> wv_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> wo_layers_;

  std::vector<std::shared_ptr<op::MatmulLayer>> w1_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> w2_layers_;
  std::vector<std::shared_ptr<op::MatmulLayer>> w3_layers_;
  std::shared_ptr<op::MatmulLayer> cls_layer_;

  std::shared_ptr<op::EmbeddingLayer> embedding_layer_;
  std::vector<std::shared_ptr<op::RmsNormLayer>> rmsnorm_layers_;
};
}  // namespace model

#endif