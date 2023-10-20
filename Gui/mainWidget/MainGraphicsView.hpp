/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef __IMAGraphicsView_h__
#define __IMAGraphicsView_h__

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QPixmap>
#include <QMouseEvent>

class MainGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	MainGraphicsView(QGraphicsView * parent = Q_NULLPTR);
	~MainGraphicsView();
public:
	void getMap(QString mapname);

private:
	int bottom, left, top, right, width, height;
	float _scale = 1.0f;
private:
	QGraphicsScene* scene;
	QPixmap* map;

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseReleaseEvent(QMouseEvent *event);
};





#endif






