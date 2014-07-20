#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Model.h"
#include "Controller.h"
#include "Player.h"

class Card;

using namespace std;

Controller::Controller(Model* model) {
	this->_model = model;
}

void Controller::initializeModel() {
	_model->cleanUp();
	_model->initializePlayers();
	_model->initializeDeck();

	_model->setState(Model::NONE);
}

void Controller::run() {
	srand48(_model->getSeed());
	initializeModel();
	playRound();
}

void Controller::playRound() {
	_model->clearCardsOnTable();
	_model->shuffle();
	_model->deal();

	for (int i = 0; i < 4; i++){
		_model->getPlayer(i)->prepForNewRound();
	}

	_model->setCurrentPlayer(_model->getFirstPlayer()->getNumber()-1);
	_model->setState(Model::ROUND_STARTED);
	_model->setState(Model::IN_PROGRESS);

	if (!_model->getCurrentPlayer()->isHuman()){
		playATurn(NULL);
	}
}

void Controller::playATurn(Card* card) {
	if (_model->getCurrentPlayer()->getHandSize() == 0) {
		_model->updateScoreAndEndGame();

		if (_model->getState() == Model::GAME_ENDED) {
			_model->cleanUp();
		} else {
			playRound();
		}

		return;
	}

	if (_model->playTurn(card)) {
		_model->advanceCurrentPlayer();
	}

	if (!_model->getCurrentPlayer()->isHuman() || _model->getCurrentPlayer()->getHandSize() == 0) {
		playATurn(NULL);
	}
}

void Controller::computerizePlayer(int playerIndex) {
	_model->computerizePlayer(playerIndex);
	_model->setPlayerType(playerIndex, 'c');
	playATurn(NULL);
}

void Controller::togglePlayer(int playerIndex) {
	(_model->getPlayerType(playerIndex) == 'h') ? _model->setPlayerType(playerIndex, 'c') : _model->setPlayerType(playerIndex, 'h');
}

void Controller::setSeed(int seed){
	_model->setSeed(seed);
}

void Controller::endGame() {
	_model->cleanUp();
}

void Controller::saveGame(string filename) {
	ofstream file(filename.c_str());
	if (file.is_open()) {
		_model->exportModel(file);
		file.close();
	}
}

void Controller::loadSavedFile(string filename) {
	_model->cleanUp();
	ifstream file(filename.c_str());
	if (file.is_open()) {
		_model->importModel(file);
		file.close();
	}
}
