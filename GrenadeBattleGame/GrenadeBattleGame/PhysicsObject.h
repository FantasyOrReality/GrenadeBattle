#pragma once
#include "OnScreenActor.h"
class PhysicsObject :
    public OnScreenActor
{
public:
    PhysicsObject();

    virtual void Update(sf::Time frameTime) override;
    virtual void Draw(sf::RenderTarget& target) override;

    virtual void SetPosition(sf::Vector2f newPosition) override;
    virtual void SetPosition(float newX, float newY) override;

    virtual void SetVelocity(sf::Vector2f newVelocity);

    void SetAccelaration();

protected:
    float gravity;

    sf::Vector2f velocity;
    sf::Vector2f fireVelocity;
    sf::Vector2f acceleration;

private:

};

