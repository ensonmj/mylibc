#include <stdio.h>
#include "misc.h"

#ifdef TEST_SORT
#include "sort.h"
#endif

#ifdef TEST_LUA
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "plugin_lua.h"
#endif

int main(int argc, char *argv[])
{
#ifdef TEST_SORT
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int cnt = sizeof(arr)/sizeof(int);
    printf("orig array:");
    print_arr(arr, cnt);

    heap_sort_ascend(arr, sizeof(arr)/sizeof(int));
    printf("heap ascend sort:");
    print_arr(arr, sizeof(arr)/sizeof(int));

    int arr1[] = {49, 38, 65, 97, 76, 13, 27, 49};
    heap_sort_descend(arr1, sizeof(arr1)/sizeof(int));
    printf("heap descend sort:");
    print_arr(arr1, sizeof(arr1)/sizeof(int));
#endif

#ifdef TEST_LUA
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);
    // print lua version
    lua_getglobal(L, "_VERSION");
    const char *ver = luaL_checkstring(L, -1);
    printf("%s\n", ver);
    // pop the _VERSION
    lua_pop(L, 1);

    // load and run the plugin script
    if(luaL_dofile(L, "plugin.lua")) {
        printf("load and run plugin.lua error");
        return 1;
    }

    // load function from lua
    load_lua_func(L, "Test", "hello");
    // exec the function
    lua_pcall(L, 0, 0, 0);
#endif

    //getchar();

    return 0;
}
