/*****************************************************************************
* Product: DPP example
* Last Updated for Version: 6.0.4
* Date of the Last Update:  2018-01-09
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2005-2018 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* https://state-machine.com
* mailto:info@state-machine.com
*****************************************************************************/
#include "qpc.h"
#include "bsp.h"
#include "Blinky.h"
#include "usart.h"

enum BlinkySignals {
	TIMEOUT_SIG = Q_USER_SIG,
	MAX_SIG
};

QActive *AO_Blinky = &l_blinky.super;

static void Blinky_ctor(void) {
	Blinky *me = (Blinky *)AO_Blinky;
	QActive_ctor(&me->super, (QStateHandler)&Blinky_initial);
	QTimeEvt_ctor(&me->timeEvt, TIMEOUT_SIG);
}

int main() {
	static QEvt const *blinky_queueSto[10];	/* 这行挪到这里 */
	BSP_init();                   			/* 自己添加这行,定义在bsp.c */
	Blinky_ctor();
	QF_init();

	QACTIVE_START(AO_Blinky, 1,
		blinky_queueSto, Q_DIM(blinky_queueSto),
		(void *)0, 1024, (QEvt *)0);
	return QF_run();
}

