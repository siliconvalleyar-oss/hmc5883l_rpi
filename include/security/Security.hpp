#ifndef SECURITY_SECURITY_HPP_
#define SECURITY_SECURITY_HPP_

#include <string>

namespace security {

class Security {
public:
    static bool authenticate(const std::string& token);
    static void auditLog(const std::string& event);
};

}

#endif
