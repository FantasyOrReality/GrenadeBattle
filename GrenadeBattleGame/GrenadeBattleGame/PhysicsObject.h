#pragma once
#include "OnScreenActor.h"
class PhysicsObject :
    public OnScreenActor
{
public:
    PhysicsObject();

    virtual void Update(sf::Time frameTime) override;


    virtual void SetVelocity(sf::Vector2f newVelocity);

    virtual void SetAccelaration();

protected:
    float gravity;

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool applyDrag;

private:

};

