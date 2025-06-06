# 0xLLama
forked from
[《动手自制大模型推理框架》](https://l0kzvikuq0w.feishu.cn/docx/ZF2hd0xfAoaXqaxcpn2c5oHAnBc)

inspired by [CS336](https://github.com/stanford-cs336/spring2025-lectures/blob/e9cb2488fdb53ea37f0e38924ec3a1701925cef3/nonexecutable/2025%20Lecture%203%20-%20architecture.pdf)

## possible ToDo List:
1. 手写并优化一些**高性能算子(如SwiGlu)** (调优参考[LeetCUDA](https://github.com/xlite-dev/LeetCUDA))
2. 实现**int4量化**
3. 用**Triton**重构部分功能，并接入原框架
4. 增加一个**MoE** 模块，serve一些moe小模型
5. **Observability**  (没想好metric)   
6. GQA MQA
7. 微调
...

## 第三方依赖
> 借助企业级开发库，更快地搭建出大模型推理框架
1. google glog https://github.com/google/glog
2. google gtest https://github.com/google/googletest
3. sentencepiece https://github.com/google/sentencepiece
4. armadillo + openblas https://arma.sourceforge.net/download.html
5. Cuda Toolkit

