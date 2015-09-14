#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

typedef struct Queue
{
    unsigned char *buffer;
    unsigned int size;
    unsigned int writePosition;
    unsigned int readPosition;
} Queue_type;

void Queue_Constructor(Queue_type *this,unsigned char *buffer, unsigned int size);

int Queue_Enqueue(Queue_type *this,unsigned char value);

unsigned char Queue_Dequeue(Queue_type *this);

#endif // UTIL_QUEUE_H
