#include "crystalpch.h"
#include "crystal/debug/Instrumentor.h"

namespace Crystal
{
	Instrumentor::Instrumentor()
		: currentSession(nullptr), profileCount(0)
	{

	}

	void Instrumentor::BeginSession(const string& name, const string& filepath)
	{
		outputStream.open(filepath);
		WriteHeader();
		currentSession = new InstrumentationSession{ name };
	}

	void Instrumentor::EndSession()
	{
		WriteFooter();
		outputStream.close();
		delete currentSession;
		currentSession = nullptr;
		profileCount = 0;
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		if (profileCount++ > 0)
			outputStream << ",";

		string name = result.name;
		replace(name.begin(), name.end(), '"', '\'');

		outputStream << "{";
		outputStream << "\"cat\":\"function\",";
		outputStream << "\"dur\":" << (result.end - result.start) << ',';
		outputStream << "\"name\":\"" << name << "\",";
		outputStream << "\"ph\":\"X\",";
		outputStream << "\"pid\":0,";
		outputStream << "\"tid\":" << result.threadID << ",";
		outputStream << "\"ts\":" << result.start;
		outputStream << "}";

		outputStream.flush();
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
}