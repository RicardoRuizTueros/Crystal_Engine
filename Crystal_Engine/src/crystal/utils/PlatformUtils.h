#pragma once

#include <string>
#include <optional>

using namespace std;

namespace Crystal
{
    class FileDialogs
    {
        public:

        static optional<string> OpenFile(const char* filter);
        static optional<string> SaveFile(const char* filter);

    };
}
