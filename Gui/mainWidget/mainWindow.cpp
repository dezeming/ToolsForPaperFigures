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

#include "mainWindow.hpp"
#include "dataPresent/DataPresentDockWidget.hpp"
#include "mainWidget/DisplayWidget.hpp"

void testCode_Dez_1();

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{

	setMinimumSize(800, 800);

	MainWindowLayout = new QVBoxLayout;
	MainWindowLayout->setAlignment(Qt::AlignCenter);

	centralWidget = new QWidget;
	centralWidget->setLayout(MainWindowLayout);
	setCentralWidget(centralWidget);

	setMenu();

	setWidget();

	setDock();


	testCode_Dez_1();
}

MainWindow::~MainWindow() {

}

void MainWindow::setMenu(void) {


}

void MainWindow::setWidget(void) {
	
	m_DisplayWidget = new DisplayWidget;
	MainWindowLayout->addWidget(m_DisplayWidget);

}

void MainWindow::setDock(void) {

	m_DataPresentDockWidget = new DataPresentDockWidget;
	addDockWidget(Qt::LeftDockWidgetArea, m_DataPresentDockWidget);


}







