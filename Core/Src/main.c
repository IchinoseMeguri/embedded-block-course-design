/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PB0 GPIOB, GPIO_PIN_0
#define PB1 GPIOB, GPIO_PIN_1
#define PB2 GPIOB, GPIO_PIN_2
#define PB3 GPIOB, GPIO_PIN_3
#define PB4 GPIOB, GPIO_PIN_4
#define PB5 GPIOB, GPIO_PIN_5
#define PB6 GPIOB, GPIO_PIN_6
#define PB7 GPIOB, GPIO_PIN_7

#define E GPIOB, GPIO_PIN_12
#define RW GPIOB, GPIO_PIN_11
#define RS GPIOB, GPIO_PIN_10
#define CS1 GPIOB, GPIO_PIN_8
#define CS2 GPIOB, GPIO_PIN_9

#define SIGNAL GPIOC, GPIO_PIN_0
#define LEFT GPIOC, GPIO_PIN_1
#define RIGHT GPIOC, GPIO_PIN_2
#define DOWN GPIOC, GPIO_PIN_4

#define TYPE1 GPIOC, GPIO_PIN_5
#define TYPE0 GPIOC, GPIO_PIN_6
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int score = 0;
int startflag = 0;
int map[8][7];  //每个格子的黑白，黑为1，白�?0
int R[3], L[3]; //正在控制的块的行列位�?
int blocktype = 0;
uint16_t ADC_Value = 0;
uint8_t button[1] = {0x00};
char c_huan[] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    0x04, 0x24, 0x44, 0x84, 0x64, 0x9C, 0x40, 0x30, 0x0F, 0xC8, 0x08, 0x08, 0x28, 0x18, 0x00, 0x00,
    0x10, 0x08, 0x06, 0x01, 0x82, 0x4C, 0x20, 0x18, 0x06, 0x01, 0x06, 0x18, 0x20, 0x40, 0x80, 0x00};
char c_ying[] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    0x40, 0x40, 0x42, 0xCC, 0x00, 0x00, 0xFC, 0x04, 0x02, 0x00, 0xFC, 0x04, 0x04, 0xFC, 0x00, 0x00,
    0x00, 0x40, 0x20, 0x1F, 0x20, 0x40, 0x4F, 0x44, 0x42, 0x40, 0x7F, 0x42, 0x44, 0x43, 0x40, 0x00};
char c_fen[] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    0x80, 0x40, 0x20, 0x90, 0x88, 0x86, 0x80, 0x80, 0x80, 0x83, 0x8C, 0x10, 0x20, 0x40, 0x80, 0x00,
    0x00, 0x80, 0x40, 0x20, 0x18, 0x07, 0x00, 0x40, 0x80, 0x40, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00};
char c_shu[] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    0x90, 0x52, 0x34, 0x10, 0xFF, 0x10, 0x34, 0x52, 0x80, 0x70, 0x8F, 0x08, 0x08, 0xF8, 0x08, 0x00,
    0x82, 0x9A, 0x56, 0x63, 0x22, 0x52, 0x8E, 0x00, 0x80, 0x40, 0x33, 0x0C, 0x33, 0x40, 0x80, 0x00};
