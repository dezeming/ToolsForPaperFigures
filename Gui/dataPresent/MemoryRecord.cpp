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

#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib") 

#include"utility/Status.hpp"

void showMemoryInfo(void) {

	//  SIZE_T PeakWorkingSetSize; //峰值内存使用
	//  SIZE_T WorkingSetSize; //内存使用
	//  SIZE_T PagefileUsage; //虚拟内存使用
	//  SIZE_T PeakPagefileUsage; //峰值虚拟内存使用

	EmptyWorkingSet(GetCurrentProcess());

	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));

	m_Status.setDataChanged("Memory Use", "WorkingSetSize", QString::number(pmc.WorkingSetSize / 1000.f / 1000.f), "M");
	m_Status.setDataChanged("Memory Use", "PeakWorkingSetSize", QString::number(pmc.PeakWorkingSetSize / 1000.f / 1000.f), "M");
	m_Status.setDataChanged("Memory Use", "PagefileUsage", QString::number(pmc.PagefileUsage / 1000.f / 1000.f), "M");
	m_Status.setDataChanged("Memory Use", "PeakPagefileUsage", QString::number(pmc.PeakPagefileUsage / 1000.f / 1000.f), "M");

}


