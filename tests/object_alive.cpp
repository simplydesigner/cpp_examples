#include "object_alive.hpp"

namespace ns_memory {

    object::object(bool& alive): alive_(alive) {
        alive_ = true;
    }

    object::~object() {
        alive_ = false;
    }
}
