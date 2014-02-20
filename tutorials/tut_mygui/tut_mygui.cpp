#include "Precompiled.h"
#include "tut_mygui.h"
#include "myguiMain.h"

tut_mygui::tut_mygui()
{
}

void tut_mygui::prepare()
{
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FPS, 100);
	//hge->System_SetState(HGE_ZBUFFER,true);
	hge->System_SetState(HGE_LOGFILE, L"hge.log");
}

void tut_mygui::createScene()
{
    MyGUI::Window* window = MyGUI::Gui::getInstance().createWidget<MyGUI::Window>(
        "Window",                         //皮肤
        MyGUI::IntCoord(0, 0, 200, 100),  //坐标、宽高
        MyGUI::Align::Default,              //对齐方式
        "Main"                              //创建于哪个层上，定义在MyGUI_Layers.xml
        );
    window->setCaption("");            //标题名称
    window->setMinSize(80, 80);             //最小的大小

    //创建位于对话框里的按钮
    MyGUI::Button* button = window->createWidget<MyGUI::Button>(
        "Button",
        MyGUI::IntCoord(10, 10, 50, 30), 
        MyGUI::Align::Default
        );
    button->setCaption("Button");
}

void tut_mygui::destroyScene()
{
}

MYGUI_APP(tut_mygui)
