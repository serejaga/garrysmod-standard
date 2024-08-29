#pragma once

namespace FileSystem {
	/*
		filesystem.Exists: does something with given path actually exist
	*/

	LUA_FUNCTION(Exists) {
		const char* sPath = LUA->CheckString(1);

		LUA->PushBool(std::filesystem::exists(sPath));

		return 1;
	}

	/*
		filesystem.IsDirectory: returns whether given file is directory or not
	*/

	LUA_FUNCTION(IsDirectory) {
		const char* sPath = LUA->CheckString(1);

		LUA->PushBool(std::filesystem::exists(sPath) and std::filesystem::is_directory(sPath));

		return 1;
	}

	/*
		filesystem.IsEmpty: returns whether given file is empty or not
	*/

	LUA_FUNCTION(IsEmpty) {
		const char* sPath = LUA->CheckString(1);

		LUA->PushBool(std::filesystem::exists(sPath) and std::filesystem::is_empty(sPath));

		return 1;
	}

	/*
		filesystem.CreateDirectory: create directory with given name
	*/

	LUA_FUNCTION(CreateDirectory) {
		const char* sPath = LUA->CheckString(1);

		LUA->PushBool(std::filesystem::create_directory(sPath));

		return 1;
	}

	/*
		filesystem.CopyDirectory: copy directory with given path
	*/

	LUA_FUNCTION(CopyDirectory) {
		const char* sPath = LUA->CheckString(1);
		const char* sNew = LUA->CheckString(2);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		double nFlags = 0;

		if (LUA->IsType(3, Lua::Number))
			nFlags = LUA->GetNumber(3);

		std::filesystem::copy(sPath, sNew, (std::filesystem::copy_options)nFlags);

		LUA->PushBool(true);

		return 1;
	}

	/*
		filesystem.CopyFile: copy file with given path
	*/

	LUA_FUNCTION(CopyFile) {
		const char* sPath = LUA->CheckString(1);
		const char* sNew = LUA->CheckString(2);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		LUA->PushBool(std::filesystem::copy_file(sPath, sNew));

		return 1;
	}

	/*
		filesystem.Remove: remove given file/directory 
	*/

	LUA_FUNCTION(Remove) {
		const char* sPath = LUA->CheckString(1);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		LUA->PushBool(std::filesystem::remove(sPath));

		return 1;
	}

	/*
		filesystem.Rename: rename given path [ first argument ] with second argument
	*/

	LUA_FUNCTION(Rename) {
		const char* sPath = LUA->CheckString(1);
		const char* sNew = LUA->CheckString(2);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		std::filesystem::rename(sPath, sNew);

		LUA->PushBool(true);

		return 1;
	}

	/*
		filesystem.Resize: alter size of file
	*/

	LUA_FUNCTION(Resize) {
		const char* sPath = LUA->CheckString(1);
		const double nSize = LUA->CheckNumber(2);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		std::filesystem::resize_file(sPath, nSize);

		LUA->PushBool(true);

		return 1;
	}

	/*
		filesystem.GetSize: gets size of file with given path 
	*/

	LUA_FUNCTION(GetSize) {
		const char* sPath = LUA->CheckString(1);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushNumber(-1);

			return 1;
		}

		LUA->PushNumber(std::filesystem::file_size(sPath));

		return 1;
	}

	/*
		filesystem.GetTime: returns last time when file was modified
	*/

	LUA_FUNCTION(GetTime) {
		const char* sPath = LUA->CheckString(1);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		std::filesystem::file_time_type FileTime = std::filesystem::last_write_time(sPath);
		double nSeconds = std::chrono::duration_cast<std::chrono::microseconds>(FileTime.time_since_epoch()).count() / 1e6;

		LUA->PushNumber(nSeconds);

		return 1;
	}

	/* 
		filesystem.Iterate: used to iterate over contents of directory, listing files and directories at top level. 
			Second argument makes iteration recursive ( including all subdirectories )	
	*/

	LUA_FUNCTION(Iterate) {
		const char* sPath = LUA->CheckString(1);

		if (!std::filesystem::exists(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		bool bRecursive = false;

		if (LUA->IsType(2, Lua::Bool))
			bRecursive = LUA->GetBool(2);

		if (!std::filesystem::exists(sPath) or !std::filesystem::is_directory(sPath)) {
			LUA->PushBool(false);

			return 1;
		}

		LUA->CreateTable();

		int iLastIndex = 1;

		if (bRecursive) {
			for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator(sPath)) {
				LUA->PushNumber(iLastIndex);
				LUA->PushString(dirEntry.path().string().c_str());
				LUA->SetTable(-3);

				iLastIndex += 1;
			}
		}
		else {
			for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(sPath)) {
				LUA->PushNumber(iLastIndex);
				LUA->PushString(dirEntry.path().string().c_str());
				LUA->SetTable(-3);

				iLastIndex += 1;
			}
		}

		return 1;
	}
}