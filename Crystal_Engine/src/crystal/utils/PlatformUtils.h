#pragma once

#include <string>

using namespace std;

namespace Crystal
{
    class FileDialogs
    {
        public:

        // Return empty string if dialog is cancelled
        static string OpenFile(const char* filter);
        static string SaveFile(const char* filter);

    };
}
