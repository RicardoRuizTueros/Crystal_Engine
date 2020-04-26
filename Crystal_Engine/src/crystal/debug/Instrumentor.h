#pragma once

#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

namespace Crystal
{
	using floatingPointMicroseconds = chrono::duration<double, micro>;

	struct ProfileResult
	{
		string name;
		floatingPointMicroseconds start;
		chrono::microseconds elapsed;
		thread::id threadID;
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
		mutex mutex;
	
	public:
		Instrumentor();

		void BeginSession(const string& name, const string& filepath = "results.json");
		void EndSession();
		void WriteProfile(const ProfileResult& result);
	
		static inline Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		bool firstProfile;

		void WriteHeader();
		void WriteFooter();
		void InternalEndSession();
	};
}

#define CRYSTAL_PROFILE 1

// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!

#if CRYSTAL_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define CRYSTAL_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define CRYSTAL_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define CRYSTAL_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define CRYSTAL_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define CRYSTAL_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define CRYSTAL_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define CRYSTAL_FUNC_SIG __func__
	#else
		#define CRYSTAL_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif
#endif

#if CRYSTAL_PROFILE
	#define CRYSTAL_PROFILE_BEGIN_SESSION(name, filepath) ::Crystal::Instrumentor::Get().BeginSession(name, filepath)
	#define CRYSTAL_PROFILE_END_SESSION() ::Crystal::Instrumentor::Get().EndSession()
	#define CRYSTAL_PROFILE_SCOPE(name) ::Crystal::InstrumentationTimer timer##__LINE__(name);
	#define CRYSTAL_PROFILE_FUNCTION() CRYSTAL_PROFILE_SCOPE(CRYSTAL_FUNC_SIG)
#else
	#define CRYSTAL_PROFILE_BEGIN_SESSION(name, filepath)
	#define CRYSTAL_PROFILE_END_SESSION()
	#define CRYSTAL_PROFILE_SCOPE(name)
	#define CRYSTAL_PROFILE_FUNCTION()
#endif