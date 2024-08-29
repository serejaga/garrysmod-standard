#pragma once

#define GMOD_MODULE_OPEN()                                  \
            int gmod13_open__Imp( ILuaBase* LUA );          \
            DLL_EXPORT int gmod13_open( LuaState* L )  \
            {                                               \
                return gmod13_open__Imp( L->base );         \
            }                                               \
            int gmod13_open__Imp( ILuaBase* LUA )

#define GMOD_MODULE_CLOSE()                                 \
            int gmod13_close__Imp( ILuaBase* LUA );         \
            DLL_EXPORT int gmod13_close( LuaState* L ) \
            {                                               \
                return gmod13_close__Imp( L->base );        \
            }                                               \
            int gmod13_close__Imp( ILuaBase* LUA )

#define LUA_FUNCTION( FUNC )                                \
            static int FUNC##__Imp( ILuaBase* LUA );        \
            static int FUNC( LuaState* L )                  \
            {                                               \
                ILuaBase* LUA = L->base;                    \
                LUA->SetState(L);                           \
                return FUNC##__Imp( LUA );                  \
            }                                               \
            static int FUNC##__Imp( ILuaBase* LUA )
