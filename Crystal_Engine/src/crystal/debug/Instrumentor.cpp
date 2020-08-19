#include "crystalpch.h"
#include "crystal/debug/Instrumentor.h"

namespace Crystal
{
	Instrumentor::Instrumentor()
	: currentSession(nullptr) 
	{
	
	}
	
	Instrumentor::~Instrumentor()
	{
		EndSession();
	}

	void Instrumentor::BeginSession(const string& name, const string& filepath)
	{
		lock_guard lock(mutex);

		if (currentSession)
		{
			if (Log::GetCoreLogger())
			{
				CRYSTAL_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, currentSession->name);
			}

			InternalEndSession();
		}

		outputStream.open(filepath);

		if (outputStream.is_open())
		{
			currentSession = new InstrumentationSession({ name });
			WriteHeader();
		}
		else
		{
			if (Log::GetCoreLogger())
			{
				CRYSTAL_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
			}
		}
	}

	void Instrumentor::EndSession()
	{
		lock_guard lock(mutex);
		InternalEndSession();
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		stringstream json;

		if (!firstProfile)
		{
			json << ",";
		}
		else
		{
			firstProfile = false;
		}

		json << setprecision(3) << fixed;
		json << "{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << result.elapsed.count() << ',';
		json << "\"name\":\"" << result.name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.threadID << ",";
		json << "\"ts\":" << result.start.count();
		json << "}";

		lock_guard lock(mutex);

		if (currentSession)
		{
			outputStream << json.str();
			outputStream.flush();
		}
	}

	void Instrumentor::WriteHeader()
	{
		outputStream << "{\"otherData\": {}, \"traceEvents\":[";
		outputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		outputStream << "]}";
		outputStream.flush();
	}

	void Instrumentor::InternalEndSession()
	{
		if (currentSession)
		{
			WriteFooter();
			outputStream.close();
			delete currentSession;
			currentSession = nullptr;
			firstProfile = true;
		}
	}
}