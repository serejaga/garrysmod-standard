#pragma once

/* Enums */
namespace Lua {
	enum Special {
		SPECIAL_GLOB,
		SPECIAL_ENV,
		SPECIAL_REG
	};

	enum Type {
		None = -1,
		Nil,
		Bool,
		LightUserData,
		Number,
		String,
		Table,
		Function,
		UserData,
		Thread,

		Entity,
		Vector,
		Angle,
		PhysObj,
		Save,
		Restore,
		DamageInfo,
		EffectData,
		MoveData,
		RecipientFilter,
		UserCmd,
		ScriptedVehicle,
		Material,
		Panel,
		Particle,
		ParticleEmitter,
		Texture,
		UserMsg,
		ConVar,
		IMesh,
		Matrix,
		Sound,
		PixelVisHandle,
		DLight,
		Video,
		File,
		Locomotion,
		Path,
		NavArea,
		SoundHandle,
		NavLadder,
		ParticleSystem,
		ProjectedTexture,
		PhysCollide,
		SurfaceInfo,

		Type_Count
	};
}

/* Lua State */
class ILuaBase;

struct LuaState {
	unsigned char header[114];
	ILuaBase* base;
};

typedef int (*CFunc) (LuaState* L);

/* Lua Interface */
struct UserData {
	void* data;
	unsigned char type;
};

class ILuaBase {
public:
	LuaState* GetLuaState() { return *reinterpret_cast<LuaState**>(this + 1); }

	virtual int	Top(void) = 0;
	virtual void Push(int iStackPos) = 0;
	virtual void Pop(int iAmt = 1) = 0;
	virtual void GetTable(int iStackPos) = 0;
	virtual void GetField(int iStackPos, const char* strName) = 0;
	virtual void SetField(int iStackPos, const char* strName) = 0;
	virtual void CreateTable() = 0;
	virtual void SetTable(int i) = 0;
	virtual void SetMetaTable(int i) = 0;
	virtual bool GetMetaTable(int i) = 0;
	virtual void Call(int iArgs, int iResults) = 0;
	virtual int PCall(int iArgs, int iResults, int iErrorFunc) = 0;
	virtual int	Equal(int iA, int iB) = 0;
	virtual int	RawEqual(int iA, int iB) = 0;
	virtual void Insert(int iStackPos) = 0;
	virtual void Remove(int iStackPos) = 0;
	virtual int Next(int iStackPos) = 0;
	virtual void* NewUserdata(unsigned int iSize) = 0;
	virtual void ThrowError(const char* strError) = 0;
	virtual void CheckType(int iStackPos, int iType) = 0;
	virtual void ArgError(int iArgNum, const char* strMessage) = 0;
	virtual void RawGet(int iStackPos) = 0;
	virtual void RawSet(int iStackPos) = 0;
	virtual const char* GetString(int iStackPos = -1, unsigned int* iOutLen = 0) = 0;
	virtual double GetNumber(int iStackPos = -1) = 0;
	virtual bool GetBool(int iStackPos = -1) = 0;
	virtual CFunc GetCFunction(int iStackPos = -1) = 0;
	virtual void* GetUserdata(int iStackPos = -1) = 0;
	virtual void PushNil() = 0;
	virtual void PushString(const char* val, unsigned int iLen = 0) = 0;
	virtual void PushNumber(double val) = 0;
	virtual void PushBool(bool val) = 0;
	virtual void PushCFunction(CFunc val) = 0;
	virtual void PushCClosure(CFunc val, int iVars) = 0;
	virtual void PushUserdata(void*) = 0;
	virtual int	ReferenceCreate() = 0;
	virtual void ReferenceFree(int i) = 0;
	virtual void ReferencePush(int i) = 0;
	virtual void PushSpecial(int iType) = 0;
	virtual bool IsType(int iStackPos, int iType) = 0;
	virtual int	GetType(int iStackPos) = 0;
	virtual const char* GetTypeName(int iType) = 0;
	virtual void CreateMetaTableType(const char* strName, int iType) = 0;
	virtual const char* CheckString(int iStackPos = -1) = 0;
	virtual double CheckNumber(int iStackPos = -1) = 0;
	virtual int	ObjLen(int) = 0;
	virtual void* GetAngle(int) = 0;
	virtual void* GetVector(int) = 0;
	virtual int PushAngle(void*) = 0;
	virtual int	PushVector(void*) = 0;
	virtual int	SetState(LuaState*) = 0;
	virtual int	CreateMetaTable(const char*) = 0;
	virtual char PushMetaTable(int) = 0;
	virtual int	PushUserType(void*, int) = 0;
	virtual void** SetUserType(int, void*) = 0;

public:
	template <class T>
	T* GetUserType(int iStackPos, int iType) {
		auto* ud = static_cast<UserData*>(GetUserdata(iStackPos));

		if (ud == nullptr || ud->data == nullptr || ud->type != iType)
			return nullptr;

		return static_cast<T*>(ud->data);
	}

	template <typename T>
	T* NewUserType(int iType) {
		UserData* ud = static_cast<UserData*>(NewUserdata(sizeof(UserData) + sizeof(T)));
		if (ud == nullptr)
			return nullptr;

		T* data = reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(ud) + sizeof(UserData));
		ud->data = new(data) T;
		ud->type = static_cast<unsigned char>(iType);

		return data;
	}

	template <class T>
	void PushUserType_Value(const T& val, int iType) {
		using UserData_T = UserData_Value<T>;

		auto* ud = static_cast<UserData_T*>(NewUserdata(sizeof(UserData_T)));
		ud->data = new(&ud->value) T(val);
		ud->type = iType;

		if (PushMetaTable(iType))
			SetMetaTable(-2);
	}

protected:
	template <class T>
	struct UserData_Value : UserData {
		T value;
	};
};