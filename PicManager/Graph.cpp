// Graph.cpp : implementation file
//

#include "stdafx.h"
//#include "testdraw.h"
#include "GraphSeries.h"
#include "GraphLegend.h"
#include "math.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraph

CGraph::CGraph()
{
	graphSeries = new CObList();
	tickRange = 100;
	seriesSize = 0;

	graphHasLegend = FALSE;
	legendWidth = 0;

	graphType = 0;

	dataColor[0] = RGB(0,255,0);  //green
	dataColor[1] = RGB(0,0,255);  //blue
	dataColor[2] = RGB(255,0,0);  //red
	dataColor[3] = RGB(255,255,0);  //yellow
	dataColor[4] = RGB(255,153,51);  //orange
	dataColor[5] = RGB(255,51,153);  //hot pink
	dataColor[6] = RGB(153,0,204);  //purple
	dataColor[7] = RGB(0,255,255);  //cyan
	dataColor[8] = RGB(0,0,0);  //black
	dataColor[9] = RGB(255,255,255);  //white

	xAxisAlign = 0;  //horizontal
	xAxisLabelLength = 0;
}

CGraph::CGraph(int type)
{
	graphSeries = new CObList();
	tickRange = 100;
	seriesSize = 0;

	graphHasLegend = FALSE;
	legendWidth = 0;

	graphType = type;

	dataColor[0] = RGB(0,255,0);  //green
	dataColor[1] = RGB(0,0,255);  //blue
	dataColor[2] = RGB(255,0,0);  //red
	dataColor[3] = RGB(255,255,0);  //yellow
	dataColor[4] = RGB(255,153,51);  //orange
	dataColor[5] = RGB(255,51,153);  //hot pink
	dataColor[6] = RGB(153,0,204);  //purple
	dataColor[7] = RGB(0,255,255);  //cyan
	dataColor[8] = RGB(0,0,0);  //black
	dataColor[9] = RGB(255,255,255);  //white

	xAxisAlign = 0;  //horizontal
	xAxisLabelLength = 0;
}

CGraph::~CGraph()
{
}


BEGIN_MESSAGE_MAP(CGraph, CStatic)
	//{{AFX_MSG_MAP(CGraph)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraph message handlers

void CGraph::SetTickSpace(int yDist)
{
	tickSpace = yDist;
}

void CGraph::SetTickRange(int maxTick)
{
	tickRange = maxTick;
}

void CGraph::SetGraphType(int gType)
{
	graphType = gType;
}

void CGraph::SetXAxisAlignment(int alignValue)
{
	xAxisAlign = alignValue;
}

int CGraph::GetXAxisAlignment()
{
	return xAxisAlign;
}

