#include "credentials.h"

class CredentialHolder {
public:
    CredentialHolder() {}

    const char* getSSID() const {
        return SECRET_SSID;
    }

    const char* getPass() const {
        return SECRET_PASS;
    }
};