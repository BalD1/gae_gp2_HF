#include "Projectile.hpp"

Projectile::Projectile(Entity _attachedEntity, sf::Texture _texture, sf::Vector2f _pos, sf::Vector2f _offset, sf::Vector2f _direction, float _speed, float _damages, bool _active)
{   
    projectileData = new Data();
    projectileData->attachedEntity = _attachedEntity;
    projectileData->spr = sf::Sprite();
    projectileData->spr.setTexture(_texture);
    projectileData->spr.setPosition(_pos);

    projectileData->direction = _direction;
    projectileData->offset = _offset;
    projectileData->speed = _speed;
    projectileData->damages = _damages;
    projectileData->activeSelf = _active;

    projectileData->hitbox = createHitbox(*projectileData, 0, 0, 10, 10);

    if (!this->hit.loadFromFile("Assets/Sounds/simplehit.wav"))
    {
        std::cout << "Could not load hit sound";
    }
    hitSound = new sf::Sound();
    hitSound->setBuffer(hit);
}

Hitbox* Projectile::createHitbox(Data projectile, float offsetX, float offsetY, float width, float height)
{
    Hitbox* hitbox = new Hitbox(projectile.spr, offsetX, offsetY, width, height);
    return hitbox;
}

void Projectile::setActive(bool active)
{
    if (active)
        hitSound->play();

    this->projectileData->activeSelf = active;
}
const bool Projectile::isActive()
{
    return projectileData->activeSelf;
}

void Projectile::addIgnoreTag(std::string tag)
{
    projectileData->ignoreTags.push_back(tag);
}
void Projectile::addIgnoreTag(std::initializer_list<std::string> tags)
{
    for (std::string s : tags)
    {
        projectileData->ignoreTags.push_back(s);
    }
}

void Projectile::update(const float& dt)
{
        if (projectileData->activeSelf)
        {
            canBounce = true;
            projectileData->hitbox->update();
            move(dt);            
            if (projectileData->spr.getPosition().x < 0 || projectileData->spr.getPosition().x > 1280)
            {
                inverseDirection(sf::Vector2f(-1, 1));
                hitSound->play();
            }
            if (projectileData->spr.getPosition().y < 0 || projectileData->spr.getPosition().y > 720)
            {
                inverseDirection(sf::Vector2f(1, -1));
                hitSound->play();
            }
        }
        else
        {
            projectileData->spr.setPosition(projectileData->attachedEntity.getPosition() + projectileData->offset);
            if (projectileData->hitbox)
            projectileData->hitbox->setPosition(projectileData->spr.getPosition());
        }
    
}

void Projectile::render(sf::RenderWindow& target, bool showHitbox)
{
        target.draw(projectileData->spr);
        if (showHitbox)
            projectileData->hitbox->render(target);
    
}

void Projectile::move(const float& dt)
{
    projectileData->spr.move(projectileData->direction * (projectileData->speed * dt));
    projectileData->hitbox->setPosition(projectileData->spr.getPosition());
}

void Projectile::setPosition(const sf::Vector2f pos)
{
    projectileData->hitbox->setPosition(pos);
    projectileData->spr.setPosition(pos);
}
void Projectile::setPosition(const float x, const float y)
{
    projectileData->hitbox->setPosition(x, y);
    projectileData->spr.setPosition(x, y);
}

sf::Vector2f Projectile::getPosition()
{
    return projectileData->spr.getPosition();
}

void Projectile::inverseDirection(sf::Vector2f _dir)
{
    projectileData->direction = MultVectors(projectileData->direction, _dir);
}

void Projectile::bounceX()
{
    if (!canBounce)
        return;

    canBounce = false;
    sf::Vector2f dir = this->projectileData->direction;
    dir.x *= -1.1;
    dir = NormalizeVector(dir);
    this->projectileData->direction = dir;
}
void Projectile::bounceY()
{
    if (!canBounce)
        return;

    canBounce = false;
    sf::Vector2f dir = this->projectileData->direction;
    dir.y *= -1.1;
    dir = NormalizeVector(dir);
    this->projectileData->direction = dir;
}