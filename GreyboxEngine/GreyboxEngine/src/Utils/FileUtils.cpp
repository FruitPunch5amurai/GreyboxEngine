#include "gbepch.h"
#include "Utils/FileUtils.h"

#include <filesystem>
#include <fstream>

#include "Logging/Logging.h"

namespace GreyboxEngine
{
    std::string FileUtils::ReadFromFile(const std::string& filepath)
    {
        std::string contents;
        std::ifstream file;
        // ensure ifstream objects can throw exceptions:
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            namespace fs = std::filesystem;
            
            fs::path executablePath = fs::current_path();
            
            fs::path fullPath = executablePath / filepath;
            if (!fs::exists(fullPath)) {
                GBE_CORE_ERROR("Filepath {0} does not exist!", fullPath.string());
                return "";
            }
            file.open(fullPath);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            contents = stream.str();
        }
        catch(std::ifstream::failure& e)
        {
            GBE_CORE_ERROR("Failed to read file {0}", filepath);
        }

        return contents;
    }
}
