#ifndef lexer_hh
#define lexer_hh

#include <string>
#include <memory>

enum class token_kind {
    add,
    sub,
    mul,
    div,
};

struct token {
    token_kind kind;
    int value;
    ::std::string content;
};

class lexer {
public:
    lexer(const char *code);
    void get_next_token();
    void get_next_char();
private:
    ::std::string src_code;
    ::std::shared_ptr<token> cur_token;
    char cur_char {'0'};
    int cursor {0};
};

#endif // lexer_hh