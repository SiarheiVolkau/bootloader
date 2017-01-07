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

#ifndef  __load_boot1_from_sdmmc_h
#define  __load_boot1_from_sdmmc_h

//SD��������ݽṹ
typedef struct _boot_sdcard_info_t
{
	__s32               card_ctrl_num;                //�ܹ��Ŀ��ĸ���
	__s32				boot_offset;                  //ָ��������֮���߼�����������Ĺ���
	__s32 				card_no[4];                   //��ǰ�����Ŀ���, 16-31:GPIO��ţ�0-15:ʵ�ʿ����������
	__s32 				speed_mode[4];                //�����ٶ�ģʽ��0�����٣�����������
	__s32				line_sel[4];                  //�������ƣ�0: 1�ߣ�������4��
	__s32				line_count[4];                //��ʹ���ߵĸ���
}
boot_sdcard_info_t;
/*******************************************************************************
*��������: load_boot1_from_spinor
*����ԭ�ͣ�int32 load_boot1_from_spinor( void )
*��������: ��һ�ݺõ�Boot1��spi nor flash�����뵽SRAM�С�
*��ڲ���: void
*�� �� ֵ: OK                         ���벢У��ɹ�
*          ERROR                      ���벢У��ʧ��
*��    ע:
*******************************************************************************/
extern __s32 load_boot1_from_sdmmc( char *buf);



#endif     //  ifndef __load_boot1_from_spi_nor_h

/* end of load_boot1_from_spinor.h */
