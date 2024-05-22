#include "Gui.h"

void Gui::initGui(sf::RenderWindow* window)
{
	// load font
	if (!this->font.loadFromFile(MAIN_DIRECTORY+"Fonts/PoetsenOne-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << std::endl;
	}

	// init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
	this->pointText.setPosition(static_cast<float>(window->getSize().x - 150), 25.f);

	//init player gui
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	this->playerHpBarBack.setPosition(sf::Vector2f(20.f, 20.f));

	// init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game over");
	this->gameOverText.setPosition(sf::Vector2f(
		window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f)
	);
}

Gui::Gui(sf::RenderWindow* window)
{
	this->initGui(window);
}

Gui::~Gui()
{
}

void Gui::update(int points, Player* player)
{
	//points gui
	std::stringstream ss;
	ss << "Points: " << points;
	this->pointText.setString(ss.str());

	//update player gui	
	float hpPersent = static_cast<float>(player->getHp()) / player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(this->playerHpBarBack.getSize().x * hpPersent, this->playerHpBar.getSize().y));
}

void Gui::render(sf::RenderTarget* target)
{
	target->draw(this->pointText);
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
}

void Gui::renderGameOver(sf::RenderTarget* target)
{
	target->draw(this->gameOverText);
}