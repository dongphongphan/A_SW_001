/**
 * @file r3_queuies.c
 * Copyright 2022  R3 Solutions GmbH
 * Version 1.0
 */

/* ************************** INCLUDES ************************** */
//#include "r3_frameTypes.h"
//#include "r3_interrupt_control.h"
//#include "memory_mgmt.h"


/* ************************** DEFINES *************************** */

typedef unsigned int r3_u32;
typedef unsigned short r3_u16;
typedef unsigned char r3_u8;
/* ************************** ENUMS ***************************** */

typedef enum r3_rxh_framePoolType_e
{
    R3_RXH_FRAMEPOOLTYPE_RECEIVED_FREE = 1,
    R3_RXH_FRAMEPOOLTYPE_RECEIVED_IN_DECRYPTION,
    R3_RXH_FRAMEPOOLTYPE_NUM
} r3_rxh_framePoolType_e;

typedef struct r3_rx_frame_t {
    struct r3_rx_frame_t *next;
    struct r3_rx_frame_t *prev;
    r3_u32 id;
    void* data;
} r3_rx_frame_t;

typedef struct r3_rxh_frameLinkedList_t
{
    r3_rx_frame_t *head; // points to first element, null if none in list
    r3_rx_frame_t *tail; // points to the last element, null if none in list
    r3_u16 numFrames;
} r3_rxh_frameLinkedList_t;

/* ************************** STRUCTS *************************** */

/* ************************** VARIABLES ************************* */
r3_rxh_frameLinkedList_t rxFramePool[R3_RXH_FRAMEPOOLTYPE_NUM]; 

/* ************************** FUNCTIONS ************************* */

void r3_rxh_initFramePools(r3_u8 amountOfRxFrames, unsigned int amountOfDiagnosticBuffer)
{
    rxFirstFrame = (r3_rx_frame_t *) malloc(amountOfRxFrames * sizeof(r3_rx_frame_t));

    r3_u8 iterator = 0;
    for (iterator = 0; iterator < amountOfRxFrames; iterator++)
    {
        rxFirstFrame[iterator].id = iterator;
        rxFirstFrame[iterator].next = rxFirstFrame[iterator + 1];
        rxFirstFrame[iterator].prev = rxFirstFrame[iterator - 1];
    }

    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_FREE].head = rxFirstFrame;
    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_FREE].tail = rxFirstFrame + amountOfRxFrames;
    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_FREE].tail->next = NULL;
    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_FREE].numFrames = amountOfRxFrames;

    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_IN_DECRYPTION].head = NULL;
    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_IN_DECRYPTION].tail = NULL;
    rxFramePool[R3_RXH_FRAMEPOOLTYPE_RECEIVED_IN_DECRYPTION].numFrames = 0;
}

void r3_rxh_addFrameToPool(r3_rxh_framePoolType_e poolType, r3_rx_frame_t *frame)
{
	r3_u32 int_mask;
	DISABLE_ALL(int_mask);
	if(rxFramePool[poolType].tail == NULL)  
	{
	    rxFramePool[poolType].head = frame;
	}
	else
	{
	    rxFramePool[poolType].tail->next = frame;
	    frame->prev = rxFramePool[poolType].tail; 
	}
	rxFramePool[poolType].tail = frame;
	rxFramePool[poolType].tail->next = NULL;
	rxFramePool[poolType].numFrames++;
}

int r3_rxh_moveFrame(r3_rxh_framePoolType_e poolFrom, r3_rxh_framePoolType_e poolTo)
{

    r3_rx_frame_t *frame = rxFramePool[poolFrom].tail;
    rxFramePool[poolFrom].tail = rxFramePool[poolFrom].tail->prev;
    rxFramePool[poolFrom].tail->next = NULL;

    // now adding to poolTo (copied from r3_rxh_addFrameToPool)
    if (rxFramePool[poolType].tail == NULL)
    {
        rxFramePool[poolType].head = frame;
    }
    else
    {
        rxFramePool[poolType].tail->next = frame;
        frame->prev = rxFramePool[poolType].tail;
    }
    rxFramePool[poolType].tail = frame;
    rxFramePool[poolType].tail->next = NULL;
    rxFramePool[poolType].numFrames++;
}