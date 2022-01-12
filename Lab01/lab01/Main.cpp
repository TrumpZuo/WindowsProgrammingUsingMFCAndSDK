
#include"MyGame.h"
/*******************************************************************
函数：WinMain ()
功能：Win32 应用程序入口函数。创建主窗口，处理消息循环
********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,         //当前实例句柄
	HINSTANCE hPrevInstance,     //前一个实例句柄
	PSTR szCmdLine,              //命令行字符
	int iCmdShow)                //窗口显示方式 
{
	MSG msg;
	//创建主窗口
	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;
	//进入消息循环：从该应用程序的消息队列中检取消息，
	//送到消息处理过程，当检取到WM_QUIT消息时，退出消息循环。
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



