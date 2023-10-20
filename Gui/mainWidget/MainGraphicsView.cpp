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

#include"MainGraphicsView.hpp"
#include"CpuTools/Common/cpu_Common.hpp"

MainGraphicsView::MainGraphicsView(QGraphicsView * parent) {
	setFrameShadow(Sunken);
	setFrameShape(NoFrame);
	setMinimumHeight(400);
	setMinimumWidth(300);
	setRenderHint(QPainter::Antialiasing);

	map = new QPixmap;
	scene = new QGraphicsScene;

	getMap("./Icons/Background.png");
	
	
	setScene(scene);
	//scene->setBackgroundBrush(QColor(0, 255, 255, 255));

	setCacheMode(CacheBackground);
	scale(_scale, _scale);
}

MainGraphicsView::~MainGraphicsView() {

}


void MainGraphicsView::mouseMoveEvent(QMouseEvent *event) {

}

void MainGraphicsView::mousePressEvent(QMouseEvent *event) {
	//QGraphicsView Position
	QPoint viewPoint = event->pos();
	//QGraphicsScene Position
	QPointF scenePoint = mapToScene(viewPoint);
	(QString::number(scenePoint.x()) + " " + QString::number(scenePoint.y())).toStdString();
}

void MainGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
	//QGraphicsView Position
	QPoint viewPoint = event->pos();
	//QGraphicsScene Position
	QPointF scenePoint = mapToScene(viewPoint);
	(QString::number(scenePoint.x()) + " " + QString::number(scenePoint.y())).toStdString();
}

void MainGraphicsView::drawBackground(QPainter *painter, const QRectF &rect) {
	painter->drawPixmap(int(sceneRect().left()), int(sceneRect().top()), *map);
	
}

void MainGraphicsView::getMap(QString mapname) {
	map->load(mapname);

	width = map->width();
	height = map->height();
	bottom = -0.5 * height;
	left = -0.5 * width;

	scene->setSceneRect(left, bottom, width, height);
}

void MainGraphicsView::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0) {
		_scale = 1.1f;
	}
	else {
		_scale = 0.9f; 
	}
	scale(_scale, _scale); 
}



