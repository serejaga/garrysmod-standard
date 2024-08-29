#pragma once

namespace FileStream {
	inline int iMetaIndex = 0;

	/*
		filestream.Read: return file contents
	*/

	LUA_FUNCTION(Read) {
		const char* path = LUA->CheckString(1);

		std::ifstream file;
		file.open(path, std::ios_base::binary | std::ios_base::ate);

		if (!file.good()) {
			LUA->PushBool(false);

			return 1;
		}

		std::streampos streamSize = file.tellg();

		if (streamSize == 0) {
			LUA->PushBool(true);
			LUA->PushString("");
			LUA->PushNumber(0);

			return 3;
		}

		char* buffer = new char[streamSize] {0};
		file.seekg(std::ios::beg);
		file.read(buffer, streamSize);
		file.close();

		LUA->PushBool(true);
		LUA->PushString(buffer, streamSize);
		LUA->PushNumber(streamSize);

		delete[] buffer;

		return 3;
	}

	/*
		filestream.Write: write file with given contents
	*/

	LUA_FUNCTION(Write) {
		const char* path = LUA->CheckString(1);
		const char* content = LUA->CheckString(2);

		std::ofstream file;
		file.open(path, std::ios_base::binary);

		if (!file.good()) {
			LUA->PushBool(false);

			return 1;
		}

		unsigned int size = strlen(content);

		file.write(content, size);
		file.close();

		LUA->PushBool(true);
		LUA->PushNumber(size);

		return 2;
	}

	/*
		filestream.GetSize: return size of file with given path 
	*/

	LUA_FUNCTION(GetSize) {
		const char* path = LUA->CheckString(1);

		std::ifstream file;
		file.open(path, std::ios_base::binary | std::ios_base::ate);

		if (!file.good()) {
			LUA->PushNumber(0);

			return 1;
		}

		std::streampos streamSize = file.tellg();
		file.close();

		LUA->PushNumber(streamSize);

		return 1;
	}

	/*
		filestream.IsGood:  returns whether given file is good or bad
	*/

	LUA_FUNCTION(IsGood) {
		const char* path = LUA->CheckString(1);

		std::ifstream file(path);

		const bool bIsGood = file.good();
		file.close();

		LUA->PushBool(bIsGood);

		return 1;
	}
}