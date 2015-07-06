#include "stdafx.h"
#include "behavior_manifyScrn.h"
namespace htmlayout {
	//�Զ����behavior�������������λ�õ�ͼ��
	//Ԫ�����ԣ�
	//update true��ʾ����Ԫ�ص�ͼ��Ϊ��ǰ���λ�õ�ͼ��false��ʹ�û����е�ͼ��
	//multiple ��ͼ��Ŵ�ı���

	magnifyScrn::magnifyScrn() : behavior(HANDLE_ALL, "magnifyScrn") {

	}

	void magnifyScrn::attached(HELEMENT he)
	{
		dom::element el = he;
		//��ȡԪ�صĴ�С
		elementWidht = styleToInt(el.get_style_attribute("width"));
		elementHeight = styleToInt(el.get_style_attribute("height"));
		multiple = _wtoi(el.get_attribute("multiple"));
		//�Ŵ�ǰ��ͼ���С
		width = ceil(elementWidht / multiple);
		height = ceil(elementHeight / multiple);
	}

	void magnifyScrn::detached(HELEMENT he)
	{

	}

	BOOL magnifyScrn::on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc) {
		
		//������Ļ��DC�����ڻ�ȡͼ��
		HDC fullDC = GetDC(nullptr);
		//������λ��
		POINT pt;
		GetCursorPos(&pt);
		//�洢Ҫȡ��ͼ��ķ�Χ
		RECT rect;
		rect.left = pt.x - (width / 2);
		rect.top = pt.y - (height / 2);
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;

		//��ȫ����DC�������ڴ����ٽ���GetPixel�����߻����������


		//��������λͼ�ͼ���DC
		HBITMAP hBitMap = CreateCompatibleBitmap(fullDC, width, height);
		HDC cdc = CreateCompatibleDC(fullDC);
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				COLORREF color = GetPixel(fullDC, rect.left + j, rect.top + i);
				drawPixel(cdc, j, i, color, multiple);
			}
		}
		//�ͷ���Դ
		DeleteDC(cdc);
		DeleteObject(hBitMap);
		ReleaseDC(nullptr, fullDC);
		return true; /*do default draw*/
	}

	BOOL magnifyScrn::on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates) {
		return false;
	}

	magnifyScrn magnifyScrn_instance;
	/*
	class magnifyScrn : public behavior {
	public:
		magnifyScrn::magnifyScrn() : behavior(HANDLE_ALL, "magnifyScrn") {

		}
		htmlayout::debug_output_console dc;

		virtual void attached(HELEMENT he)
		{
			
		}

		virtual void detached(HELEMENT he)
		{
			
		}

		virtual BOOL on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc) {
			dom::element el = he;
			//��ȡԪ�صĴ�С
			int elementWidht = styleToInt(el.get_style_attribute("width"));
			int elementHeight = styleToInt(el.get_style_attribute("height"));
			int multiple = _wtoi(el.get_attribute("multiple"));
			//�Ŵ�ǰ��ͼ���С
			int width = ceil(elementWidht / multiple);
			int height = ceil(elementHeight / multiple);
			//������Ļ��DC�����ڻ�ȡͼ��
			HDC fullDC = GetDC(nullptr);
			//��������λͼ�ͼ���DC
			HBITMAP hBitMap = CreateCompatibleBitmap(fullDC, width, height);
			HDC cdc = CreateCompatibleDC(fullDC);
			//������λ��
			POINT pt;
			GetCursorPos(&pt);
			//�洢Ҫȡ��ͼ��ķ�Χ
			RECT rect;
			rect.left = pt.x - (width / 2);
			rect.top = pt.y - (height / 2);
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					COLORREF color = GetPixel(fullDC, rect.left + j, rect.top + i);
					drawPixel(cdc, j, i, color, multiple);
				}
			}
			//�ͷ���Դ
			DeleteDC(cdc);
			DeleteObject(hBitMap);
			ReleaseDC(nullptr, fullDC);
			return true; //do default draw
		}
		virtual BOOL on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates) {
			return false;
		}
	};
	*/
}