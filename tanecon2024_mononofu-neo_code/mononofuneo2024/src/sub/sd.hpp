#ifndef SD_HPP
#define SD_HPP

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "pinassign.hpp"

class sd
{
    private:
    public:
        int n_logdata=202402010;    //YYYYMMDDN
        char sd_filename[64];
        String buffer;
        void init();
        void logWrite(io& sensors);
        void writeFile(fs::FS &fs,const char *path,const char *message);
        void appendFile(fs::FS &fs,const char *path,String message);
        void makebuffer(io& sensors);
};

#endif