#include "mbed.h"
#include "HEPTA_EPS.h"
#include "HEPTA_CDH.h"
#include "HEPTA_SENSOR.h"

RawSerial pc(USBTX,USBRX);
HEPTA_EPS eps(p16,p26);
HEPTA_CDH cdh(p5,p6,p7,p8,"sd");
HEPTA_SENSOR sensor(p17,
                  p28,p27,0x19,0x69,0x13,
                  p13, p14,p25,p24);

int main(){
    FILE *dummy = fopen("/sd/dummy.txt","w");
    if(dummy == NULL) {
        error("Could not open file for write\r\n");
    }
    fclose(dummy);
    
    pc.printf("Camera Snapshot Mode\r\n");
    pc.printf("Hit Any Key To Take Picture\r\n");
    while(!pc.readable()) {}
    sensor.Sync();
    sensor.initialize(HeptaCamera_GPS::Baud115200, HeptaCamera_GPS::JpegResolution320x240);
    sensor.test_jpeg_snapshot_picture("/sd/test.jpg");
}

