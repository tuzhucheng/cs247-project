#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "Model.h"
#include "View.h"
#include "Player.h"
#include "HumanPlayer.h"

#include <vector>

class Model;
class View;

class Controller{
public:
	Controller(Model* model);
	void run();
	void initializeModel();
	void setView(View* view);
	void requestCommand(HumanPlayer*, std::vector<Card*>&, std::vector<Card*>&);
private:
	Model* _model;
	View* _view;
};

#endif