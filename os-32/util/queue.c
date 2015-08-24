#include <queue.h>
#define QUEUE_NULL 0

unsigned int Assistant_ComputeNextPosition(Queue_type *this,unsigned int current);

void Queue_Constructor(Queue_type *this,unsigned char *buffer,unsigned int size)
{
    this->buffer = buffer;
    this->size = size;
    this->writePosition = 0;
    this->readPosition = 0;
}

/**
*   \brief Add a \param value to \param this queue. The \param value must not be 0.
*   \param value The value that is being added to the queue.
*   \return Return 0 if execution was normal.
*   \return Return -1 if \param value equals 0.
*   \return Return -2 if \param this->buffer is full.
*/
int Queue_Enqueue(Queue_type *this,unsigned char value)
{
    if(value == QUEUE_NULL)
    {
        return -1;
    }

    unsigned int wp = this->writePosition;
    if(this->buffer[wp] != QUEUE_NULL)
    {
        return -2;
    }

    this->buffer[wp] = value;
    this->writePosition = Assistant_ComputeNextPosition(this,wp);
    return 0;
}

unsigned char Queue_Dequeue(Queue_type *this)
{
    unsigned int rp = this->readPosition;
    unsigned char output = this->buffer[rp];
    if(output == QUEUE_NULL)
    {
        return output;
    }
    this->buffer[rp] = QUEUE_NULL;
    this->readPosition = Assistant_ComputeNextPosition(this,rp);
    return output;
}


unsigned int Assistant_ComputeNextPosition(Queue_type *this,unsigned int current)
{
    unsigned int size = this->size;
    return ++current % size;
}
