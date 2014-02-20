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
        "Window",                         //Ƥ��
        MyGUI::IntCoord(0, 0, 200, 100),  //���ꡢ���
        MyGUI::Align::Default,              //���뷽ʽ
        "Main"                              //�������ĸ����ϣ�������MyGUI_Layers.xml
        );
    window->setCaption("");            //��������
    window->setMinSize(80, 80);             //��С�Ĵ�С

    //����λ�ڶԻ�����İ�ť
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
