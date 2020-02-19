#pragma once

#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

namespace Crystal
{
	struct ProfileResult
	{
		string name;
		long long start, end;
		uint32_t threadID;
	};

	struct InstrumentationSession
	{
		string name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* currentSession;
		ofstream outputStream;
		int profileCount;
	
	public:
		Instrumentor();

		void BeginSession(const string& name, const string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileResult& result);
		void WriteHeader();
		void WriteFooter();

		static inline Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};
}

#define CRYSTAL_PROFILE 1

#if CRYSTAL_PROFILE
	#define CRYSTAL_PROFILE_BEGIN_SESSION(name, filepath) ::Crystal::Instrumentor::Get().BeginSession(name, filepath)
	#define CRYSTAL_PROFILE_END_SESSION() ::Crystal::Instrumentor::Get().EndSession()
	#define CRYSTAL_PROFILE_SCOPE(name) ::Crystal::InstrumentationTimer timer##__LINE__(name);
	#define CRYSTAL_PROFILE_FUNCTION() CRYSTAL_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define CRYSTAL_PROFILE_BEGIN_SESSION(name, filepath)
	#define CRYSTAL_PROFILE_END_SESSION()
	#define CRYSTAL_PROFILE_SCOPE(name)
	#define CRYSTAL_PROFILE_FUNCTION()
#endif