#include "ControlsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


ControlsState::ControlsState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(TextureIDs::ControlScreen));


	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 575.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&ControlsState::requestStackPop, this)); //Exiting game rather than returning to Menu

	mGUIContainer.pack(backButton);
}

void ControlsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool ControlsState::update(sf::Time)
{
	return true;
}

bool ControlsState::handleEvent(const sf::Event& event)
{
	
	mGUIContainer.handleEvent(event);
	return false;
}

