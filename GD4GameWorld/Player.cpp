#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
#include "Utility.hpp"

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

struct AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx, vy)//, rotation(r)
	{

	}
	// Add Rotation to update
	//AircraftMover(float d) : rotation(d)
	//{

	//}
	void operator() (Aircraft& aircraft, sf::Time) const
	{
		
		aircraft.accelerate(velocity * aircraft.getMaxSpeed());
		///aircraft.rotate(rotation);
		//aircraft.distance(velocity, rotation);
		
	}
	sf::Vector2f velocity;
	//float rotation;
};

struct AircraftRotator
{
	AircraftRotator(float angle) : rotation(angle)
	{

	}
	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.rotate(rotation * aircraft.getMaxRotationSpeed());
	}

	float rotation;
};

Player::Player()
	: mCurrentMissionStatus(MissionStatus::MissionRunning)
{
	//Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::W] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::S] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Action::Fire;
	mKeyBinding[sf::Keyboard::M] = Action::LaunchMissile;
	mKeyBinding[sf::Keyboard::A] = Action::RotateAntiClockWise;
	mKeyBinding[sf::Keyboard::D] = Action::RotateClockWise;

	//set initial action bindings
	initializeActions();
	//Assign all categories to the player's aircraft
	for (auto& pair : mActionBinding)
	{
		pair.second.category = static_cast<unsigned int>(Category::PlayerAircraft);
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		//check if key pressed is in the key bindings, if so trigger command
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	//Check if any key binding keys are pressed
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	//Remove all keys that are already mapped to an action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
	{
		if (itr->second == action)
		{
			mKeyBinding.erase(itr++);
		}
		else
		{
			++itr;
		}
		//insert new binding
		mKeyBinding[key] = action;
	}
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}
	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initializeActions()
{
	mActionBinding[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0.f)); //Moves Position (x,y)
	mActionBinding[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(1, 0.f));
	mActionBinding[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -1));
	mActionBinding[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, 1));
	mActionBinding[Action::Fire].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time) { a.fire(); });
	mActionBinding[Action::LaunchMissile].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time) { a.launchMissile(); });
	mActionBinding[Action::RotateAntiClockWise].action = derivedAction<Aircraft>(AircraftRotator(-5.f)); //Rotate
	mActionBinding[Action::RotateClockWise].action = derivedAction<Aircraft>(AircraftRotator(5.f));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveUp:
	case Action::MoveDown:
	case Action::RotateAntiClockWise:
	case Action::RotateClockWise:
	case Action::Fire:
		return true;
	default:
		return false;
	}
}

