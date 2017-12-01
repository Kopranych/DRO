/* 
 * File:   fifo.h
 * Author: Kopranov_IN
 *
 * Created on 20 ������ 2017 �., 13:40
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

#define MAX 100

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




//������������� ������
void init_fifo(fifo_t *fifo);
//���������� ������ � ����� 
int fifo_put(fifo_t *fifo, unsigned long data);
//���������� ������ �� ������
unsigned long fifo_get(fifo_t *fifo);
//�������� ���������� ������ � fifo
int get_count_fifo(fifo_t *fifo);
