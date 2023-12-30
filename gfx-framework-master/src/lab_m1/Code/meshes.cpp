#include "meshes.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, -1), color),
        VertexFormat(corner + glm::vec3(length, 0, -1), color),
        VertexFormat(corner + glm::vec3(length, length, -1), color),
        VertexFormat(corner + glm::vec3(0, length, -1), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRomb(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(size / 2 * (-1), 0, 2), color),
        VertexFormat(corner + glm::vec3(size / 2 , 0, 2), color),
        VertexFormat(corner + glm::vec3(0, size, 2), color),

        VertexFormat(corner + glm::vec3(size / 2 * (-1), 0, 2), color),
        VertexFormat(corner + glm::vec3(size / 2 , 0, 2), color),
        VertexFormat(corner + glm::vec3(0, size * (-1), 2), color),

        VertexFormat(corner + glm::vec3(0 , size/4, 2), color),
        VertexFormat(corner + glm::vec3(size , size/4, 2), color),
        VertexFormat(corner + glm::vec3(size , size / 4 * (-1), 2), color),

        VertexFormat(corner + glm::vec3(size , size / 4 * (-1), 2), color),
        VertexFormat(corner + glm::vec3(0 , size / 4 * (-1), 2), color),
        VertexFormat(corner + glm::vec3(0 , size / 4, 2), color),
    };

    Mesh* romb = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4 ,5,6,7,8,9, 10, 11};

    if (!fill) {
        romb->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    romb->InitFromData(vertices, indices);
    return romb;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 9), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 9), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 9), color),

        

        VertexFormat(corner + glm::vec3(0, 0, 9), color),
        VertexFormat(corner + glm::vec3(size / 2, size, 9), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 9), color),

        VertexFormat(corner + glm::vec3(0, 0, 9), color),
        VertexFormat(corner + glm::vec3(size / 2, size, 9), color),
        VertexFormat(corner + glm::vec3(size, 0, 9), color),

        VertexFormat(corner + glm::vec3(0, 0, 9), color),
        VertexFormat(corner + glm::vec3(size, 0, 9), color),
        VertexFormat(corner + glm::vec3(0, size * (-1), 9), color),

        VertexFormat(corner + glm::vec3(0, 0, 9), color),
        VertexFormat(corner + glm::vec3(0, size * (-1), 9), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 9), color),


        
        VertexFormat(corner + glm::vec3(size * (-1), 0, 9), color),
        VertexFormat(corner + glm::vec3(size * (-2), size , 9), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 9), color),

        VertexFormat(corner + glm::vec3(size * (1), 0, 9), color),
        VertexFormat(corner + glm::vec3(size * (2), size , 9), color),
        VertexFormat(corner + glm::vec3(size * (1) / 2, size, 9), color),

        VertexFormat(corner + glm::vec3(0, size * (-1), 9), color),
        VertexFormat(corner + glm::vec3(size * (-1.5) ,  size * (-1.5), 9), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 9), color),
        
        VertexFormat(corner + glm::vec3(0, size * (-1), 9), color),
        VertexFormat(corner + glm::vec3(size * (1.5) ,  size * (-1.5), 9), color),
        VertexFormat(corner + glm::vec3(size * (1), 0, 9), color),
        

        
        VertexFormat(corner + glm::vec3(size * (-0.5), size, 0), color),
        VertexFormat(corner + glm::vec3(0, size * 2, 0), color),
        VertexFormat(corner + glm::vec3(size * (0.5), size, 0), color),
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4 ,5,6,7,8,9, 10, 11,12,13,14, 15,16,17,18,19,20,21,22,23,24,25,26,27,28,29 };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreatePinkStar(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 10), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 10), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 10), color),



        VertexFormat(corner + glm::vec3(0, 0, 10), color),
        VertexFormat(corner + glm::vec3(size / 2, size, 10), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 10), color),

        VertexFormat(corner + glm::vec3(0, 0, 10), color),
        VertexFormat(corner + glm::vec3(size / 2, size, 10), color),
        VertexFormat(corner + glm::vec3(size, 0, 10), color),

        VertexFormat(corner + glm::vec3(0, 0, 10), color),
        VertexFormat(corner + glm::vec3(size, 0, 10), color),
        VertexFormat(corner + glm::vec3(0, size * (-1), 10), color),

        VertexFormat(corner + glm::vec3(0, 0, 10), color),
        VertexFormat(corner + glm::vec3(0, size * (-1), 10), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 10), color),



        VertexFormat(corner + glm::vec3(size * (-1), 0, 10), color),
        VertexFormat(corner + glm::vec3(size * (-2), size , 10), color),
        VertexFormat(corner + glm::vec3(size * (-1) / 2, size, 10), color),

        VertexFormat(corner + glm::vec3(size * (1), 0, 10), color),
        VertexFormat(corner + glm::vec3(size * (2), size , 10), color),
        VertexFormat(corner + glm::vec3(size * (1) / 2, size, 10), color),

        VertexFormat(corner + glm::vec3(0, size * (-1), 10), color),
        VertexFormat(corner + glm::vec3(size * (-1.5) ,  size * (-1.5), 10), color),
        VertexFormat(corner + glm::vec3(size * (-1), 0, 10), color),

        VertexFormat(corner + glm::vec3(0, size * (-1), 10), color),
        VertexFormat(corner + glm::vec3(size * (1.5) ,  size * (-1.5), 10), color),
        VertexFormat(corner + glm::vec3(size * (1), 0, 10), color),



        VertexFormat(corner + glm::vec3(size * (-0.5), size, 10), color),
        VertexFormat(corner + glm::vec3(0, size * 2, 10), color),
        VertexFormat(corner + glm::vec3(size * (0.5), size, 10), color),
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4 ,5,6,7,8,9, 10, 11,12,13,14, 15,16,17,18,19,20,21,22,23,24,25,26,27,28,29 };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}


Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float largeHexagonSize,
    float smallHexagonSize,
    glm::vec3 largeHexagonColor,
    glm::vec3 smallHexagonColor,
    bool fill)
{
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 0 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 0 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 1 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 1 + 20.0f)), 0), largeHexagonColor),
    
        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 1 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 1 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 2 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 2 + 20.0f)), 0), largeHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 2 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 2 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 3 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 3 + 20.0f)), 0), largeHexagonColor),
        
        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 3 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 3 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 4 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 4 + 20.0f)), 0), largeHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 4 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 4 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 5 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 5 + 20.0f)), 0), largeHexagonColor),
        
        VertexFormat(corner + glm::vec3(0, 0, 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 0 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 0 + 20.0f)), 0), largeHexagonColor),
        VertexFormat(corner + glm::vec3(largeHexagonSize * glm::cos(glm::radians(60.0f * 5 + 20.0f)), largeHexagonSize * glm::sin(glm::radians(60.0f * 5 + 20.0f)), 0), largeHexagonColor),
        //-------------------------------

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 0 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 0 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 1 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 1 + 20.0f)), 1), smallHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 1 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 1 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 2 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 2 + 20.0f)), 1), smallHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 2 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 2 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 3 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 3 + 20.0f)), 1), smallHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 3 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 3 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 4 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 4 + 20.0f)), 1), smallHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 4 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 4 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 5 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 5 + 20.0f)), 1), smallHexagonColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 0 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 0 + 20.0f)), 1), smallHexagonColor),
        VertexFormat(corner + glm::vec3(smallHexagonSize * glm::cos(glm::radians(60.0f * 5 + 20.0f)), smallHexagonSize * glm::sin(glm::radians(60.0f * 5 + 20.0f)), 1), smallHexagonColor),

    };

    Mesh* hex = new Mesh(name);
    const unsigned int size = 36; // You can change this to the desired size

    // Create a vector and add consecutive integers
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < size; ++i) {
        indices.push_back(i);
    }

    if (!fill) {
        hex->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    hex->InitFromData(vertices, indices);
    return hex;
}



