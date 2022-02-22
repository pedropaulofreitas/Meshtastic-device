#include "configuration.h"
#include "TextMessagePlugin.h"
#include "NodeDB.h"
#include "PowerFSM.h"

TextMessagePlugin *textMessagePlugin;


typedef struct {
    int port;
    int value;
} Timer;

void swap(Timer* xp, Timer* yp)
{
    Timer temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void selectionSort(Timer arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].value < arr[min_idx].value)
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
 

bool TextMessagePlugin::handleReceived(const MeshPacket &mp)
{
    auto &p = mp.decoded;
    DEBUG_MSG("Received text msg from=0x%0x, id=0x%x, msg=%.*s\n", mp.from, mp.id, p.payload.size, p.payload.bytes);

    // We only store/display messages destined for us.
    // Keep a copy of the most recent text message.
    devicestate.rx_text_message = mp;
    devicestate.has_rx_text_message = true;

    powerFSM.trigger(EVENT_RECEIVED_TEXT_MSG);
    notifyObservers(&mp);


    Timer timers[8];

    char * pch;
    pch = strtok ((char *) p.payload.bytes,",");
    char* opt[4];
    int i = 0;
    while (pch != NULL)
    {
        opt[i] = (char *) malloc( (strlen(pch)+1) * sizeof(char));
        sscanf(opt[i], "%d:%d", timers[i].port, timers[i].value);

        strcpy(opt[i++], pch);
        pch = strtok (NULL, ",");
    }


    selectionSort(timers, 8);

    if(timers[0].value != 0) {
        pinMode(timers[0].port, OUTPUT);
        digitalWrite(timers[0].port, 1);
    }

    if(timers[1].value != 0) {
        pinMode(timers[1].port, OUTPUT);
        digitalWrite(timers[1].port, 1);
    }

    if(timers[2].value != 0) {
        pinMode(timers[2].port, OUTPUT);
        digitalWrite(timers[2].port, 1);
    }

    if(timers[3].value != 0) {
        pinMode(timers[3].port, OUTPUT);
        digitalWrite(timers[3].port, 1);
    }

    if(timers[4].value != 0) {
        pinMode(timers[4].port, OUTPUT);
        digitalWrite(timers[4].port, 1);
    }

    if(timers[5].value != 0) {
        pinMode(timers[5].port, OUTPUT);
        digitalWrite(timers[5].port, 1);
    }

    if(timers[6].value != 0) {
        pinMode(timers[6].port, OUTPUT);
        digitalWrite(timers[6].port, 1);
    }

    if(timers[7].value != 0) {
        pinMode(timers[7].port, OUTPUT);
        digitalWrite(timers[7].port, 1);
    }

    if(timers[0].value != 0) {
        delay((timers[0].value)*1000);
        digitalWrite(timers[0].port, 0);
    }

    if(timers[1].value != 0) {
        if((timers[1].value - timers[0].value) > 0) {
            delay((timers[1].value - timers[0].value)*1000);
            digitalWrite(timers[1].port, 0);
        } else {
            digitalWrite(timers[1].port, 0);
        }
    }

    if(timers[2].value != 0) {
        if((timers[2].value - timers[1].value) > 0) {
            delay((timers[2].value - timers[1].value)*1000);
            digitalWrite(timers[2].port, 0);
        } else {
            digitalWrite(timers[2].port, 0);
        }
    }

 
    if(timers[3].value != 0) {
        if((timers[3].value - timers[2].value) > 0) {
            delay((timers[3].value - timers[2].value)*1000);
            digitalWrite(timers[3].port, 0);
        } else {
            digitalWrite(timers[3].port, 0);
        }
    }

  
    if(timers[4].value != 0) {
        if((timers[4].value - timers[3].value) > 0) {
            delay((timers[4].value - timers[3].value)*1000);
            digitalWrite(timers[4].port, 0);
        } else {
            digitalWrite(timers[4].port, 0);
        }
    }

  
    if(timers[5].value != 0) {
        if((timers[5].value - timers[4].value) > 0) {
            delay((timers[5].value - timers[4].value)*1000);
            digitalWrite(timers[5].port, 0);
        } else {
            digitalWrite(timers[5].port, 0);
        }
    }

  
    if(timers[6].value != 0) {
        if((timers[6].value - timers[5].value) > 0) {
            delay((timers[6].value - timers[5].value)*1000);
            digitalWrite(timers[6].port, 0);
        } else {
            digitalWrite(timers[6].port, 0);
        }
    }

  
    if(timers[7].value != 0) {
        if((timers[7].value - timers[6].value) > 0) {
            delay((timers[7].value - timers[6].value)*1000);
            digitalWrite(timers[7].port, 0);
        } else {
            digitalWrite(timers[7].port, 0);
        }
    }

   
  

    return false; // Let others look at this message also if they want
}



   



    // // remoteHardwarePlugin.handleReceived(mp)
    // digitalWrite(25, 1);
    // delay(atoi( (const char*) p.payload.bytes));
    // digitalWrite(25, 0);

    // pinMode(25, OUTPUT);