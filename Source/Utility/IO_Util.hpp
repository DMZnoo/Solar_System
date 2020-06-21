//
//  IO_Util.hpp
//
//  Created by JINWOO LEE on 29/04/20.
//

#ifndef IO_Util_hpp
#define IO_Util_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <cstdlib>
extern std::string ROOT;
class IO_Util
{

    public:
        static std::string getFile(const std::string &filePath)
    {
        std::string code;
        std::stringstream sstr;
        
        std::ifstream fileStream(filePath);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Impossible to open.\n" + filePath);
        } else {
            sstr << fileStream.rdbuf();
            code = sstr.str();
            fileStream.close();
        }

        return code;
    }
    static std::string concat(std::string concat)
    {
        return ROOT + concat;
    }
    
    

};


#endif /* IO_Util_hpp */
