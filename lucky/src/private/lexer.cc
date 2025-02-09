#include "lexer.hh"

#include <cstring>

lexer::lexer(const char *code) {
    this->src_code = code;

}

void lexer::get_next_token() {
    // 1. 跳过空格字符
    while(::isspace(this->cur_char)) {
        this->get_next_char();
    }

    // todo https://www.bilibili.com/video/BV1pZ4y1S7Aj?t=1779.8
}

void lexer::get_next_char() {
    if (this->cursor == this->src_code.length()) {
        ::printf("error: end of code\n");
        ::exit(0);
    }
    this->cur_char = this->src_code[this->cursor];
}