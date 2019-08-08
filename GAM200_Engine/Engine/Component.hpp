#pragma once

class Object;

class Component
{
public: 
    virtual void Init(Object* ) = 0;
    virtual void Update(float dt) = 0;

public:
    Object* m_owner = nullptr;
};