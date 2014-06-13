#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void load_lua_func(lua_State *L, const char *table, const char *func)
{
    lua_getglobal(L, table);
    lua_pushstring(L, func);
    lua_gettable(L, -2);
    //remove table from stack
    lua_remove(L, -2);
}

void dump_lua_stack(lua_State *L)
{
    int top=lua_gettop(L);

    printf("dumpstack -- BEGIN\n");
    for(int i=1; i<=top; i++) {
        printf("%d\t%s\t",i,luaL_typename(L,i));
        switch (lua_type(L, i)) {
            case LUA_TNUMBER:
                printf("%g\n",lua_tonumber(L,i));
                break;
            case LUA_TSTRING:
                printf("%s\n",lua_tostring(L,i));
                break;
            case LUA_TBOOLEAN:
                printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
                break;
            case LUA_TNIL:
                printf("%s\n", "nil");
                break;
            case LUA_TTHREAD: {
                lua_State *pThread = lua_tothread(L, i);
                if (pThread) {
                    if (pThread == L) {
                        printf("running\n");
                    } else {
#if LUA_VER >= 511
                        switch (lua_status(pThread)) {
                            case LUA_YIELD:
                                printf("suspended\n");
                                break;
                            case 0:
                                lua_Debug ar;
                                if (lua_getstack(pThread, 0, &ar) > 0)
                                    printf("normal\n");
                                else if (lua_gettop(pThread) == 0)
                                    printf("dead\n");
                                else
                                    printf("suspended\n");
                                break;
                            default: printf("dead\n"); break;
                        }
#else
                        lua_Debug ar;
                        if((lua_getstack(pThread, 0, &ar) == 0)
                                && (lua_gettop(pThread) == 0))
                            printf("dead\n");
                        else
                            printf("suspended\n");
#endif
                    }
                }
                break;
            }
            default:
                printf("%p\n",lua_topointer(L,i));
                break;
        }
    }
    printf("dumpstack -- END\n");
}
