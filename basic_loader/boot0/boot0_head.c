/*
 * (C) Copyright 2007-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Jerry Wang <wangflord@allwinnertech.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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

#include "boot0_i.h"

#pragma  arm section  rodata="bt0_head"

#define   DDR3_USED

#ifdef __GNUC__
__attribute__ ((section(".bt0_head")))
#endif
const boot0_file_head_t  BT0_head = {
	                                  {
	      /* jump_instruction */          ( 0xEA000000 | ( ( ( sizeof( boot0_file_head_t ) + sizeof( int ) - 1 ) / sizeof( int ) - 2 ) & 0x00FFFFFF ) ),
							   		      BOOT0_MAGIC,
							   		      STAMP_VALUE,
#ifdef ALIGN_SIZE_8K
									      0x2000,
#else
                                                                              0x4000,
#endif
							   		      sizeof( boot_file_head_t ),
							   		      BOOT_PUB_HEAD_VERSION,
							   		      0,
							   		      0,
							   		      EGON_VERSION,
							   		      {
							   		      	0, 0, '3','.','1','.','0',0
							   		      },
							 	      },
#ifdef  DDR3_USED
							 	      {
							 	          sizeof( boot0_private_head_t ),
							 	          BOOT0_PRVT_HEAD_VERSION,
							 	          { 0 },
							 	          0,
										  {
										  	{ 2, 0, 3, 1, 1, 0, 0, 0},
											{ 2, 1, 3, 1, 1, 0, 0, 0}
										  },
							 	          0,
							 	          { 0 },
							 	          {
										  	{ 6, 0, 2, 1, 2, 0, 0, 0},
											{ 6, 1, 2, 1, 2, 0, 0, 0},
											{ 6, 2, 2, 1, 2, 0, 0, 0},
											{ 6, 3, 2, 1, 2, 0, 0, 0},
											{ 6, 4, 2, 1, 2, 0, 0, 0},
											{ 6, 5, 2, 1, 2, 0, 0, 0},
										  },
										  { 0 }
							 	      }
#else
							 	      {
							 	          sizeof( boot0_private_head_t ),
							 	          BOOT0_PRVT_HEAD_VERSION,
							 	          { 0x40000000,
							 	            1024,
							 	            180,
							 	            1,
							 	            1,
							 	            0,
							 	            (__dram_type_e)1,
							 	            16,
							 	            10,
							 	            14,
							 	            4,
							 	            3,
							 	            0,
							 	            16,
							 	            1024
							 	          },
							 	          0,
										  {
										  	{ 2, 22, 4, 1, 1, 0, 0, 0},
										  	{ 2, 23, 4, 1, 1, 0, 0, 0}
										  },
							 	          0,
							 	          { 0 },
							 	          { 0 },
							 	          { 0 }
							 	      }
#endif
							 	  };



/*******************************************************************************
*
*                  ����Boot_file_head�е�jump_instruction�ֶ�
*
*  jump_instruction�ֶδ�ŵ���һ����תָ�( B  BACK_OF_Boot_file_head )������
*תָ�ִ�к󣬳�����ת��Boot_file_head�����һ��ָ�
*
*  ARMָ���е�Bָ��������£�
*          +--------+---------+------------------------------+
*          | 31--28 | 27--24  |            23--0             |
*          +--------+---------+------------------------------+
*          |  cond  | 1 0 1 0 |        signed_immed_24       |
*          +--------+---------+------------------------------+
*  ��ARM Architecture Reference Manual�����ڴ�ָ�������½��ͣ�
*  Syntax :
*  B{<cond>}  <target_address>
*    <cond>    Is the condition under which the instruction is executed. If the
*              <cond> is ommitted, the AL(always,its code is 0b1110 )is used.
*    <target_address>
*              Specified the address to branch to. The branch target address is
*              calculated by:
*              1.  Sign-extending the 24-bit signed(wro's complement)immediate
*                  to 32 bits.
*              2.  Shifting the result left two bits.
*              3.  Adding to the contents of the PC, which contains the address
*                  of the branch instruction plus 8.
*
*  �ɴ˿�֪����ָ���������8λΪ��0b11101010����24λ����Boot_file_head�Ĵ�С��
*̬���ɣ�����ָ�����װ�������£�
*  ( sizeof( boot_file_head_t ) + sizeof( int ) - 1 ) / sizeof( int )
*                                              ����ļ�ͷռ�õġ��֡��ĸ���
*  - 2                                         ��ȥPCԤȡ��ָ������
*  & 0x00FFFFFF                                ���signed-immed-24
*  | 0xEA000000                                ��װ��Bָ��
*
*******************************************************************************/
