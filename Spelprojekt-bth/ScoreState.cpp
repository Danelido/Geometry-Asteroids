#include "Game.h"
#include "ScoreState.h"
#include "MenuState.h"
#include <fstream>
#include <iostream>
#include "ResourceManager.h"

ScoreState::ScoreState(Game * game, int score) :
	State(game)
{
	this->highScore = 0;
	this->score = score;

	this->background.setSize((sf::Vector2f)this->game->getWindow()->getSize());
	this->background.setTexture(&ResourceManager::getTexture("Background"));

	// Get highscore from file
	this->getHighscoreFromFile("Resources/Data/highscore.txt");

	if (this->score > this->highScore)
	{
		this->saveNewHighscoreToFile("Resources/Data/highscore.txt", this->score);
		
		this->infoText.setText("New highscore: " + std::to_string(this->score));
		this->infoText.setTextSize(42);
		this->infoText.centerWithinBounds(sf::FloatRect(0, this->game->getWindow()->getSize().y / 2.f - 250,
			(float)this->game->getWindow()->getSize().x, this->game->getWindow()->getSize().y / 2.f - 150));
		
		this->highScoreText.setText("Last highscore: " + std::to_string(this->highScore));
		this->highScoreText.setTextSize(28);
		this->highScoreText.centerWithinBounds(sf::FloatRect(0, this->game->getWindow()->getSize().y / 2.f - 200,
			(float)this->game->getWindow()->getSize().x, this->game->getWindow()->getSize().y / 2.f - 100));

	}
	//Probably coming from menustate
	if (this->score == 0)
	{
		this->highScoreText.setText("Highscore: " + std::to_string(this->highScore));
		this->highScoreText.setTextSize(42);
		this->highScoreText.centerWithinBounds(sf::FloatRect(0, this->game->getWindow()->getSize().y / 2.f - 250,
			(float)this->game->getWindow()->getSize().x, this->game->getWindow()->getSize().y / 2.f - 150));
	}

	if (this->score != 0 && this->score <= this->highScore)
	{
		this->highScoreText.setText("Highscore: " + std::to_string(this->highScore));
		this->highScoreText.setTextSize(42);
		this->highScoreText.centerWithinBounds(sf::FloatRect(0, this->game->getWindow()->getSize().y / 2.f - 250,
			(float)this->game->getWindow()->getSize().x, this->game->getWindow()->getSize().y / 2.f - 150));

		this->infoText.setText("Your score: " + std::to_string(this->score));
		this->infoText.setTextSize(28);
		this->infoText.centerWithinBounds(sf::FloatRect(0, this->game->getWindow()->getSize().y / 2.f - 200,
			(float)this->game->getWindow()->getSize().x, this->game->getWindow()->getSize().y / 2.f - 100));
	}


	this->particleHandler = new ParticleHandler();
	this->backToMenuButton = new CustomButton("Back to menu", sf::Vector2f(190.f, 50.f), this->particleHandler);
	this->backToMenuButton->setParticleColor(sf::Color(151, 21, 133));
	this->backToMenuButton->centerHorizontal();
	this->backToMenuButton->setY((float)(this->game->getWindow()->getSize().y / 2 + 150));

}

ScoreState::~ScoreState()
{
	delete this->particleHandler;
	delete this->backToMenuButton;
}

void ScoreState::getHighscoreFromFile(std::string path)
{
	std::ifstream inFileStream;
	inFileStream.open(path);
	
	if (inFileStream.fail())
	{
		printf("Failed to open file: %s\n", path.c_str());
	}
	else
	{
		inFileStream >> this->highScore;
		inFileStream.close();
	}
	
	
}
void ScoreState::saveNewHighscoreToFile(std::string path, int newHighscore) throw(...)
{
	std::ofstream outFileStream;
	outFileStream.open(path);
	
	if (outFileStream.fail())
	{
		printf("Failed to open file: %s\n", path.c_str());
	}
	else
	{
		outFileStream << newHighscore;
		outFileStream.close();
	}

}

void ScoreState::input()
{
	this->mousePos = sf::Mouse::getPosition(*this->game->getWindow());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (this->backToMenuButton->isHovered())
		{
			this->game->changeState(new MenuState(this->game));
		}
	}
	else
	{
		//Back to menu
		if (this->backToMenuButton->isHovered())
		{
			this->backToMenuButton->setTextColor(sf::Color(151, 21, 133, 150));
		}
		else
		{
			this->backToMenuButton->setTextColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void ScoreState::update(float dt)
{
	this->particleHandler->update(dt);
	this->backToMenuButton->update(dt,this->mousePos,this->game->getWindow()->getSize());

	if (this->score != 0)
	{
		this->game->getWindow()->draw(this->infoText.getDrawable());
	}
	this->game->getWindow()->draw(this->highScoreText.getDrawable());

}

void ScoreState::render()
{
	this->game->getWindow()->draw(this->background);
	this->particleHandler->render(this->game->getWindow());
	if (this->score != 0) 
	{
		this->game->getWindow()->draw(this->infoText.getDrawable());
	}
	this->game->getWindow()->draw(this->highScoreText.getDrawable());
	this->backToMenuButton->render(this->game->getWindow());
}

void ScoreState::updateViewport()
{
	this->background.setSize((sf::Vector2f)this->game->getWindow()->getSize());
	this->backToMenuButton->setY((float)(this->game->getWindow()->getSize().y / 2 + 150));
}
