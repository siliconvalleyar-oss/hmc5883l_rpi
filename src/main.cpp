#include "drivers/HMC5883L.hpp"

int main() {
    auto device = std::make_unique<app::Hmc5883l_t>();
    device->run();
    return 0;
}
