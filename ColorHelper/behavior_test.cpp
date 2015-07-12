#include "stdafx.h"
#include "behavior_test.h"

namespace htmlayout {
	//�Զ����behavior������갴סʱ����Ԫ���л���ͼ��
	//Ԫ�����ԣ�
	//isclick�� ���������ʱΪtrue�����Ϊfalse
	//cur�� ��ʾҪ������ͼ�����Դ��
	test::test() : behavior(HANDLE_ALL, "test") {

	}

	void test::attached(HELEMENT he)
	{

	}

	void test::detached(HELEMENT he)
	{

	}

	BOOL test::on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc) {
		//Ҫ���ػ��Ԫ��
		dom::element el = he;
		//���Ҫ�ͷŵĶ���
		HDC hcdc;
		HBITMAP hbm;
		HGDIOBJ old_obj;
		//�������Ԫ�ص����Ͻ�����
		RECT rect = rc;
		//λͼ��Ϣ
		BITMAP bitmap;

		std::wstring str = el.get_attribute("isclick");
		if (L"true" == str){
			return false;
		}
		//���Ԫ�ص�cur���ԣ���������Ӧ��λͼ
		str = el.get_attribute("cur");
		int curId = _wtoi(str.c_str());
		hbm = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(curId));
		GetObject(hbm, sizeof(BITMAP), &bitmap);
		//��������DC
		hcdc = CreateCompatibleDC(hdc);
		//ѡ��λͼ
		old_obj = SelectObject(hcdc, hbm);
		//�����ξ��У�������λͼ
		rect.left += (rc.right - rc.left) / 2 - bitmap.bmWidth / 2;
		rect.top += (rc.bottom - rc.top) / 2 - bitmap.bmHeight / 2;
		//������DC�����ݻ���hdc��
		TransparentBlt(hdc, rect.left, rect.top, bitmap.bmWidth, bitmap.bmHeight, hcdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 255, 255));
		//��ԭ�ɵ�λͼ
		SelectObject(hcdc, old_obj);
		//�ͷ���Դ
		DeleteObject(hbm);
		DeleteObject(hcdc);
		return false; /*do default draw*/
	}

	BOOL test::on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates) {
		switch (event_type) {
		case MOUSE_DOWN:
			switch (mouseButtons) {
			case MAIN_MOUSE_BUTTON:
				mouse_left_down(he);
				break;
			default:
				break;
			}
			break;
		case MOUSE_UP:
			switch (mouseButtons) {
			case MAIN_MOUSE_BUTTON:
				mouse_left_UP(he);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		//
		return false;
	}

	void test::mouse_left_down(dom::element el) {
		el.set_attribute("isclick", L"true");
		el.set_capture();
		el.update(true);
	}
	void test::mouse_left_UP(dom::element el) {
		el.set_attribute("isclick", L"false");
		el.release_capture();
		el.update(true);
	}

	test test_instance;
}