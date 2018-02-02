#pragma once

/************************************************************************/
/* 

绘制曲线

*/
/************************************************************************/


#include <deque>


class CCurveDraw
{
public:
	CCurveDraw(void)
	{
		m_color=RGB(255,0,0);

		list_init();
	}

	~CCurveDraw(void)
	{

	}

	void Draw(CRect rect,CDC* pDC,int height_1024kb )
	{
 
		CPen pen(0,1,m_color);  

		 
		pDC->SelectObject(pen);

		 

		for (int i=0;i<m_lst.size();i++)
		{
			int kb=m_lst[i];//改为 1M/s 网速分隔1行
			int yy=rect.bottom-((float)kb/1024)*height_1024kb-2;
			if (i==0)
				pDC->MoveTo(0,yy);
			else
				pDC->LineTo((i+1)*5,yy);
		}

	 
	}

	void list_adddata(int kb)
	{
		m_lst.push_front(kb);
		m_lst.pop_back();
	}

	void SetColor(COLORREF col)
	{
		m_color=col;
	}

private:

	void list_init()
	{
		for (int i=0;i<60;i++)
		{
			m_lst.push_front(0);
		}
	}

	 
	COLORREF	m_color;

	std::deque<int> m_lst;

};
