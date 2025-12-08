#include "GameObject.h"

static const float SCALE = 30.0f;    // Box2D uses meters — SFML uses pixels

GameObject::GameObject(b2World& world,
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    bool dynamic)
{
    shape.setSize(size);
    shape.setOrigin(size.x / 2.f, size.y / 2.f);

    // ----- Box2D body definition -----
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    body = world.CreateBody(&bodyDef);
    body->SetSleepingAllowed(false);
    // ----- Box2D shape -----
    b2PolygonShape boxShape;
    boxShape.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);

    // ----- Fixture -----
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = dynamic ? 1.0f : 0.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f;

    body->CreateFixture(&fixtureDef);
}

GameObject::~GameObject()
{
    if (body && body->GetWorld())
        body->GetWorld()->DestroyBody(body);
}

void GameObject::update()
{
    // Sync Box2D → SFML
    b2Vec2 pos = body->GetPosition();
    float angle = body->GetAngle();

    setPosition(pos.x * SCALE, pos.y * SCALE);
    setRotation(angle * 180.f / 3.14159f);
}

void GameObject::setTexture(const sf::Texture& tex)
{
    shape.setTexture(&tex);
}

void GameObject::setFillColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(shape, states);
}
