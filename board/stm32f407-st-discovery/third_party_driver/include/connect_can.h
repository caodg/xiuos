/*
* Copyright (c) 2020 AIIT XUOS Lab
* XiUOS is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*        http://license.coscl.org.cn/MulanPSL2
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
* See the Mulan PSL v2 for more details.
*/
 
/**
* @file connect_can.h
* @brief define aiit-arm32-board can function and struct
* @version 1.0 
* @author AIIT XUOS Lab
* @date 2021-04-22
*/

#ifndef CONNECT_CAN_H
#define CONNECT_CAN_H

#include "hardware_can.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Stm32Can
{
    CAN_TypeDef *instance;

    char *bus_name;

    CAN_InitTypeDef init;

    uint8 can_flag;
    struct CanBus can_bus;
};

int Stm32HwCanBusInit(void);

#ifdef __cplusplus
}
#endif

#endif