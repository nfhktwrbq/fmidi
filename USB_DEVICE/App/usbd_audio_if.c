/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_audio_if.c
  * @version        : v1.0_Cube
  * @brief          : Generic media access layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
 /* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_audio_if.h"

/* USER CODE BEGIN INCLUDE */
#define NEXTBYTE(idx, mask) (mask & (idx + 1))

tUsbMidiCable usbmidicable1;
tUsbMidiCable usbmidicable2;
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_AUDIO_IF
  * @{
  */

/** @defgroup USBD_AUDIO_IF_Private_TypesDefinitions USBD_AUDIO_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Private_Defines USBD_AUDIO_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Private_Macros USBD_AUDIO_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Private_Variables USBD_AUDIO_IF_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Exported_Variables USBD_AUDIO_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Private_FunctionPrototypes USBD_AUDIO_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */
static int8_t AUDIO_Init_FS(uint32_t AudioFreq, uint32_t Volume, uint32_t options);
static int8_t AUDIO_DeInit_FS(uint32_t options);
static int8_t AUDIO_AudioCmd_FS(uint8_t* pbuf, uint32_t size, uint8_t cmd);
static uint8_t MIDI_DataRx_FS(uint8_t *msg, uint16_t length);
static uint8_t MIDI_DataTx_FS(uint8_t *msg, uint16_t length);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_AUDIO_ItfTypeDef USBD_AUDIO_fops_FS =
{
  AUDIO_Init_FS,
  AUDIO_DeInit_FS,
  AUDIO_AudioCmd_FS,
  MIDI_DataRx_FS,
  MIDI_DataTx_FS,
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the AUDIO media low layer over USB FS IP
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @param  Volume: Initial volume level (from 0 (Mute) to 100 (Max))
  * @param  options: Reserved for future use 
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t AUDIO_Init_FS(uint32_t AudioFreq, uint32_t Volume, uint32_t options)
{
  /* USER CODE BEGIN 0 */
  UNUSED(AudioFreq);
  UNUSED(Volume);
  UNUSED(options);
  return (USBD_OK);
  /* USER CODE END 0 */
}

/**
  * @brief  De-Initializes the AUDIO media low layer
  * @param  options: Reserved for future use
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t AUDIO_DeInit_FS(uint32_t options)
{
  /* USER CODE BEGIN 1 */
  UNUSED(options);
  return (USBD_OK);
  /* USER CODE END 1 */
}

/**
  * @brief  Handles AUDIO command.
  * @param  pbuf: Pointer to buffer of data to be sent
  * @param  size: Number of data to be sent (in bytes)
  * @param  cmd: Command opcode
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t AUDIO_AudioCmd_FS(uint8_t* pbuf, uint32_t size, uint8_t cmd)
{
  /* USER CODE BEGIN 2 */

  UNUSED(pbuf);
  UNUSED(size);
  UNUSED(cmd);
  return (USBD_OK);
  /* USER CODE END 2 */
}

//fill midi tx buffer
static uint8_t MIDI_DataTx_FS(uint8_t *msg, uint16_t length)
{
  uint16_t i = 0;
  while (i < length) {
    APP_Rx_Buffer[APP_Rx_ptr_in] = *(msg + i);
    APP_Rx_ptr_in++;
    i++;
    if (APP_Rx_ptr_in == APP_RX_DATA_SIZE) {
      APP_Rx_ptr_in = 0;
    }
  }
  return (USBD_OK);
}


//process recived midi data
static uint8_t MIDI_DataRx_FS(uint8_t* msg, uint16_t length)
{
  uint16_t cnt;
  //uint16_t chk = length % 4; //if (chk != 0) return;
  //uint16_t *pid;
  //uint8_t *pbuf;
  tUsbMidiCable* pcable;

  for (cnt = 0; cnt < length; cnt += 4)
  {
    switch ( msg[cnt] >> 4 ) {
    case 0:
      pcable = &usbmidicable1;
      break;
    case 1:
      pcable = &usbmidicable2;
      break;
    default:
      continue;
    };

    switch ( msg[cnt] & 0x0F ) {
    case 0x0:
    case 0x1:
      continue;
    case 0x5:
    case 0xF:
      pcable->buf[ pcable->curidx ] = msg[ cnt+1 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      break;
    case 0x2:
    case 0x6:
    case 0xC:
    case 0xD:
      pcable->buf[ pcable->curidx ] = msg[ cnt+1 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      pcable->buf[ pcable->curidx ] = msg[ cnt+2 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      break;
    default:
      pcable->buf[ pcable->curidx ] = msg[ cnt+1 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      pcable->buf[ pcable->curidx ] = msg[ cnt+2 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      pcable->buf[ pcable->curidx ] = msg[ cnt+3 ];
      pcable->curidx = NEXTBYTE(pcable->curidx, USBMIDIMASK);
      break;
    };
  };

  return (USBD_OK);
}

void USBD_SendMidiMessages(void)
{
  if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED)
  {
    if (!USB_Tx_State)
      USBD_MIDI_SendPacket();
    else
      USB_Tx_State = USB_TX_CONTINUE;
  }
  else
  {
      USB_Tx_State = USB_TX_READY;
  }
}


/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
void USBD_AddNoteOn(uint8_t cable, uint8_t ch, uint8_t note, uint8_t vel)
{
  //uint8_t cable = 0;
  uint8_t txbuf[4];

  if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) return;
  cable <<= 4;
  txbuf[0] = cable + 0x9;
  txbuf[1] = 0x90 | ch;
  txbuf[2] = 0x7F & note;
  txbuf[3] = 0x7F & vel;
  MIDI_DataTx_FS(txbuf, 4);
}

void USBD_AddNoteOff(uint8_t cable, uint8_t ch, uint8_t note, uint8_t vel)
{
  //uint8_t cable = 0;
  uint8_t txbuf[4];

  if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) return;
  cable <<= 4;
  txbuf[0] = cable + 0x8;
  txbuf[1] = 0x80 | ch;
  txbuf[2] = 0x7F & note;
  txbuf[3] = 0x7F & vel;
  MIDI_DataTx_FS(txbuf, 4);
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
