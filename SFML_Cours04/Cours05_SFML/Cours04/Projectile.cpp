#include "Projectile.hpp"

Projectile::Projectile()
{
    projectiles = new std::vector<projData>;
}

void Projectile::createProjectile(sf::Texture _texture, sf::Vector2f _pos, sf::Vector2f _direction, float _speed, float _damages, bool _active)
{
    projData p = projData();
    p.spr = sf::Sprite();
    p.spr.setTexture(_texture);
    p.spr.setPosition(_pos);

    p.direction = _direction;
    p.speed = _speed;
    p.damages = _damages;
    p.activeSelf = _active;

    p.hitbox = createHitbox(p, 0, 0, 10, 10);

    projectiles->push_back(p);
    projectilesNumber += 1;
}

Hitbox* Projectile::createHitbox(projData projectile, float offsetX, float offsetY, float width, float height)
{
    Hitbox* hitbox = new Hitbox(projectile.spr, offsetX, offsetY, width, height);
    return hitbox;
}

void Projectile::setActive(int idx, bool active)
{
    projectiles[idx].data()->activeSelf = active;
    if (active)
    {
        projectiles[idx].data()->spr.setColor(sf::Color::Red);
    }
    else
    {
        projectiles[idx].data()->spr.setColor(sf::Color::Transparent);
    }
}
const bool Projectile::isActive(int idx)
{
    return projectiles[idx].data()->activeSelf;
}

void Projectile::addIgnoreTag(int idx, std::string tag)
{
    projectiles[idx].data()->ignoreTags.push_back(tag);
}
void Projectile::addIgnoreTag(int idx, std::initializer_list<std::string> tags)
{
    for (std::string s : tags)
    {
        projectiles[idx].data()->ignoreTags.push_back(s);
    }
}

void Projectile::update(const float& dt)
{
    for (int i = 0; i < projectilesNumber; i++)
    {
        if (projectiles[i].data()->activeSelf)
        {
            projectiles[i].data()->hitbox->update();
            move(i, dt);            
            if (projectiles[i].data()->spr.getPosition().x < 0 || projectiles[i].data()->spr.getPosition().x > 1280)
            {
                inverseDirection(i, sf::Vector2f(-1, 1));
            }
            if (projectiles[i].data()->spr.getPosition().y < 0 || projectiles[i].data()->spr.getPosition().y > 720)
            {
                inverseDirection(i, sf::Vector2f(1, -1));
            }
        }
    }
}

void Projectile::render(sf::RenderWindow& target, bool showHitbox)
{
    for (int i = 0; i < projectilesNumber; i++)
    {
        target.draw(projectiles[i].data()->spr);
        if (showHitbox)
            projectiles[i].data()->hitbox->render(target);
    }
}

void Projectile::move(int idx, const float& dt)
{
    projectiles[idx].data()->spr.move(projectiles[idx].data()->direction * (projectiles[idx].data()->speed * dt));
    projectiles[idx].data()->hitbox->setPosition(projectiles[idx].data()->spr.getPosition());
}

void Projectile::setPosition(int idx, const sf::Vector2f pos)
{
    projectiles[idx].data()->hitbox->setPosition(pos);
    projectiles[idx].data()->spr.setPosition(pos);
}
void Projectile::setPosition(int idx, const float x, const float y)
{
    projectiles[idx].data()->hitbox->setPosition(x, y);
    projectiles[idx].data()->spr.setPosition(x, y);
}

sf::Vector2f Projectile::getPosition(int idx)
{
    return projectiles[idx].data()->spr.getPosition();
}

void Projectile::inverseDirection(int idx, sf::Vector2f _dir)
{
    projectiles[idx].data()->direction = MultVectors(projectiles[idx].data()->direction, _dir);
}

void Projectile::bounce(int idx, const sf::Vector2f target)
{
    sf::Vector2f dir = this->projectiles[idx].data()->direction;
    dir = Reflect(dir, target);
    dir = NormalizeVector(dir);
    this->projectiles[idx].data()->direction = dir;
}