char c_number[][32] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0xFC, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0xFC, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x04, 0x02, 0x01, 0x01, 0x81, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x08, 0x0C, 0x0A, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x11, 0x19, 0x15, 0x23, 0xC1, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x21, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0xC0, 0x30, 0x28, 0x24, 0x22, 0x21, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x81, 0x61, 0x19, 0x05, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x8C, 0x52, 0x21, 0x21, 0x21, 0x21, 0x52, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x1C, 0x22, 0x41, 0x41, 0x41, 0x41, 0xC2, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
char c_gameover[][32] = {
    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x82, 0x84, 0x8E, 0x80, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x0F, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x00, 0x00, 0xC0, 0xB0, 0x8C, 0x82, 0x8C, 0xB0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x08, 0x0C, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x0C, 0x08, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x02, 0xFE, 0x04, 0x18, 0x60, 0x80, 0x60, 0x18, 0x04, 0xFE, 0x02, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x08, 0x0F, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x08, 0x0F, 0x08, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x02, 0xFE, 0x42, 0x42, 0x42, 0x42, 0xE2, 0x02, 0x02, 0x0E, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x08, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0xF0, 0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x02, 0x06, 0x1A, 0x60, 0x80, 0x00, 0x00, 0x00, 0x80, 0x60, 0x1A, 0x06, 0x02, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x02, 0xFE, 0x42, 0x42, 0x42, 0x42, 0xE2, 0x02, 0x02, 0x0E, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x08, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00, 0x00, 0x00, 0x00},

    /*--  文字:  �??  --*/
    /*--  宋体12;  此字体下对应的点阵为：宽x�??=16x16   --*/
    {0x00, 0x00, 0x02, 0xFE, 0x42, 0x42, 0xC2, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x08, 0x0F, 0x08, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00}};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void SetPB(char data) //设置PB0-PB7
{
    HAL_GPIO_WritePin(PB0, data % 2);
    HAL_GPIO_WritePin(PB1, (data >> 1) % 2);
    HAL_GPIO_WritePin(PB2, (data >> 2) % 2);
    HAL_GPIO_WritePin(PB3, (data >> 3) % 2);
    HAL_GPIO_WritePin(PB4, (data >> 4) % 2);
    HAL_GPIO_WritePin(PB5, (data >> 5) % 2);
    HAL_GPIO_WritePin(PB6, (data >> 6) % 2);
    HAL_GPIO_WritePin(PB7, (data >> 7) % 2);
}
void CheckBusy() //忙检�??
{
    HAL_GPIO_WritePin(RW, 1);
    HAL_GPIO_WritePin(RS, 0);
    HAL_GPIO_WritePin(E, 1);
    while (1)
    {
        HAL_GPIO_WritePin(E, 0);
        if (HAL_GPIO_ReadPin(PB7) == 0)
            break;
    }
    HAL_GPIO_WritePin(E, 1);
}
void WriteCmd(char data) //写指�??
{
    HAL_GPIO_WritePin(RS, 0);
    HAL_GPIO_WritePin(RW, 0);
    HAL_GPIO_WritePin(E, 1);
    SetPB(data);
    HAL_GPIO_WritePin(E, 0);
}
void WriteData(char data) //写数�??
{
    HAL_GPIO_WritePin(RS, 1);
    HAL_GPIO_WritePin(RW, 0);
    HAL_GPIO_WritePin(E, 1);
    SetPB(data);
    HAL_GPIO_WritePin(E, 0);
}
void LCD_Init() //初始�??
{
    WriteCmd(0x30);
    HAL_Delay(5);
    WriteCmd(0x0C); //�??显示，关光标，不闪烁
    HAL_Delay(5);
    WriteCmd(0x01); //清除显示
    HAL_Delay(5);
    WriteCmd(0x06); //光标的移动方向向左，DDRM的地�??计数器（AC）加1
    HAL_Delay(5);
}
void SetPosition(char x, char y) //设置坐标
{
    if (y >= 64)
    {
        HAL_GPIO_WritePin(CS1, 1);
        HAL_GPIO_WritePin(CS2, 0);
        y = y - 64;
    }
    else
    {
        HAL_GPIO_WritePin(CS1, 0);
        HAL_GPIO_WritePin(CS2, 1);
    }
    WriteCmd(0x40 | y);
    HAL_Delay(10);
    WriteCmd(0xb8 | x);
}
void DisplayCharacter(char R, char L, char p[]) //显示字符
{
    char i;
    for (i = 0; i < 16; i++)
    {
        SetPosition(2 * R, 16 * L + i);
        WriteData(p[i]);
        SetPosition(2 * R + 1, 16 * L + i);
        WriteData(p[i + +16]);
    }
}
void DisplayBlack(char R, char L) //显示黑色方块
{
    char i;
    for (i = 0; i < 8; i++)
    {
        SetPosition(R, 8 * L + i);
        WriteData(0xFF);
    }
}
void DisplayWrite(char R, char L) //显示白色方块
{
    char i;
    for (i = 0; i < 8; i++)
    {
        SetPosition(R, 8 * L + i);
        WriteData(0x00);
    }
}
void LCD_ShowHuanYing()
{
    DisplayCharacter(0, 6, c_huan);
    DisplayCharacter(0, 7, c_ying);
}
void LCD_ShoeFenShu()
{
    DisplayCharacter(0, 6, c_fen);
    DisplayCharacter(0, 7, c_shu);
}
void LCD_ShowScore()
{
    if (score >= 1000)
        DisplayCharacter(1, 4, c_number[(score % 10000) / 1000]);
    if (score >= 100)
        DisplayCharacter(1, 5, c_number[(score % 1000) / 100]);
    if (score >= 10)
        DisplayCharacter(1, 6, c_number[(score % 100) / 10]);
    if (score >= 0)
        DisplayCharacter(1, 7, c_number[score % 10]);
}
void LCD_ShowGO()
{
    for (int i = 0; i < 8; i++)
        DisplayCharacter(i / 4 + 2, i % 4 + 4, c_gameover[i]);
}
void LCD_ShowStartWrite()
{
    for (int i = 0; i < 128; i++)
        if (i % 16 == 7)
            DisplayBlack(i / 16, i % 16);
        else
            DisplayWrite(i / 16, i % 16);
}
void MakeNewBlock()
{
    blocktype = ((int)ADC_Value % 400) / 100;
    switch (blocktype)
    {
    case 0: //横直�?
        R[0] = 0;
        L[0] = 2;
        R[1] = 0;
        L[1] = 3;
        R[2] = 0;
        L[2] = 4;
        break;
    case 1: //竖直�?
        R[0] = 2;
        L[0] = 3;
        R[1] = 1;
        L[1] = 3;
        R[2] = 0;
        L[2] = 3;
        break;
    case 2: //左上�?
        R[0] = 1;
        L[0] = 3;
        R[1] = 0;
        L[1] = 3;
        R[2] = 0;
        L[2] = 4;
        break;
    case 3: //右下�?
        R[0] = 1;
        L[0] = 3;
        R[1] = 0;
        L[1] = 4;
        R[2] = 1;
        L[2] = 4;
        break;
    }
    for (int i = 0; i < 3; i++)
        if (map[R[i]][L[i]] == 1)
        {
            startflag = 0;
            return;
        }
    for (int i = 0; i < 3; i++)
    {
        DisplayBlack(R[i], L[i]);
        map[R[i]][L[i]] = 1;
    }
}
void BlockGetBottom()
{
    for (int i = 0; i < 8; i++)
    {
        if (map[i][0] == 1 && map[i][1] == 1 && map[i][2] == 1 && map[i][3] == 1 && map[i][4] == 1 && map[i][5] == 1 && map[i][6] == 1)
        {
            for (int j = i; j > 0; j--)
            {
                for (int k = 0; k < 7; k++)
                {
                    DisplayWrite(j, k);
                    if (map[j - 1][k] == 0)
                    {
                        DisplayWrite(j, k);
                        map[j][k] = 0;
                    }
                    if (map[j - 1][k] == 1)
                    {
                        DisplayBlack(j, k);
                        map[j][k] = 1;
                    }
                }
            }
            score++;
            HAL_UART_Transmit(&huart1, "Score+1\r\n", 10, 1000);
            LCD_ShowScore();
        }
    }
    MakeNewBlock();
}
void BlockStep()
{
    if (R[0] == 7 || R[1] == 7 || R[2] == 7)
    {
        BlockGetBottom();
        return;
    }
    switch (blocktype)
    {
    case 0:
        if (map[R[0] + 1][L[0]] == 1 || map[R[1] + 1][L[1]] == 1 || map[R[2] + 1][L[2]] == 1)
        {
            BlockGetBottom();
            return;
        }
        break;
    case 1:
        if (map[R[0] + 1][L[0]] == 1)
        {
            BlockGetBottom();
            return;
        }
        break;
    case 2:
        if (map[R[0] + 1][L[0]] == 1 || map[R[2] + 1][L[2]] == 1)
        {
            BlockGetBottom();
            return;
        }
        break;
    case 3:
        if (map[R[0] + 1][L[0]] == 1 || map[R[2] + 1][L[2]] == 1)
        {
            BlockGetBottom();
            return;
        }
        break;
    }
    HAL_GPIO_WritePin(RIGHT, 1);
    HAL_GPIO_WritePin(LEFT, 1);
    HAL_GPIO_WritePin(DOWN, 0);
    for (int i = 0; i < 3; i++)
    {
        DisplayWrite(R[i], L[i]);
        map[R[i]][L[i]] = 0;
        R[i] = R[i] + 1;
    }
    for (int i = 0; i < 3; i++)
    {
        DisplayBlack(R[i], L[i]);
        map[R[i]][L[i]] = 1;
    }
}
void BlockToLeft()
{
    if (L[0] == 0)
        return;
    switch (blocktype)
    {
    case 0:
        if (map[R[0]][L[0] - 1] == 1)
            return;
        break;
    case 1:
        if (map[R[0]][L[0] - 1] == 1 || map[R[1]][L[1] - 1] == 1 || map[R[2]][L[2] - 1] == 1)
            return;
        break;
    case 2:
        if (map[R[0]][L[0] - 1] == 1 || map[R[1]][L[1] - 1] == 1)
            return;
        break;
    case 3:
        if (map[R[0]][L[0] - 1] == 1 || map[R[1]][L[1] - 1] == 1)
            return;
        break;
    }
    HAL_GPIO_WritePin(RIGHT, 1);
    HAL_GPIO_WritePin(DOWN, 1);
    HAL_GPIO_WritePin(LEFT, 0);
    for (int i = 0; i < 3; i++)
    {
        DisplayWrite(R[i], L[i]);
        map[R[i]][L[i]] = 0;
        L[i] = L[i] - 1;
    }
    for (int i = 0; i < 3; i++)
    {
        DisplayBlack(R[i], L[i]);
        map[R[i]][L[i]] = 1;
    }
}
void BlockToRight()
{
    if (L[2] == 6)
        return;
    switch (blocktype)
    {
    case 0:
        if (map[R[2]][L[2] + 1] == 1)
            return;
        break;
    case 1:
        if (map[R[0]][L[0] + 1] == 1 || map[R[1]][L[1] + 1] == 1 || map[R[2]][L[2] + 1] == 1)
            return;
        break;
    case 2:
        if (map[R[0]][L[0] + 1] == 1 || map[R[2]][L[2] + 1] == 1)
            return;
        break;
    case 3:
        if (map[R[1]][L[1] + 1] == 1 || map[R[2]][L[2] + 1] == 1)
            return;
        break;
    }
    HAL_GPIO_WritePin(LEFT, 1);
    HAL_GPIO_WritePin(DOWN, 1);
    HAL_GPIO_WritePin(RIGHT, 0);
    for (int i = 0; i < 3; i++)
    {
        DisplayWrite(R[i], L[i]);
        map[R[i]][L[i]] = 0;
        L[i] = L[i] + 1;
    }
    for (int i = 0; i < 3; i++)
    {
        DisplayBlack(R[i], L[i]);
        map[R[i]][L[i]] = 1;
    }
}
int PC_LED = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        switch (PC_LED)
        {
        case 0:
            HAL_GPIO_TogglePin(SIGNAL);
            HAL_GPIO_TogglePin(LEFT);
            PC_LED = 1;
            break;
        case 1:
            HAL_GPIO_TogglePin(LEFT);
            HAL_GPIO_TogglePin(RIGHT);
            PC_LED = 2;
            break;
        case 2:
            HAL_GPIO_TogglePin(RIGHT);
            HAL_GPIO_TogglePin(DOWN);
            PC_LED = 3;
            break;
        case 3:
            HAL_GPIO_TogglePin(DOWN);
            HAL_GPIO_TogglePin(SIGNAL);
            PC_LED = 0;
            break;
        }
    }
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    MX_ADC1_Init();
    /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(SIGNAL, 0);
    HAL_GPIO_WritePin(LEFT, 1);
    HAL_GPIO_WritePin(RIGHT, 1);
    HAL_GPIO_WritePin(DOWN, 1);
    HAL_TIM_Base_Start_IT(&htim3);
    LCD_Init();
    LCD_ShowStartWrite();
    LCD_ShowHuanYing();
    HAL_UART_Transmit(&huart1, "Welcome to the game.\r\n", 23, 1000);
    HAL_UART_Transmit(&huart1, "You can input 'Space' to start the game.\r\n", 43, 1000);
    HAL_UART_Transmit(&huart1, "You can input 'A'(left) or 'D'(right) or 'S'(down) to control the block.\r\n", 75, 1000);
    HAL_UART_Transmit(&huart1, "Also,you can use the pot to control the type pf next block.\r\n", 62, 1000);
    HAL_UART_Transmit(&huart1, "After use the pot, don't forget to click the terminal when you want to move the block.\r\n", 89, 1000);
    HAL_UART_Transmit(&huart1, "Now, you can input 'space' to start the game.\r\n", 48, 1000);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 7; j++)
            map[i][j] = 0;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_Delay(100);
        HAL_UART_Receive(&huart1, button, 1, 100);
        if (button[0] == ' ')
            startflag = 1;
        if (startflag == 1)
            break;
    }
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_GPIO_WritePin(SIGNAL, 0);
    HAL_GPIO_WritePin(LEFT, 1);
    HAL_GPIO_WritePin(RIGHT, 1);
    HAL_GPIO_WritePin(DOWN, 1);
    LCD_ShoeFenShu();
    LCD_ShowScore();
    MakeNewBlock();
    while (1)
    {
        if (startflag == 0)
            break;
        HAL_Delay(100);
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 1000);
        ADC_Value = HAL_ADC_GetValue(&hadc1);
        HAL_GPIO_WritePin(TYPE1, (ADC_Value % 400) / 200);
        HAL_GPIO_WritePin(TYPE0, (ADC_Value % 200) / 100);
        HAL_UART_Receive(&huart1, button, 1, 1000);
        switch (button[0])
        {
        case 'a':
            BlockToLeft();
            HAL_UART_Transmit(&huart1, "Left\r\n", 7, 1000);
            break;
        case 'd':
            BlockToRight();
            HAL_UART_Transmit(&huart1, "Right\r\n", 8, 1000);
            break;
        case 's':
            BlockStep();
            HAL_UART_Transmit(&huart1, "Down\r\n", 7, 1000);
            break;
        default:
            BlockStep();
            HAL_UART_Transmit(&huart1, "Down\r\n", 7, 1000);
            break;
        }
        button[0] = 's';
    }
    HAL_GPIO_WritePin(SIGNAL, 1);
    HAL_GPIO_WritePin(LEFT, 1);
    HAL_GPIO_WritePin(RIGHT, 1);
    HAL_GPIO_WritePin(DOWN, 1);
    HAL_UART_Transmit(&huart1, "Game Over.\r\n", 13, 1000);
    HAL_UART_Transmit(&huart1, "Please stop and end the game.\r\n", 32, 1000);
    LCD_ShowGO();
    HAL_Delay(30000);
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};
    ADC_InjectionConfTypeDef sConfigInjected = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
     */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Injected Channel
     */
    sConfigInjected.InjectedChannel = ADC_CHANNEL_1;
    sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
    sConfigInjected.InjectedNbrOfConversion = 1;
    sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    sConfigInjected.ExternalTrigInjecConv = ADC_INJECTED_SOFTWARE_START;
    sConfigInjected.AutoInjectedConv = DISABLE;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    sConfigInjected.InjectedOffset = 0;
    if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */
}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void)
{

    /* USER CODE BEGIN TIM3_Init 0 */

    /* USER CODE END TIM3_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM3_Init 1 */

    /* USER CODE END TIM3_Init 1 */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 7999;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 99;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM3_Init 2 */

    /* USER CODE END TIM3_Init 2 */
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, CS2_Pin | DB4_Pin | DB3_Pin | CS1_Pin | DB7_Pin | DB5_Pin | DB6_Pin | DB0_Pin | DB1_Pin | DB2_Pin | RS_Pin | RW_Pin | E_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, LED_LEFT_Pin | LED_SIGNAL_Pin | LED_RIGHT_Pin | GPIO_PIN_6 | LED_DOWN_Pin | GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pins : CS2_Pin DB4_Pin DB3_Pin CS1_Pin
                             DB7_Pin DB5_Pin DB6_Pin DB0_Pin
                             DB1_Pin DB2_Pin RS_Pin RW_Pin
                             E_Pin */
    GPIO_InitStruct.Pin = CS2_Pin | DB4_Pin | DB3_Pin | CS1_Pin | DB7_Pin | DB5_Pin | DB6_Pin | DB0_Pin | DB1_Pin | DB2_Pin | RS_Pin | RW_Pin | E_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : LED_LEFT_Pin LED_SIGNAL_Pin LED_RIGHT_Pin PC6
                             LED_DOWN_Pin PC5 */
    GPIO_InitStruct.Pin = LED_LEFT_Pin | LED_SIGNAL_Pin | LED_RIGHT_Pin | GPIO_PIN_6 | LED_DOWN_Pin | GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
