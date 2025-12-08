#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class GameObject : public sf::Drawable, public sf::Transformable {
public:
    GameObject(b2World& world,
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        bool dynamic = true);

    ~GameObject();

    void update();                                   // sync physics → SFML
    b2Body* getBody() { return body; }               // access Box2D body

    void setTexture(const sf::Texture& tex);
    void setFillColor(const sf::Color& color);

private:
    b2Body* body = nullptr;
    sf::RectangleShape shape;                         // drawable

    virtual void draw(sf::RenderTarget& target,
        sf::RenderStates states) const override;
};
