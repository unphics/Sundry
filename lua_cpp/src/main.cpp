#include <iostream>

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int ctest(lua_State *L) {
    // std::cout << "ctest" << std::endl;
    size_t len;
    const char *str = lua_tolstring(L, 1, &len);
    std::cout << "lua string: " << str << std::endl;
    float num = lua_tonumber(L, 2);
    std::cout << "lua number: " << num << std::endl;
    bool b = lua_toboolean(L, 3);
    std::cout << "lua boolean: " << b << std::endl;
    return 0;
}

int ctestarr(lua_State *L) {
    // std::cout << "ctestarr" << std::endl;
    int len = lua_rawlen(L, 1);
    for (int i = 1; i <= len; ++i) {
        lua_pushnumber(L, i); // 2 or -1
        lua_gettable(L, 1); // pop index -> push table[i]
        const char* str = lua_tolstring(L, -1, nullptr);
        std::cout << "ctestarr: " << str << std::endl;
        lua_pop(L, 1); // 这里的1是移除元素的个数
    }
    return 0;
}

int ctestmap(lua_State *L) {
#if 0
    lua_pushnil(L);
    while(lua_next(L, 1) != 0) {
        // push key, push value
        printf("key = %s, value = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        lua_pop(L, 1); // lua_next的调用会每次自己pop掉key, 所以value要自己处理pop掉
    }
#else
    luaL_checktype(L, 1, LUA_TTABLE);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        printf("param 2 is not a number\n");
    } 
    lua_getfield(L, 1, "name");
    printf("name = %s\n", lua_tostring(L, -1));
#endif
    return 0;
}

int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;

    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaopen_string(L);
    luaopen_table(L);

    lua_register(L, "ctest", &ctest);
    lua_register(L, "ctestarr", &ctestarr);
    lua_register(L, "ctestmap", &ctestmap);
    
    if (luaL_loadfile(L, "./script/main.lua")) {
        const char *error = lua_tostring(L, -1);
        ::std::cout << "lua load file error: " << error << std::endl;
        return -1;
    }

    if (lua_pcall(L, 0, 0, 0)) {
        const char *error = lua_tostring(L, -1);
        ::std::cout << "lua pcall error: " << error << std::endl;
        return -1;
    }
    
    return 0;
}
