#pragma once
#include "stdafx.h"

namespace htmlayout {
	//�Զ����behavior������갴סʱ����Ԫ���л���ͼ��
	//Ԫ�����ԣ�
	//isclick ���������ʱΪtrue�����Ϊfalse
	//cur ��ʾҪ������ͼ�����Դ��
	class test : public behavior {
		//htmlayout::debug_output_console dc;
	public:
		test();

		virtual void attached(HELEMENT he);
		virtual void detached(HELEMENT he);

		virtual BOOL on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc);
		virtual BOOL on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates);
	};
}