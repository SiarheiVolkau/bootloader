/*
 * (C) Copyright 2007-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Jerry Wang <wangflord@allwinnertech.com>
 *
 * (C) Copyright 2017
 * Siarhei Volkau <lis8215@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */



.ifndef __egon2_inc
.set __egon2_inc, 1

.set ARMV7_USR_MODE,	0x10
.set ARMV7_FIQ_MODE,	0x11
.set ARMV7_IRQ_MODE,	0x12
.set ARMV7_SVC_MODE,	0x13
.set ARMV7_MON_MODE,	0x16
.set ARMV7_ABT_MODE,	0x17
.set ARMV7_UND_MODE,	0x1b
.set ARMV7_SYSTEM_MODE,	0x1f
.set ARMV7_MODE_MASK,	0x1f
.set ARMV7_FIQ_MASK,	0x40
.set ARMV7_IRQ_MASK,	0x80


//coprocessor CP15
//C1
.set ARMV7_THUMB_MASK,	(1<<5)
.set ARMV7_END_MASK,	(1<<9)

.set ARMV7_IT_MASK,  	((0x3f<<10)|(0x03<<25))
.set ARMV7_GE_MASK,  	(0x0f<<16)
.set ARMV7_JAVA_MASK,	(1<<24)

.set ARMV7_QFLAG_BIT,	(1 << 27)
.set ARMV7_CC_V_BIT,	(1 << 28)
.set ARMV7_CC_C_BIT,	(1 << 29)
.set ARMV7_CC_Z_BIT,	(1 << 30)
.set ARMV7_CC_N_BIT,	(1 << 31)
.set ARMV7_CC_E_BIT,	(1 << 9)

.set ARMV7_C1_M_BIT,	(1 << 0)
.set ARMV7_C1_A_BIT,	(1 << 1)
.set ARMV7_C1_C_BIT,	(1 << 2)
.set ARMV7_C1_Z_BIT,	(1 << 11)
.set ARMV7_C1_I_BIT,	(1 << 12)


.set BOOT0_STACK_BOTTOM,	(0x00048000)


.endif