void CGraph::DrawGraph(CDC* pDC)
{
	CString tickLabel;
	CWnd* graphWnd = pDC->GetWindow();
	CRect graphRect;
	graphWnd->GetClientRect(&graphRect);

	maxHeight = graphRect.Height() - 20;  //for frame window and status bar
	maxWidth = graphRect.Width() - 5;  //for frame window
	//We will leave 5 pixels blank on all sides of the graph.  So
	//top-left side of graph is at 5,5 and the bottom-right side of
	//graph is at ((maxHeight - 5), (maxWidth - 5))
	//these settings are altered by axis labels and legends.

	//draw graph title
	CFont titleFont;
	titleFont.CreateFont(28, 0, 0, 0, 700, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
	CFont* pOldFont = (CFont*) pDC->SelectObject(&titleFont);

	pDC->TextOut((maxWidth / 2) - ((graphTitle.GetLength() * 16) / 2),
				10, graphTitle);
	pDC->SelectObject(pOldFont);

	if(graphType == 2)  //pie
	{

		//since pie has not axis lines, set to full size minus 5 on each side
		//these are needed for legend to plot itself
		xAxisWidth = maxWidth - 10;
		yAxisHeight = maxHeight - 20;  //10 buffer and 20 for title
		xApexPoint = 5;
		yApexPoint = maxHeight - 5;
	}
	else
	{
		//X-axis will be raised by 20 pixels for tick-labels
		//Y-axis will be shifted by (max(tick-label size) * 10) + label * 10
		
		tickLabel.Format(_T("%d"), tickRange);

		//determine axis specifications 
			//tick label offset is 4 (for the tick) + 6 (total 10) from axis line
		xApexPoint = 5 + (tickLabel.GetLength() * 8) + 10 + 30/*(axisYLabel.GetLength() * 8)*/ + 5; //allowing 8 pixels per char in tick label
			//y apex based on 5 + 15 (x label) + 4 (for the tick) + 4 (text below tick) + 12 (tick label) + 10
		if(!xAxisAlign)  //horizontal
			yApexPoint = (maxHeight - 5) - 45;		//apex points are the cross section of axis lines
		else
			yApexPoint = (maxHeight - 5) - (xAxisLabelLength * 12) - 10;
		yAxisHeight = yApexPoint - 40;
		xAxisWidth = (maxWidth - 5) - xApexPoint;
	}

	//draw legend
	if(graphHasLegend)
		DrawLegend(pDC);

	if(graphType != 2)  //pie
	{
		//draw axis lines
		DrawAxis(pDC);
	}

	//draw series data and labels
	DrawSeries(pDC);

}

void CGraph::DrawAxis(CDC* pDC)
{
	pDC->SetTextColor(RGB(0,0,0));

	//draw y axis
	pDC->MoveTo(xApexPoint, yApexPoint);  
	pDC->LineTo(xApexPoint, yApexPoint - yAxisHeight);

	//draw x axis
	pDC->MoveTo(xApexPoint, yApexPoint);  
	if(graphHasLegend)
		pDC->LineTo(xApexPoint + (xAxisWidth - legendWidth - 10), yApexPoint);
	else
		pDC->LineTo(xApexPoint + xAxisWidth, yApexPoint);

	//draw labels
	CFont sideFont;
	sideFont.CreateFont(16, 0, 900, 0, 700, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
	CFont* pOldFont = (CFont*) pDC->SelectObject(&sideFont);

	pDC->TextOut(10, (maxHeight / 2) - 6, axisYLabel);
	pDC->SelectObject(pOldFont);

	pDC->TextOut(xApexPoint + (xAxisWidth / 2) - (axisXLabel.GetLength() * 19), maxHeight - 5 - 6, axisXLabel);

	//to allow scalability (height may be less than tickRange)
	double tickScale = 0.00;
	if(tickRange > yAxisHeight)
		tickScale = ((yAxisHeight * 1.00) / (tickRange * 1.00)) * tickSpace;
	else tickScale = tickSpace;

	//draw y axis ticks
	for(int y = 1; y <= tickRange / tickSpace; y++)  //no tick at 0
	{
		int tickYLocation = yApexPoint - (y * tickScale);

		pDC->MoveTo(xApexPoint - 4, tickYLocation);
		pDC->LineTo(xApexPoint + 4, tickYLocation);

		//draw tick label
		CString tickLabel;
		tickLabel.Format(_T("%d"), y * tickSpace);

		pDC->TextOut(xApexPoint - 10 - (tickLabel.GetLength() * 8), tickYLocation - 6, tickLabel);

	}

	//draw X axis tick marks
	POSITION pos;
	pos = graphSeries->GetHeadPosition();
	CGraphSeries* tmpSeries;
	for(int x = 1; x <= graphSeries->GetCount(); x++)
	{
		tmpSeries = (CGraphSeries*)graphSeries->GetNext(pos);

		int seriesSpace;
		int tickXLocation;
		if(graphHasLegend)
			seriesSpace= (xAxisWidth - legendWidth - 10) / graphSeries->GetCount();
		else
			seriesSpace= xAxisWidth / graphSeries->GetCount();
		tickXLocation = xApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

		pDC->MoveTo(tickXLocation,yApexPoint - 4);
		pDC->LineTo(tickXLocation,yApexPoint + 4);

		//draw tick label
		CString tickLabel;
		tickLabel = tmpSeries->GetLabel();
		if(!xAxisAlign)  //horizontal
			pDC->TextOut(tickXLocation - ((tickLabel.GetLength() * 8) / 2), yApexPoint + 8, tickLabel);
		else
		{
			CFont sideFont2;
			sideFont2.CreateFont(16, 0, (xAxisAlign * 10), 0, 700, FALSE, FALSE, 0,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arial"));
			pOldFont = (CFont*) pDC->SelectObject(&sideFont2);
			if(xAxisAlign < 180)
				pDC->TextOut(tickXLocation - 8, yApexPoint + 8 + (xAxisLabelLength * 8), tickLabel);
			else
				pDC->TextOut(tickXLocation + 8, yApexPoint + 8, tickLabel);

			pDC->SelectObject(pOldFont);
		}
	}


}

void CGraph::AddSeries(CGraphSeries* dataSet)
{
	int numData = 0;
	for(int i = 0; i < 10; i++)
	{
		if(dataSet->GetData(i) > 0)
			numData++;
		if(dataSet->GetLabel().GetLength() > xAxisLabelLength)
			xAxisLabelLength = dataSet->GetLabel().GetLength();
	}
	if(numData > seriesSize)
		seriesSize = numData;

	graphSeries->AddTail(dataSet);
}

void CGraph::SetXAxisLabel(CString label)
{
	axisXLabel = label;
}
void CGraph::SetYAxisLabel(CString label)
{
	axisYLabel = label;
}

void CGraph::SetColor(int group, COLORREF groupColor)
{
	dataColor[group] = groupColor;
}

COLORREF CGraph::GetColor(int group)
{
	return dataColor[group];
}

void CGraph::DrawSeries(CDC* pDC)
{
	int barWidth;
	int dataPlotSize;   //used to plot rects of data
	int barL, barT, barR, barB;
	int tickXLocation;
	int seriesSpace;
	double barHeight;  //for scalability
	POSITION pos;
	CGraphSeries* tmpSeries;

	if(graphType == 0) //bar
	{
		//determine width of barchart data blocks
		if(graphHasLegend)
			seriesSpace = (xAxisWidth - legendWidth - 10) / graphSeries->GetCount();
		else
			seriesSpace = xAxisWidth / graphSeries->GetCount();
		barWidth = (seriesSpace * .6) / seriesSize;
		dataPlotSize = seriesSize * barWidth;

		pos = graphSeries->GetHeadPosition();

		for(int x = 1; x <= graphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)graphSeries->GetNext(pos);

			tickXLocation = xApexPoint + ((x * seriesSpace) - (seriesSpace / 2));

			for(int s = 0; s < seriesSize; s++)
			{
				barHeight = 0.00;
				//to allow scalability (height may be less than tickRange)
				double dataScale = 0.00;
				if(tickRange > yAxisHeight)
					dataScale = (yAxisHeight * 1.00) / (tickRange * 1.00);
				else dataScale = 1;
				barHeight = (tmpSeries->GetData(s) * 1.00) * dataScale;
				barL = tickXLocation - (dataPlotSize / 2) + (s * barWidth);
				barT = yApexPoint - barHeight;
				barR = barL + barWidth;
				barB = yApexPoint;
				
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Rectangle(barL, barT, barR, barB);
				pDC->SelectObject(&pOldBrush);
			}
		}
	}

	if(graphType == 1)  //line
	{
		int lastXLoc, lastYLoc;
		for(int s = 0; s < seriesSize; s++)
		{
			//determine width of barchart data blocks
			if(graphHasLegend)
				seriesSpace = (xAxisWidth - legendWidth - 10) / graphSeries->GetCount();
			else
				seriesSpace = xAxisWidth / graphSeries->GetCount();
			barWidth = (seriesSpace * .6) / seriesSize;
			dataPlotSize = seriesSize * barWidth;

			pos = graphSeries->GetHeadPosition();

			for(int x = 1; x <= graphSeries->GetCount(); x++)
			{
				tmpSeries = (CGraphSeries*)graphSeries->GetNext(pos);

				tickXLocation = xApexPoint + ((x * seriesSpace) - (seriesSpace / 2));
				
				barHeight = 0.00;
				//to allow scalability (height may be less than tickRange)
				double dataScale = 0.00;
				if(tickRange > yAxisHeight)
					dataScale = (yAxisHeight * 1.00) / (tickRange * 1.00);
				else dataScale = 1;
				barHeight = (tmpSeries->GetData(s) * 1.00) * dataScale;

				int yDataLocation = yApexPoint - barHeight;
				
				//now have x and y location of center of ellipse
				COLORREF barColor;
				barColor = GetColor(s);
				CBrush brush (barColor);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);
				//draw line back to last data member
				if(x > 1)
				{
					CPen* pOldPen;
					CPen linePen (PS_SOLID, 1, barColor);
					pOldPen = pDC->SelectObject(&linePen);
					pDC->MoveTo(lastXLoc + 2, lastYLoc - 1);
					pDC->LineTo(tickXLocation - 3, yDataLocation - 1);
					pDC->SelectObject(pOldPen);
				}
				//now draw ellipse...
				pDC->Ellipse(tickXLocation - 3, yDataLocation - 3,
					tickXLocation + 3, yDataLocation + 3);
				lastXLoc = tickXLocation;
				lastYLoc = yDataLocation;
				pDC->SelectObject(&pOldBrush);
			}
		}
	}

	if(graphType == 2)  //pie
	{
		double dataSum = 0.00;  //for storing cumulative sum
		int lastXLocation, lastYLocation;
		int newXLocation, newYLocation;
		double percent = 0.00;
		int degrees;
		double totalSum = 0.00;
		int deltaXY;
		int radius;
			
		lastXLocation = 0;
		lastYLocation = 0;

		//determine width of pie display area
		if(graphHasLegend)
			if(((xAxisWidth - legendWidth - 10) / graphSeries->GetCount())
					> (yAxisHeight - 10))
				seriesSpace = (yAxisHeight - 10) / graphSeries->GetCount();
			else
				seriesSpace = (xAxisWidth - legendWidth - 10) / graphSeries->GetCount();
		else
			if(xAxisWidth > yAxisHeight)
				seriesSpace = yAxisHeight / graphSeries->GetCount();
			else
				seriesSpace = xAxisWidth / graphSeries->GetCount();
		double tmpD = (seriesSpace - 60)* .9;  //max width of any pie
		radius = tmpD / 2;  

		int centerYPie = yAxisHeight / 2;
		
		pos = graphSeries->GetHeadPosition();
		for(int x = 1; x <= graphSeries->GetCount(); x++)
		{
			tmpSeries = (CGraphSeries*)graphSeries->GetNext(pos);
			totalSum = 0;
			for(int s = 0; s < 10; s++)
				totalSum += tmpSeries->GetData(s);
			int pieLeft, pieRight;
			if(graphSeries->GetCount() == 1)
			{
				pieLeft = ((xAxisWidth - legendWidth - 10) / 2) - radius - 25;
			}
			else
			{
				pieLeft = xApexPoint + 25 + (x * 50) + ((x - 1) * (2 * radius));
			}
			pieRight = pieLeft + (2 * radius);
			CRect pieRect (pieLeft, 
					centerYPie - radius,
					pieRight, 
					centerYPie + radius);
			int centerXPie = pieLeft + radius;

			//plot series label
			pDC->TextOut(centerXPie - ((tmpSeries->GetLabel().GetLength() * 8) / 2),
						centerYPie + radius + 30, tmpSeries->GetLabel());
			lastXLocation = pieLeft;
			lastYLocation = centerYPie;
			
			dataSum = 0;
			for(int s = 0; s < 10; s++)
			{
				if(tmpSeries->GetData(s) > 0)
				{
					dataSum += tmpSeries->GetData(s);
					percent = (dataSum * 100) / totalSum;
					degrees = (360 * percent) / 100;

						//degress / 90 will never exceed 4.
						//this can tell us the quadrant of destination
					deltaXY = (degrees * radius) / 90;
						//deltaXY is change from start point of pie 0
						//this value is total change.  so if radius is 300
						//and degrees is 270, delta is 300.  The change 
						//would move both x and y 300 pixels.  For x, 100
						//to right is center, another 100 to right edge,
						//100 back to center.  For y, 100 to bottom, 100
						//back to center, 100 to top. thus gives 270 degree
						//rotation.

					//determine destination quadrant...
						//and set newXLocation and newYLocation values...
					int quadrant = degrees / 90;  //truncates decimal
					switch(quadrant)
					{
						//in the computations below, the remarked line is
						//the original computation.  The line above it, for
						//actual use, is the simplified line, and gives the
						//exact same result
						case 0 : newXLocation = pieLeft + deltaXY;
								 newYLocation = centerYPie + deltaXY;
								 break;
						case 1 : newXLocation = pieLeft + deltaXY;
								 newYLocation = centerYPie + (2 * radius) - deltaXY;
//								 newYLocation = centerYPie + radius - (deltaXY - radius);
								 break;
						case 2 : newXLocation = pieLeft + (4 * radius) - deltaXY;
//								 newXLocation = pieLeft + (2 * radius) - (deltaXY - (2 * radius));
								 newYLocation = centerYPie + (2 * radius) - deltaXY;
//								 newYLocation = centerYPie - (deltaXY - (2 * radius));
								 break;
						case 3 : newXLocation = pieLeft + (4 * radius) - deltaXY;
//								 newXLocation = pieLeft + radius - (deltaXY - (3 * radius));
								 newYLocation = centerYPie - (4 * radius) + deltaXY;
//								 newYLocation = centerYPie - radius + (deltaXY - (3 * radius));
								 break;
						case 4 : newXLocation = pieLeft;
								 newYLocation = centerYPie - 1;
								 break;
					}
					
					if(s == 0)
						lastYLocation -= 1;

					CPoint p1 (lastXLocation, lastYLocation);
					CPoint p2 (newXLocation, newYLocation);
					COLORREF barColor;
					barColor = GetColor(s);
					CBrush brush (barColor);
					CBrush* pOldBrush;
					pOldBrush = pDC->SelectObject(&brush);
					pDC->Pie(pieRect, p1, p2); 
					pDC->SelectObject(pOldBrush);

					lastXLocation = newXLocation;
					lastYLocation = newYLocation;
				}
			}
			
		}
	}

}

void CGraph::SetLegend(int datagroup, CString label)
{
	graphLegend.SetLegendText(datagroup, label);
	graphHasLegend = TRUE;
}

void CGraph::DrawLegend(CDC* pDC)
{
	//determine size of legend
	//12 chars per seriesSize + 6 for spacing (3 top and bottom) 
	//+ 1 set for label title(3+12+6) + rectangle (2 chars) + 3 for final bottom buffer
	int legendHeight = 23 + (seriesSize * 18) + 3;
	int legendL, legendT, legendR, legendB;
	int barL, barT, barR, barB;

	legendT = (maxHeight / 2) - (legendHeight / 2);
	legendB = legendT + legendHeight;
	legendR = maxWidth - 5;
	legendL = legendR - ((graphLegend.GetLegendLength() * 12) + 50);
		//allows 50 pixels for display of legend bar 45 + 5 space.
	legendWidth = legendR - legendL;

	pDC->Rectangle(legendL, legendT, legendR, legendB);
	pDC->TextOut(legendL + (legendWidth / 2) - 24, 
					legendT + 3, _T("Legend"));
	for(int i = 0; i < seriesSize; i++)
	{
		//top "Legend" text will use 12 + 3 top + 6 bottom (21 total)
		//each legend label will need 3 chars on top, so the 24 in the offset
		//each label than uses 12 + 3 below + 3 above next label, so 18
		// in the i * offset.  
		pDC->TextOut(legendL + 5, legendT + 24 + (i * 18), graphLegend.GetLegendText(i));

		//draw bar
		COLORREF barColor;
		barColor = GetColor(i);
		CBrush brush (barColor);
		CBrush* pOldBrush;
		pOldBrush = pDC->SelectObject(&brush);

		barL = legendL + 5 + (graphLegend.GetLegendText(i).GetLength() * 8) + 5;
		barT = legendT + 24 + (i * 18) + 1, graphLegend.GetLegendText(i);
		barR = legendR - 5;
		barB = barT + 12;
		pDC->Rectangle(barL, barT, barR, barB);

		pDC->SelectObject(&pOldBrush);

	
	}

}

void CGraph::SetGraphTitle(CString title)
{
	graphTitle = title;
}