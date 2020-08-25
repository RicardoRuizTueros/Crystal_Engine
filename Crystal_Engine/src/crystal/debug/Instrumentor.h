#pragma once

#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>

#include "crystal/core/Log.h"

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
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		~Instrumentor();

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

	namespace InstrumentorUtils
	{
		template <size_t N>
		struct ChangeResult
		{
			char data[N];
		};

		template <size_t N, size_t K>

		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
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
	#elif defined(__FUNCSIG__) || (_MSC_VER)
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
	#define CRYSTAL_PROFILE_SCOPE(name) CRYSTAL_PROFILE_SCOPE_LINE(name, __LINE__)
	#define CRYSTAL_PROFILE_SCOPE_LINE(name, line) constexpr auto fixedName##line = ::Crystal::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												   ::Crystal::InstrumentationTimer timer##line(fixedName##line.data)

	#define CRYSTAL_PROFILE_FUNCTION() CRYSTAL_PROFILE_SCOPE(CRYSTAL_FUNC_SIG)
#else
	#define CRYSTAL_PROFILE_BEGIN_SESSION(name, filepath)
	#define CRYSTAL_PROFILE_END_SESSION()
	#define CRYSTAL_PROFILE_SCOPE(name)
	#define CRYSTAL_PROFILE_FUNCTION()
#endif
