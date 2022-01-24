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

    
    int a, b, c, d, e, f, g, h;
    char * pch;
    pch = strtok ((char *) p.payload.bytes,",");
    char* opt[4];
    int i = 0;
    while (pch != NULL)
    {
        opt[i] = (char *) malloc( (strlen(pch)+1) * sizeof(char));
        strcpy(opt[i++], pch);
        pch = strtok (NULL, ",");
    }

    sscanf(opt[0], "%d:%d", &a, &b);
    sscanf(opt[1], "%d:%d", &c, &d);
    sscanf(opt[2], "%d:%d", &e, &f);
    sscanf(opt[3], "%d:%d", &g, &h);

    if(b != 0) {
        pinMode(a, OUTPUT);
        digitalWrite(a, 1);
    }


    if(d != 0) {
        pinMode(c, OUTPUT);
        digitalWrite(c, 1);
    }

    if(f != 0) {
        pinMode(e, OUTPUT);
        digitalWrite(e, 1);
    }

    if(h != 0) {
        pinMode(g, OUTPUT);
        digitalWrite(g, 1);
    }
    
    if(b != 0) {
        delay((b)*1000);
        digitalWrite(a, 0);
    }

    if(d != 0) {
        if((d-b) > 0) {
            delay((d -b)*1000);
            digitalWrite(c, 0);
        } else {
            digitalWrite(c, 0);
        }
    }

    if(f != 0) {
        if((f -d) > 0) {
            delay((f -d)*1000);
            digitalWrite(e, 0);
        } else{
            digitalWrite(e, 0);
        }
    }

    if(h != 0) {
        if((h -f) > 0){
            delay((h -f)*1000);
            digitalWrite(g, 0);
        } else {
            digitalWrite(g, 0);
        }
    }


    return false; // Let others look at this message also if they want
}



   



    // // remoteHardwarePlugin.handleReceived(mp)
    // digitalWrite(25, 1);
    // delay(atoi( (const char*) p.payload.bytes));
    // digitalWrite(25, 0);

    // pinMode(25, OUTPUT);