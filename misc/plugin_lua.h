#ifndef __MYLIBC_PLUGIN_LUA_H__
#define __MYLIBC_PLUGIN_LUA_H__

void load_lua_func(lua_State *L, const char *table, const char *func);
void dump_lua_stack(lua_State *L);

#endif
