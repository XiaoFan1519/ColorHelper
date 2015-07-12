#pragma once
#include "stdafx.h"

namespace htmlayout {
	//�Զ����behavior�������������λ�õ�ͼ��
	//Ԫ�����ԣ�
	//update true��ʾ����Ԫ�ص�ͼ��Ϊ��ǰ���λ�õ�ͼ��false��ʹ�û����е�ͼ��
	//multiple ��ͼ��Ŵ�ı���
	class magnifyScrn : public behavior {
	private:
		htmlayout::debug_output_console dc;
		int elementWidht;
		int elementHeight;
		int multiple;
		//�Ŵ�ǰ��ͼ���С
		int width;
		int height;
		//����λͼ
		HBITMAP hBitMap;
		bool iscreate = false;
	public:
		magnifyScrn();
		~magnifyScrn();

		virtual void attached(HELEMENT he);
		virtual void detached(HELEMENT he);

		virtual BOOL on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc);
		virtual BOOL on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates);
	};
}