#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace synonms
{
    namespace gfx
    {
        namespace utilities
        {
            class StringExtensions
            {
            public:
                // trim from start (in place)
                static inline void LeftTrim(std::string& s) 
                {
                    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                        return !std::isspace(ch);
                    }));
                }

                // trim from end (in place)
                static inline void RightTrim(std::string& s) 
                {
                    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                        return !std::isspace(ch);
                    }).base(), s.end());
                }

                // trim from both ends (in place)
                static inline void Trim(std::string& s) 
                {
                    LeftTrim(s);
                    RightTrim(s);
                }

                // trim from start (copying)
                static inline std::string LeftTrimCopy(std::string s) 
                {
                    LeftTrim(s);
                    return s;
                }

                // trim from end (copying)
                static inline std::string RightTrimCopy(std::string s) 
                {
                    RightTrim(s);
                    return s;
                }

                // trim from both ends (copying)
                static inline std::string TrimCopy(std::string s) 
                {
                    Trim(s);
                    return s;
                }

                static inline std::vector<std::string> Tokenise(const std::string& line, char separator)
                {
                    std::vector<std::string> tokens;
                    std::stringstream stream(line);
                    std::string token;

                    while (std::getline(stream, token, separator))
                    {
                        tokens.push_back(token);
                    }

                    return tokens;
                }
            };
        }
    }
}