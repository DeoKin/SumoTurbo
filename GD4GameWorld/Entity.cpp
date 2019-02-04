#include "Entity.hpp"

#include <cassert>

Entity::Entity(int hitpoints) : mVelocity(), mHitpoints(hitpoints) , mRotation()
{

}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setRotation(float angle)
{
	mRotation = angle;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

float Entity::getRotation() const
{
	return mRotation;
}

void Entity::rotate(float rotation)
{
	mRotation += rotation;

}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

/*void Entity::distance(sf::Vector2f velocity, float rotation)
{
	mVelocity.x += velocity.x * -sin(rotation);
	mVelocity.y += velocity.y * cos(rotation);
}*/

int Entity::getHitpoints() const
{
	return mHitpoints;
}

void Entity::repair(int points)
{
	assert(points > 0);
	mHitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);
	mHitpoints -= points;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

void Entity::remove()
{
	destroy();
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
	rotate(mRotation * dt.asSeconds());
	move(mVelocity * dt.asSeconds());
	//distance(mVelocity, mRotation);
}
