#pragma once
#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
	explicit Entity(int hitpoints);
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	void setRotation(float angle);
	sf::Vector2f getVelocity() const;
	float getRotation() const;
	void rotate(float rotation);
	void accelerate(sf::Vector2f velocity);
	void accelerate(float vx, float vy);
	//void distance(sf::Vector2f velocity, float r);

	int getHitpoints() const;
	void repair(int points);
	void damage(int points);
	void destroy();
	virtual void remove();
	virtual bool isDestroyed() const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);


private:
	//virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::Vector2f mVelocity;
	sf::Vector2f mDistance;
	float mRotation;
	int mHitpoints;
};