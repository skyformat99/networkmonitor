/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015 simawei<simawei@qq.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
*/


#pragma once

/************************************************************************/
/* 

»æÖÆÇúÏß

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

	void Draw(CRect rect,CDC* pDC,int height_100kb )
	{
 
		CPen pen(0,1,m_color);  

		 
		pDC->SelectObject(pen);

		 

		for (int i=0;i<m_lst.size();i++)
		{
			int kb=m_lst[i];
			int yy=rect.bottom-((float)kb/128)*height_100kb-2;
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
