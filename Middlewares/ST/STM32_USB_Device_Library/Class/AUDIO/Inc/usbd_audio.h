/**
  ******************************************************************************
  * @file    usbd_audio.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_audio.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_AUDIO_H
#define __USB_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_AUDIO
  * @brief This file is the Header file for usbd_audio.c
  * @{
  */


/** @defgroup USBD_AUDIO_Exported_Defines
  * @{
  */


/**
  * @}
  */
#define MIDI_IN_EP                                   0x81  /* EP1 for data IN */
#define MIDI_OUT_EP                                  0x01  /* EP1 for data OUT */

#define USB_MIDI_CONFIG_DESC_SIZ                     133 //101
#define MIDI_DATA_FS_MAX_PACKET_SIZE                 64  /* Endpoint IN & OUT Packet size */
#define MIDI_DATA_IN_PACKET_SIZE                     MIDI_DATA_FS_MAX_PACKET_SIZE
#define MIDI_DATA_OUT_PACKET_SIZE                    MIDI_DATA_FS_MAX_PACKET_SIZE

#define APP_RX_DATA_SIZE                             (MIDI_DATA_FS_MAX_PACKET_SIZE * 32) //buffer to send


#define USB_TX_READY            0       //ready for transfer
#define USB_TX_BUSY             1       //busy
#define USB_TX_CONTINUE         2       //ready to continue tx next packet (64 bit)
/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef struct
{
  uint8_t cmd;
  uint8_t data[USB_MAX_EP0_SIZE];
  uint8_t len;
  uint8_t unit;
} USBD_AUDIO_ControlTypeDef;

/*
typedef struct
{
  uint32_t alt_setting;
  uint8_t buffer[AUDIO_TOTAL_BUF_SIZE];
  AUDIO_OffsetTypeDef offset;
  uint8_t rd_enable;
  uint16_t rd_ptr;
  uint16_t wr_ptr;
  USBD_AUDIO_ControlTypeDef control;
} USBD_AUDIO_HandleTypeDef;
*/

typedef struct
{
  int8_t (*Init)(uint32_t AudioFreq, uint32_t Volume, uint32_t options);
  int8_t (*DeInit)(uint32_t options);
  int8_t (*AudioCmd)(uint8_t *pbuf, uint32_t size, uint8_t cmd);
  uint8_t (*MidiRx)(uint8_t *msg, uint16_t length);
  uint8_t (*MidiTx)(uint8_t *msg, uint16_t length);
} USBD_AUDIO_ItfTypeDef;

extern uint8_t APP_Rx_Buffer   [APP_RX_DATA_SIZE];
extern uint32_t APP_Rx_ptr_in;
extern uint32_t APP_Rx_ptr_out;
extern uint32_t APP_Rx_length;
extern uint8_t  USB_Tx_State;

/**
  * @}
  */



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef USBD_AUDIO;
#define USBD_AUDIO_CLASS &USBD_AUDIO
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
uint8_t USBD_AUDIO_RegisterInterface(USBD_HandleTypeDef *pdev,
                                     USBD_AUDIO_ItfTypeDef *fops);

void USBD_MIDI_SendPacket(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_AUDIO_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
