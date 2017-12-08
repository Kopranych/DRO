#include "fifo.h"


void init_fifo(fifo_t *fifo)
{
    fifo->head = fifo->tail = fifo->count = 0;
}

int fifo_put(fifo_t *fifo, unsigned long high_data, unsigned long low_data)
{
  /* ������� �������������, ����� fifo->head �� �������
     ������ fifo->tail, ���� ����� spos ���������
     �� ����� �������, � fifo->tail - �� ������.
  
  if(fifo->head+1==fifo->tail || (fifo->head+1==MAX && !(fifo->tail))) {
   * */
  if(fifo->count == MAX)
  {
    //printf("������ �����\n");
    return 0;
  }

  fifo->buf_data[fifo->head].high_byte = high_data;
  fifo->buf_data[fifo->head].low_byte = low_data;
  fifo->head++;
  fifo->count++;
  if(fifo->head==MAX) fifo->head = 0; /* ���������� �� ������ */
  return 1;
}

double_long fifo_get(fifo_t *fifo)
{
  if(fifo->tail == MAX) fifo->tail = 0; /* ���������� �� ������ */
  if(fifo->count == 0) {
    //printf("����� ����\n");
      return;
  }
  fifo->tail++;
  fifo->count--;
  return fifo->buf_data[fifo->tail-1];
}

int get_count_fifo(fifo_t *fifo)
{
    return fifo->count;
}

//unsigned long summa_array(fifo_t *fifo)
//{
//    unsigned long int sum_num = 0;
//    int count = 0;
//    for(count = 0; count < MAX; count++)
//    {
//        sum_num += fifo->buf_data[count];       
//    }
//    return sum_num;
//}
