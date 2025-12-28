#include <iostream>
#include "lua.hpp"

int main(int argc, char **argv) {
    std::cout << "hello world!" << std::endl;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    const char* script = "print('Hello LuaJIT! Version:'..jit.version)";
    if (luaL_dostring(L, script)) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
    }
    lua_close(L);
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}