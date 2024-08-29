#include "../main.h"

/* Connect with lua interface */
void Features::Push(ILuaBase* luaBase) {
	LuaBase = luaBase;

	luaBase->PushSpecial(Lua::SPECIAL_GLOB);
	{
		luaBase->CreateTable();
		{
			luaBase->CreateTable();
			{
				luaBase->PushCFunction(FileSystem::Exists);
				luaBase->SetField(-2, "Exists");

				luaBase->PushCFunction(FileSystem::IsDirectory);
				luaBase->SetField(-2, "IsDirectory");

				luaBase->PushCFunction(FileSystem::IsEmpty);
				luaBase->SetField(-2, "IsEmpty");

				luaBase->PushCFunction(FileSystem::CreateDirectory);
				luaBase->SetField(-2, "CreateDirectory");

				luaBase->PushCFunction(FileSystem::CopyDirectory);
				luaBase->SetField(-2, "CopyDirectory");

				luaBase->PushCFunction(FileSystem::CopyFile);
				luaBase->SetField(-2, "CopyFile");

				luaBase->PushCFunction(FileSystem::Remove);
				luaBase->SetField(-2, "Remove");

				luaBase->PushCFunction(FileSystem::Rename);
				luaBase->SetField(-2, "Rename");

				luaBase->PushCFunction(FileSystem::Resize);
				luaBase->SetField(-2, "Resize");

				luaBase->PushCFunction(FileSystem::GetSize);
				luaBase->SetField(-2, "GetSize");

				luaBase->PushCFunction(FileSystem::GetTime);
				luaBase->SetField(-2, "GetTime");

				luaBase->PushCFunction(FileSystem::Iterate);
				luaBase->SetField(-2, "Iterate");

				luaBase->PushString(std::filesystem::current_path().string().c_str());
				luaBase->SetField(-2, "BASE");
			}
			luaBase->SetField(-2, "filesystem");

			luaBase->CreateTable();
			{
				luaBase->PushCFunction(FileStream::Write);
				luaBase->SetField(-2, "Write");

				luaBase->PushCFunction(FileStream::Read);
				luaBase->SetField(-2, "Read");

				luaBase->PushCFunction(FileStream::IsGood);
				luaBase->SetField(-2, "IsGood");

				luaBase->PushCFunction(FileStream::GetSize);
				luaBase->SetField(-2, "GetSize");
			}
			luaBase->SetField(-2, "filestream");
		}
		luaBase->SetField(-2, "std");
	} 
	luaBase->Pop();
}