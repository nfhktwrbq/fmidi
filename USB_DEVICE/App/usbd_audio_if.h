/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_audio_if.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_audio_if.c file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_AUDIO_IF_H__
#define __USBD_AUDIO_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_audio.h"

/* USER CODE BEGIN INCLUDE */
#define USBMIDIBUFSIZE 2048 //must be power of 2
#define USBMIDIMASK (USBMIDIBUFSIZE-1)

typedef struct
{
uint16_t curidx; //current pointer position
uint16_t rdidx;  //reading pointer position
uint8_t buf[USBMIDIBUFSIZE];
} tUsbMidiCable;

extern tUsbMidiCable usbmidicable1; //rx buf for virtual midi cable 1
extern tUsbMidiCable usbmidicable2; //rx buf for vortual midi cable 2

/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief For Usb device.
  * @{
  */

/** @defgroup USBD_AUDIO_IF USBD_AUDIO_IF
  * @brief Usb audio interface device module.
  * @{
  */

/** @defgroup USBD_AUDIO_IF_Exported_Defines USBD_AUDIO_IF_Exported_Defines
  * @brief Defines.
  * @{
  */

/* USER CODE BEGIN EXPORTED_DEFINES */

/* USER CODE END EXPORTED_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Exported_Types USBD_AUDIO_IF_Exported_Types
  * @brief Types.
  * @{
  */

/* USER CODE BEGIN EXPORTED_TYPES */

/* USER CODE END EXPORTED_TYPES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Exported_Macros USBD_AUDIO_IF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* USER CODE BEGIN EXPORTED_MACRO */

/* USER CODE END EXPORTED_MACRO */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Exported_Variables USBD_AUDIO_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/** AUDIO_IF Interface callback. */
extern USBD_AUDIO_ItfTypeDef USBD_AUDIO_fops_FS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Exported_FunctionsPrototype USBD_AUDIO_IF_Exported_FunctionsPrototype
  * @brief Public functions declaration.
  * @{
  */

/**
  * @brief  Manages the DMA full transfer complete event.
  * @retval None
  */
void TransferComplete_CallBack_FS(void);

/**
  * @brief  Manages the DMA half transfer complete event.
  * @retval None
  */
void HalfTransfer_CallBack_FS(void);

/* USER CODE BEGIN EXPORTED_FUNCTIONS */
//Create NoteOn buffer
void USBD_AddNoteOn(uint8_t cable, uint8_t ch, uint8_t note, uint8_t vel);
void USBD_AddNoteOff(uint8_t cable, uint8_t ch, uint8_t note, uint8_t vel);
void USBD_AddPithBend(uint8_t cable, uint8_t ch, uint value);
void USBD_SendMidiMessages(void);
/* USER CODE END EXPORTED_FUNCTIONS */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_AUDIO_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
