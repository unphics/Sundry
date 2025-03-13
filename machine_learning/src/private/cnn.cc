#include "cnn.hh"

using namespace ::std;

conv2d::conv2d(int in_ch, int out_ch, int k_size): in_ch(in_ch), out_ch(out_ch), k_size(k_size) {
    // 初始化卷积核和偏执
    kernels = tensor3d(in_ch, vector<vector<float>>(k_size, vector<float>(k_size, 0.0f)));
    biases = vector<float>(out_ch, 0.0f);
}