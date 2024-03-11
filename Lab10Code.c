#include <stdint.h> 
//#include "alt_types.h"
#include "sys/alt_irq.h"
#include "system.h"

//prototypes
uint16_t nextValue(uint16_t value);
static void handle_timer_interrupts(void* context);

//PIO base addresses CHANGE IN LAB
volatile uint32_t * timerBase = (volatile uint32_t *) 0x00041020;
volatile uint32_t * spiBase = (volatile uint32_t *) 0x00041000;

//value to send to DAC over spi
uint16_t outputValue = 0;

int main()
{

	alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_IRQ, handle_timer_interrupts, NULL, 0x0);
    
    //start timer and enable interrupts
    timerBase[1] = 0x7;

    //spin
    while(1);

    return 0;
}

static void handle_timer_interrupts(void* context)
{
    //clear TO bit
    timerBase[0] = 0x1;

    //set spi output value to nextValue
    spiBase[1] = nextValue(outputValue);

	return;
}

uint16_t nextValue(uint16_t value)
{
    //rollover 
    if(value >= 4095)
    {
        value = 0;
    }
    //increment
    else
    {
        value++;
    }

    //mask for upper 4 bits
    uint16_t mask = 0x1000;

    //clear upper 4 bits of 16 bit number 
    //set upper 4 bits to values determined in prelab
   value |= mask;
    
    return value;
}
