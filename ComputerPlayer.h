#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"
#include "View.h"

#include <map>

class ComputerPlayer: public Player{
public:
	ComputerPlayer(View* view, Model* model, int playerNumber);
	~ComputerPlayer(){};
	void playTurn(bool (&cardMap)[4][13]);
};

#endif