#pragma once

#include "vector.hpp"

namespace rfg {
struct matrix {
    vector right;
    vector up;
    vector forward;
};

struct matrix43 {
    matrix m_rotation;
    vector m_translation;
};

} // namespace rfg
