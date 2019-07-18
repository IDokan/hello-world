#include <Mesh.hpp>
#include <angles.hpp>
#include <cmath>

    std::size_t Mesh::GetPointCount() const noexcept
    {
        return points.size();
    }
    vector2 Mesh::GetPoint(std::size_t index) const noexcept
    {
        return points[index];
    }
    Color4ub Mesh::GetColor(std::size_t index) const noexcept
    {
        if (index >= colors.size())
        {
            return colors.back();
        }
        else if (0 <= index && index < GetPointCount())
        {
            return colors[index];
        }
        else
        {
            return Color4ub(0, 0, 0);
        }
    }
    vector2 Mesh::GetTextureCoordinate(std::size_t index) const noexcept
    {
        if (index >= textureCoordinates.size())
        {
            return textureCoordinates.back();
        }
        else if (0 <= index && index < GetPointCount())
        {
            return textureCoordinates[index];
        }
        else
        {
            return vector2(0.0f, 0.0f);
        }
    }
    PointListPattern Mesh::GetPointListPattern() const noexcept
    {
        return pointListType;
    }
    void Mesh::SetPointListType(PointListPattern type) noexcept
    {
        pointListType = type;
    }
    void Mesh::AddColor(Color4ub color) noexcept
    {
        colors.push_back(color);
    }
    void Mesh::AddPoint(vector2 point) noexcept
    {
        points.push_back(point);
    }
    void Mesh::AddTextureCoordinate(vector2 texture_coordinate) noexcept
    {
        textureCoordinates.push_back(texture_coordinate);
    }
    void Mesh::ClearColors() noexcept
    {
        colors.clear();
    }
    bool Mesh::HasMoreThanOneColor() const noexcept
    {
        if (colors.size() > 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Mesh::ClearTextureCoordinates() noexcept
    {
        textureCoordinates.clear();
    }
    void Mesh::ClearPoints() noexcept
    {
        points.clear();
    }
    void Mesh::Clear() noexcept
    {
        ClearTextureCoordinates();
        ClearPoints();
        ClearColors();
    }
    namespace MESH
    {
        Mesh create_circle(float radius, Color4ub color, std::size_t point_count) noexcept
        {
            Mesh circle;
            float angle = TWO_PI / point_count;

            circle.SetPointListType(PointListPattern::TriangleFan);
            circle.AddColor(color);
            circle.AddPoint({ 0,0 });

            for (int i = 0; i <= point_count; i++)
            {
                circle.AddPoint(vector2(radius * std::sin(i*angle), -radius * std::cos(i*angle)));
            }
            return circle;
        }
        Mesh create_wire_circle(float radius, Color4ub color,
            std::size_t point_count) noexcept
        {
            Mesh wireCircle;
            float angle = TWO_PI / point_count;

            wireCircle.SetPointListType(PointListPattern::LineLoop);
            wireCircle.AddColor(color);

            for (int i = 0; i <= point_count; i++)
            {
                wireCircle.AddPoint(vector2(radius * std::sin(i*angle), -radius * std::cos(i*angle)));
            }
            return wireCircle;
        }
        Mesh create_box(float dimension, Color4ub color) noexcept
        {
            return create_rectangle(dimension, dimension, color);
        }
        Mesh create_rectangle(float width, float height, Color4ub color) noexcept
        {
            Mesh rectangle;

            rectangle.SetPointListType(PointListPattern::TriangleFan);

            rectangle.AddTextureCoordinate(vector2(0.0f, 1.0f));
            rectangle.AddTextureCoordinate(vector2(0.0f, 0.0f));
            rectangle.AddTextureCoordinate(vector2(1.0f, 0.0f));
            rectangle.AddTextureCoordinate(vector2(1.0f, 1.0f));

            rectangle.AddPoint(vector2(-width / 2, -height / 2));
            rectangle.AddPoint(vector2(-width / 2, height / 2));
            rectangle.AddPoint(vector2(width / 2, height / 2));
            rectangle.AddPoint(vector2(width / 2, -height / 2));
            rectangle.AddColor(color);

            return rectangle;

        }
        Mesh create_wire_rectangle(float width, float height, Color4ub color) noexcept
        {
            Mesh wireRectangle;

            wireRectangle.SetPointListType(PointListPattern::LineLoop);

            wireRectangle.AddTextureCoordinate(vector2(0.0f, 1.0f));
            wireRectangle.AddTextureCoordinate(vector2(1.0f, 0.0f));
            wireRectangle.AddTextureCoordinate(vector2(0.0f, 1.0f));
            wireRectangle.AddTextureCoordinate(vector2(1.0f, 1.0f));

            wireRectangle.AddColor(color);
            wireRectangle.AddPoint(vector2(-width / 2, -height / 2));
            wireRectangle.AddPoint(vector2(-width / 2, height / 2));
            wireRectangle.AddPoint(vector2(width / 2, height / 2));
            wireRectangle.AddPoint(vector2(width / 2, -height / 2));

            return wireRectangle;
        }
        Mesh create_wire_box(float dimension, Color4ub color) noexcept
        {
            return create_wire_rectangle(dimension, dimension, color);
        }
        Mesh create_line(vector2 a, vector2 b, Color4ub color) noexcept
        {
            Mesh line;

            line.SetPointListType(PointListPattern::LineStrip);

            line.AddColor(color);
            line.AddPoint(a);
            line.AddPoint(b);

            return line;
        }
    }
