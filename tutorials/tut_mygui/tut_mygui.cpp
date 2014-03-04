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
	hge->System_SetState(HGE_HIDEMOUSE, true);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FPS, 100);
	//hge->System_SetState(HGE_ZBUFFER,true);
	hge->System_SetState(HGE_LOGFILE, L"hge_tut_mygui.log");

	mResourceFileName = "MyGUI_Core.xml";
}

void tut_mygui::createScene()
{
    MyGUI::Window* window = MyGUI::Gui::getInstance().createWidget<MyGUI::Window>(
        "WindowCSX",                         //Ƥ��
        MyGUI::IntCoord(200, 200, 400, 150),  //���ꡢ���
        MyGUI::Align::Default,              //���뷽ʽ
        "Main"                              //�������ĸ����ϣ�������MyGUI_Layers.xml
        );
    window->setCaption("");            //��������
    window->setMinSize(80, 80);             //��С�Ĵ�С

	MyGUI::EditBox* mEdit = window->createWidget<MyGUI::EditBox>("EditBoxStretch", MyGUI::IntCoord(0, 0, 100, 100), MyGUI::Align::Default);
	mEdit->setCaption("");
	mEdit->setTextAlign(MyGUI::Align::Center);
	mEdit->setEditMultiLine(true);

	MyGUI::TextBox* mtext = window->createWidget<MyGUI::TextBox>("TextBox", MyGUI::IntCoord(100, 0, 100, 100), MyGUI::Align::Default);
	mtext->setCaption("wo ca");
	mtext->setTextAlign(MyGUI::Align::Center);

}

void tut_mygui::destroyScene()
{
}

bool tut_mygui::Frame()
{
	while(GetInputEvent(0))
	{
	}


	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	drawOneFrame();
	hge->Gfx_EndScene();
	return false;
}

MYGUI_APP(tut_mygui)
