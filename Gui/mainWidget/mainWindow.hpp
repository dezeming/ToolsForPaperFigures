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

#ifndef __mainWindow_hpp__
#define __mainWindow_hpp__

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>

class DataPresentDockWidget;
class DisplayWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private:
	QWidget* centralWidget;
	QVBoxLayout* MainWindowLayout;

	DisplayWidget* m_DisplayWidget;

	DataPresentDockWidget* m_DataPresentDockWidget;

private:
	void setMenu(void);
	void setWidget(void);
	void setDock(void);
};





#endif






