#pragma once 

#include "BaseManager.h"

class tut_mygui :
	public base::BaseManager
{
public:
	tut_mygui();
	virtual ~tut_mygui(){};

	virtual void prepare();

	virtual void createScene();
	virtual void destroyScene();

	virtual bool Frame();
};
