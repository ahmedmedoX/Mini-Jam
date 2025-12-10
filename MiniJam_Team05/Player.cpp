#include "Player.h"

Player::Player(b2World& world, const b2Vec2 position) {
    this->world = &world;

    interacting = false;
    boxBody = nullptr;

    velocity = walkVelocity;
    animationRate = 0.5f;

    footContacts = 0;
    onGround = false;

    filter.categoryBits = PLAYER;
    filter.maskBits = GROUND | BOX | KEY | SPIKE | DOOR;

    SetBody(position);
    SetFixture();
    InitializeAnimations();
}

void Player::SetBody(const b2Vec2 Position) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(Position.x, Position.y);
    bodyDef.fixedRotation = true;
    bodyDef.allowSleep = false;
    body = world->CreateBody(&bodyDef);
}

void Player::SetFixture() {
    b2PolygonShape boxShape;
    boxShape.SetAsBox((size.x / 2) / Utilities::PIXELS_PER_UNIT, (size.y / 2) / Utilities::PIXELS_PER_UNIT);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter = filter;

    body->CreateFixture(&fixtureDef);

    float footHalfWidth = (size.x * 0.5f - 5.f) / Utilities::PIXELS_PER_UNIT;   // -5px inward
    float footHalfHeight = 2.f / Utilities::PIXELS_PER_UNIT;

    float footOffsetY = (size.y * 0.5f) / Utilities::PIXELS_PER_UNIT;

    b2PolygonShape footShape;
    footShape.SetAsBox(
        footHalfWidth,
        footHalfHeight,
        b2Vec2(0.f, -footOffsetY),
        0.f
    );

    b2FixtureDef footFixture;
    footFixture.shape = &footShape;
    footFixture.isSensor = true;
    footFixture.filter = filter;
    footFixture.userData.pointer = 1;

    footSensor = body->CreateFixture(&footFixture);
}

void Player::InitializeAnimations() {
    textures[IDLE] = &SpriteLoader::getTexture(playerIdle);
    textures[MOVE] = &SpriteLoader::getTexture(playerRun);
    textures[PUSH] = &SpriteLoader::getTexture(playerPush);
    textures[PULL] = &SpriteLoader::getTexture(playerPull);
    textures[FALL] = &SpriteLoader::getTexture(playerFall);

    animations[IDLE] = Animation(textures[IDLE], { 4, 1 }, .8);
    animations[MOVE] = Animation(textures[MOVE], { 5, 1 }, animationRate);
    animations[PUSH] = Animation(textures[PUSH], { 2, 1 }, animationRate);
    animations[PULL] = Animation(textures[PULL], { 2, 1 }, animationRate);
    animations[FALL] = Animation(textures[FALL], { 1, 1 }, animationRate);

    sprite.setScale(size.x / animations[IDLE].uvRect.width,
        size.y / animations[IDLE].uvRect.height);
}

void Player::Update(Direction dir, Control control, float deltaTime) {
    currentState = IDLE;

    bool horizontalMove = (dir == LEFT || dir == RIGHT);
    int dirX = (dir == LEFT ? -1 : (dir == RIGHT ? 1 : 0));

    if (control == INTERACT && interacting && boxBody && onGround) {
        if (dirX != 0) {
            float gravity = 9.8;

            float force = boxBody->GetMass() * gravity * 0.52f;
            float drag = body->GetMass() * gravity * 0.52f;

            float dx = boxBody->GetPosition().x - body->GetPosition().x;

            if ((dx > 0 && dirX > 0) || (dx < 0 && dirX < 0))
                currentState = PUSH;
            else
                currentState = PULL;

            boxBody->ApplyForceToCenter({ force * dirX, 0 }, true);
            body->ApplyForceToCenter({ drag * dirX, 0 }, true);
        }
    }
    else {
        if (!onGround) {
            currentState = FALL;
            velocity = fallVelocity;
        }
        else
            velocity = walkVelocity;

        if (horizontalMove) {
            Move(dir);
            currentState = MOVE;
        }

    }

    UpdateAnimation(deltaTime, dir);
}

void Player::Move(Direction dir) {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = velocity * (dir == LEFT ? -1 : 1);
    body->SetLinearVelocity(vel);
}

void Player::UpdateAnimation(const float dt, Direction dir) {
    Animation* animation = &animations[currentState];
    sprite.setTexture(*textures[currentState]);
    int scaleSign = sprite.getScale().x < 0 ? -1 : 1;

    if (dir != NOMOVE) scaleSign = (int)dir;
    if (currentState == PULL) scaleSign = -scaleSign;

    sprite.setOrigin(animation->uvRect.width / 2.0f, animation->uvRect.height / 2.0f);
    sprite.setScale(scaleSign * (size.x / animation->uvRect.width),
        size.y / animation->uvRect.height);

    animation->Update(0, dt);
    sprite.setTextureRect(animation->uvRect);

    //b2Vec2 pos = body->GetPosition();
    sprite.setPosition(
        Utilities::Convert_Box2D_SFML_Space(body->GetPosition())
    );
}

void Player::BeginContact(b2Contact* contact) {
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    uint16 cA = fA->GetFilterData().categoryBits;
    uint16 cB = fB->GetFilterData().categoryBits;

    if (cA == SPIKE || cB == SPIKE) {
        std::cout << "Player hit spikes!" << std::endl;
        return;
    }

    if (cA == DOOR || cB == DOOR) {
        std::cout << "Player reached the door!" << std::endl;
        return;
    }

    if (cA == BOX) {
        std::cout << "Player interacting with box" << std::endl;
        boxBody = fA->GetBody();
        interacting = true;
    }

    else if (cB == BOX) {
        std::cout << "Player interacting with box" << std::endl;
        boxBody = fB->GetBody();
        interacting = true;
    }

    if (cA == KEY || cB == KEY) {
        collectables++;
        std::cout << "Player collected a key! Total keys: " << collectables << std::endl;
    }

    if (fA == footSensor || fB == footSensor) {
        footContacts++;
        onGround = true;
        std::cout << "Player on ground" << std::endl;
    }
}

int Player::GetCollectablesNumber() {
    return collectables;
}

void Player::EndContact(b2Contact* contact) {
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    uint16 cA = fA->GetFilterData().categoryBits;
    uint16 cB = fB->GetFilterData().categoryBits;

    if (cA == BOX || cB == BOX) {
        boxBody = nullptr;
        interacting = false;
    }

    if (fA == footSensor || fB == footSensor) {
        footContacts--;
        if (footContacts <= 0)
            onGround = false;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

Player::~Player() {
    if (body && world)
    {
        world->DestroyBody(body);
        body = nullptr;
    }
    footSensor = nullptr;
    textures.clear();
    animations.clear();
}