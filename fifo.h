/* 
 * File:   fifo.h
 * Author: Kopranov_IN
 *
 * Created on 20 Ноябрь 2017 г., 13:40
 */

#ifndef FIFO_H
#define	FIFO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_H */

#include <stdio.h>
#include <stdlib.h>
#include "Timer.h"

#define TIME_MEAS_FREQ 10000// время накопления данных измерений частоты в секундах
#define MAX TIME_MEAS_FREQ/PERIOD_CORRECTION

typedef struct{
    unsigned long high_byte;
    unsigned long low_byte;
}double_long;


typedef struct{
    double_long buf_data[MAX];
    int head;
    int tail;
    int count;
}fifo_t;




//инициализация буфера
void init_fifo(fifo_t *fifo);
//добавление данных в буфер 
int fifo_put(fifo_t *fifo, unsigned long high_data, unsigned long low_data);
//извлечение данных из буфера
double_long fifo_get(fifo_t *fifo);
//получить количество данных в fifo
int get_count_fifo(fifo_t *fifo);
