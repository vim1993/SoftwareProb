#ifndef YY_M_LUA_H
#define YY_M_LUA_H
#include "yy_f_alloc.h"


#ifndef YY_ENV_NOT_M_LUA

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lstate.h"
#include "yy_e_uri_parser.h"
#include "yy_e_http_parser.h"

#if defined(WIN32)
#pragma comment( lib, "lua.lib" )
#endif

typedef struct lua_State yy_m_lua_ctx_t;

extern yy_m_lua_ctx_t *yy_m_lua_open();
extern int yy_m_lua_close(yy_m_lua_ctx_t *ctx);

#define yy_m_lua_dostring 			luaL_dostring 
#define yy_m_lua_getglobal 			lua_getglobal 
#define yy_m_lua_pushlightuserdata 	lua_pushlightuserdata
#define yy_m_lua_pcall				lua_pcall
#define yy_m_lua_isboolean			lua_isboolean
#define yy_m_lua_toboolean			lua_toboolean
#define yy_m_lua_pop				lua_pop
#define yy_m_lua_register			lua_register
#define yy_m_lua_isstring			lua_isstring
#define yy_m_lua_tostring			lua_tostring

extern void yy_m_lua_test();


#endif//YY_ENV_NOT_M_LUA

#endif
