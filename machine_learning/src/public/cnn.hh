#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <memory>

// 张量类型
using tensor3d = ::std::vector<::std::vector<::std::vector<float>>>;

// 卷积层
class conv2d {
public:
    conv2d(int in_ch, int out_ch, int k_size);
private:
    int in_ch;
    int out_ch;
    int k_size;
    tensor3d kernels;
    ::std::vector<float> biases;
};