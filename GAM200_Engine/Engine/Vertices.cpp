/*  1. sinil.gang
 *  2. Shapes Programming Assignment
 *  3. CS230
 *  4. Spring 2019
 */
#include "Mesh.hpp""
#include "VertexLayoutDescription.hpp"
#include "Vertices.hpp"
#include <GL/glew.h>
#include <cassert>

    int FindVerticesListPattern(const Mesh& mesh)
    {
        switch (mesh.GetPointListPattern())
        {
            case PointListPattern::Lines:
                return GL_LINES;
            case PointListPattern::LineStrip:
                return GL_LINE_STRIP;
            case PointListPattern::LineLoop:
                return GL_LINE_LOOP;
            case PointListPattern::Triangles:
                return GL_TRIANGLES;
            case PointListPattern::TriangleStrip:
                return GL_TRIANGLE_STRIP;
            case PointListPattern::TriangleFan:
                return GL_TRIANGLE_FAN;
            default:
            return 0;
        }
    }

    Vertices::Vertices(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
    {
        InitializeWithMeshAndLayout(mesh, vertex_layout);
    }

    Vertices::~Vertices() noexcept
    {
        DeleteVerticesOnGPU();
    }

    Vertices::Vertices(Vertices&& other) noexcept
    {
        verticesHandle             = other.verticesHandle;
        dataBufferHandle           = other.dataBufferHandle;
        verticesCount              = other.verticesCount;
        verticesListPattern        = other.verticesListPattern;
        layout                     = other.layout;
        bufferVertexCapacity       = other.bufferVertexCapacity;
        other.verticesHandle       = 0;
        other.dataBufferHandle     = 0;
        other.verticesCount        = 0;
        other.bufferVertexCapacity = 0;
    }

    void Vertices::operator=(Vertices&& other) noexcept
    {
        if (this == &other)
            return;
        DeleteVerticesOnGPU();
        verticesHandle             = other.verticesHandle;
        dataBufferHandle           = other.dataBufferHandle;
        verticesCount              = other.verticesCount;
        verticesListPattern        = other.verticesListPattern;
        layout                     = other.layout;
        bufferVertexCapacity       = other.bufferVertexCapacity;
        other.verticesHandle       = 0;
        other.dataBufferHandle     = 0;
        other.verticesCount        = 0;
        other.bufferVertexCapacity = 0;
    }

    void Vertices::InitializeWithMeshAndLayout(const Mesh& mesh, const VertexLayoutDescription& vertex_layout) noexcept
    {
        DeleteVerticesOnGPU();

        layout = vertex_layout;

        verticesListPattern = FindVerticesListPattern(mesh);
        verticesCount = static_cast<int>(mesh.GetPointCount());
        bufferVertexCapacity = verticesCount;

        (glGenVertexArrays(1, &verticesHandle));

        (glGenBuffers(1, &dataBufferHandle));

        (glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));

        Select(*this);

        (glBufferData(GL_ARRAY_BUFFER, (verticesCount * layout.GetVertexSize()), nullptr, GL_STATIC_DRAW));

        layout.SendVertexDescriptionToOpenGL();

        WriteMeshDataToVertexBuffer(mesh);

        SelectNothing();
    }

    void Vertices::UpdateVerticesFromMesh(const Mesh& mesh)
    {
        if (static_cast<int>(mesh.GetPointCount()) <= bufferVertexCapacity)
        {
            verticesCount = static_cast<unsigned int>(mesh.GetPointCount());

            verticesListPattern = FindVerticesListPattern(mesh);
        }
        else
        {
            DeleteVerticesOnGPU();
            InitializeWithMeshAndLayout(mesh, layout);
        }

        WriteMeshDataToVertexBuffer(mesh);
    }

    void Vertices::Select(const Vertices& vertices)
    {
        (glBindVertexArray(vertices.verticesHandle));

    }

    void Vertices::SelectNothing()
    {
        (glBindVertexArray(NULL));
    }

    void Vertices::DeleteVerticesOnGPU() noexcept
    {
        if (verticesHandle != 0)
        {
            (glDeleteBuffers(1, &verticesHandle));
            verticesHandle = 0;
            (glDeleteVertexArrays(1, &dataBufferHandle));
        }
    }

    void Vertices::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
    {
        if (mesh.GetPointCount() == 0)
        {
            return;
        }

        Select(*this);

        (glBindBuffer(GL_ARRAY_BUFFER, dataBufferHandle));
        void* pointer;
        (pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        GLuint offset = 0;
        vector2  position          ;
        vector2  textureCoordinate ;
        Color4ub color;
        char* destination = nullptr; 
        for (std::size_t index = 0; index < mesh.GetPointCount(); ++index)
        {
            for (const auto& element : layout.GetFieldTypes())
            {
                destination = reinterpret_cast<char*>(pointer) + offset;
                switch (element)
                {
                    case VertexLayoutDescription::Position2WithFloats:
                        position = mesh.GetPoint(index);
                        std::memcpy(destination, &position, sizeof(position));
                        offset += sizeof(position);
                        break;
                    case VertexLayoutDescription::TextureCoordinates2WithFloats:
                        textureCoordinate = mesh.GetTextureCoordinate(index);
                        std::memcpy(destination, &textureCoordinate, sizeof(textureCoordinate));
                        offset += sizeof(textureCoordinate);
                        break;
                    case VertexLayoutDescription::Color4WithUnsignedBytes:
                        color = mesh.GetColor(index);
                        std::memcpy(destination, &color, sizeof(color));
                        offset += sizeof(color);
                        break;
                    default:;
                }
            }
        }

        (glUnmapBuffer(GL_ARRAY_BUFFER));

        SelectNothing();
    }