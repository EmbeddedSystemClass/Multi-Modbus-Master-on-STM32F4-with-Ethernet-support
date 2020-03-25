/* 
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mbframe.h,v 1.9 2006/12/07 22:10:34 wolti Exp $
 */

#ifndef _RS485_FRAME_H
#define _RS485_FRAME_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

/*!
 * Constants which defines the format of a RS485 frame. The example is
 * shown for a Rs485 frame. Note that the RS485 is not
 * dependent on the underlying transport.
 *
 * <code>
 *  <------------------------------------- RS485 SERIAL LINE (1) -------------------------------->
 *                         <------------------- RS485 PDU(1') --------------------->
 *  |    1 Byte   | 2 Byte |   1 Byte  |   1 Byte       |   1 Byte   |   N Byte    |   2 Byte    |
 *  +-------------+--------+-----------+----------------+------------+-------------+-------------+
 *  | Frame begin | Lenght | Device ID |  Function Code | Frame Type |    Data     |    CRC16    |
 *  +-------------+--------+-----------+----------------+------------+-------------+-------------+
 *
 * </code>
 
/*!
 * Constants which defines the format of a modbus frame. The example is
 * shown for a Modbus RTU/ASCII frame. Note that the Modbus PDU is not
 * dependent on the underlying transport.
 *
 * <code>
 * <------------------------ MODBUS SERIAL LINE PDU (1) ------------------->
 *              <----------- MODBUS PDU (1') ---------------->
 *  +-----------+---------------+----------------------------+-------------+
 *  | Address   | Function Code | Data                       | CRC/LRC     |
 *  +-----------+---------------+----------------------------+-------------+
 *  |           |               |                                   |
 * (2)        (3/2')           (3')                                (4)
 *
 * (1)  ... MB_SER_PDU_SIZE_MAX = 256
 * (2)  ... MB_SER_PDU_ADDR_OFF = 0
 * (3)  ... MB_SER_PDU_PDU_OFF  = 1
 * (4)  ... MB_SER_PDU_SIZE_CRC = 2
 *
 * (1') ... MB_PDU_SIZE_MAX     = 253
 * (2') ... MB_PDU_FUNC_OFF     = 0
 * (3') ... MB_PDU_DATA_OFF     = 1
 * </code>
 */

/* ----------------------- Defines ------------------------------------------*/
#define RS485_PDU_SIZE_MAX     			253 /*!< Maximum size of a RS485. */
#define RS485_PDU_SIZE_MIN     			1  /*!< Function Code */
#define RS485_PDU_FUNC_OFF     			0  /*!< Offset of function code in RS485. */
// #define MB_PDU_DATA_OFF          1  /*!< Offset of Frame Type in RS485. */
#define RS485_PDU_DATA_OFF     			1/*!< Offset for response data in RS485. */
#define MB_PDU_SIZE_MAX     			253 /*!< Maximum size of a RS485. */
#define MB_PDU_SIZE_MIN     			1  /*!< Function Code */
#define MB_PDU_FUNC_OFF     			0  /*!< Offset of function code in RS485. */
// #define MB_PDU_DATA_OFF          1  /*!< Offset of Frame Type in RS485. */
#define MB_PDU_DATA_OFF     			1/*!< Offset for response data in RS485. */


/* ----------------------- Prototypes  0-------------------------------------*/
typedef void    ( *pvRS485FrameStart ) ( UCHAR Port );

typedef void    ( *pvRS485FrameStop ) ( UCHAR Port );

typedef eRS485ErrorCode( *peRS485FrameReceive ) ( UCHAR Port, UCHAR *pucRcvAddress,
																				UCHAR ** pucFrame,
                                        USHORT * pusLength );

typedef eRS485ErrorCode( *peRS485FrameSend ) ( UCHAR Port, UCHAR ucSlaveAddress ,
                                         const UCHAR * pucFrame,
                                         USHORT usLength );

typedef void( *pvRS485FrameClose )(UCHAR port);

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif