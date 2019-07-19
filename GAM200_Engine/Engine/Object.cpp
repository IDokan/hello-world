#include "Object.hpp"

void Object::AddComponent(Component * comp)
{
    comp->Init(this);
    components.push_back(comp);
}

void Object::DeleteComponent(Component * comp)
{
    components.erase(std::find(components.begin(), components.end(), comp));
}

void Object::SetTranslation(vector2 pos)
{
    m_transform.SetTranslation(pos);
}

void Object::SetRotation(float angle)
{
    m_transform.SetRotation(angle);
}

void Object::SetScale(vector2 scale)
{
    m_transform.SetScale(scale);
}

void Object::SetScale(float scale)
{
    m_transform.SetScale(scale);
}

void Object::SetDepth(float depth)
{
    m_transform.SetDepth(depth);
}

void Object::SetMesh(Mesh mesh)
{
    this->mesh = mesh;
}
