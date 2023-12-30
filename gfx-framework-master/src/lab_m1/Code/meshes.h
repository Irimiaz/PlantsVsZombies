#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateRomb(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(
        const std::string& name,
        glm::vec3 center,
        float distance,
        glm::vec3 color,
        bool fill = false);

    Mesh* CreateHexagon(
        const std::string& name,
        glm::vec3 center,
        float largeHexagonSize,
        float smallHexagonSize,
        glm::vec3 largeHexagonColor,
        glm::vec3 smallHexagonColor,
        bool fill = false);
    Mesh* CreatePinkStar(
        const std::string& name,
        glm::vec3 center,
        float size,
        glm::vec3 color,
        bool fill);
}
