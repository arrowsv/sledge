#pragma once

namespace rfg {
enum salvage_material_type {
    INVALID_SALVAGE_MATERIAL = 0xFFFFFFFF,
    SALVAGE_MATERIAL_METAL = 0x0,
    SALVAGE_MATERIAL_ORE = 0x1,
    SALVAGE_MATERIAL_CHEMICAL = 0x2,
    NUM_SALVAGE_MATERIAL_TYPES = 0x3,
};
} // namespace rfg
