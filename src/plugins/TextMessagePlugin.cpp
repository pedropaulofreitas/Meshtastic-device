#include "configuration.h"
#include "TextMessagePlugin.h"
#include "NodeDB.h"
#include "PowerFSM.h"

TextMessagePlugin *textMessagePlugin;

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

    
    char * pch;
    pch = strtok ((char *) p.payload.bytes,",");
    char* opt[8];

    typedef struct {
        int port;
        int value;
    } Timer;

    Timer timers[8];

    int i = 0;
    while (pch != NULL) {
        opt[i] = (char *) malloc( (strlen(pch)+1) * sizeof(char));
        strcpy(opt[i++], pch);
        pch = strtok (NULL, ",");
    }

    //write values to struct
    for(int i = 0; i< 8; ++i) {
     sscanf(opt[i], "%d:%d", timers[i].port, timers[i].value);
    }

    //sort by value
    Timer temp;

    for (int i = 0; i < 8; i++) {     
        for (int j = i+1; j < 8; j++) {     
            if(timers[i].value < timers[j].value) {    
                temp = timers[i];    
                timers[i] = timers[j];    
                timers[j] = temp;    
            }     
        } 
    }  

    //activete all ports
    for(int i = 0; i< 8; ++i) {
        if(timers[i].value != 0) {
             pinMode(timers[i].port, OUTPUT);
             digitalWrite(timers[i].port, 1);
        }
    }
    //deactivate first element
    delay((timers[0].value)*1000);
    digitalWrite(timers[0].port, 0);
    
    //deactivate other elements
    for(int i = 1; i< 8; ++i) {
        int diff = timers[i].value - timers[i -1].value;

        if(diff != 0) {
            delay((diff)*1000);
            digitalWrite(timers[i].port, 0);
        }
    }
     
    return false; // Let others look at this message also if they want
}





   
