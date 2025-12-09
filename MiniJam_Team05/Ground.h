#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ground : public sf::Drawable
{
public:
    Ground(b2World& world, const sf::Vector2f& size, const sf::Vector2f& position, float friction = 0.3f)
        : m_size(size), m_position(position), m_friction(friction)
    {
        const float scale = 32.f; // Pixels per Box2D unit

        // Box2D body definition
        b2BodyDef bodyDef;
        bodyDef.position.Set(position.x / scale, position.y / scale);
        bodyDef.type = b2_staticBody;
        m_body = world.CreateBody(&bodyDef);
        m_body->SetSleepingAllowed(false);

        // Box2D shape
        b2PolygonShape boxShape;
        boxShape.SetAsBox((size.x / 2.f) / scale, (size.y / 2.f) / scale);

        // Fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.friction = friction;

        b2Filter filter;
        filter.categoryBits = 0x0001; // GROUND
        filter.maskBits = 0xFFFF;     // Collide with everything
        fixtureDef.filter = filter;

        m_body->CreateFixture(&fixtureDef);

        // SFML rectangle
        m_rect.setSize(size);
        m_rect.setOrigin(size.x / 2.f, size.y / 2.f);
        m_rect.setFillColor(sf::Color::Green);
        m_rect.setPosition(position);
    }

    void Update()
    {
        // Sync SFML rectangle with Box2D body
        // For static ground this is optional, but useful for future dynamic objects
        const float scale = 32.f;
        b2Vec2 pos = m_body->GetPosition();
        float angle = m_body->GetAngle();
        m_rect.setPosition(pos.x * scale, pos.y * scale);
        m_rect.setRotation(angle * 180.f / b2_pi);
    }

    b2Body* GetBody() { return m_body; }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_rect, states);
    }

private:
    sf::Vector2f m_size;
    sf::Vector2f m_position;
    float m_friction;

    b2Body* m_body;
    sf::RectangleShape m_rect;
};
