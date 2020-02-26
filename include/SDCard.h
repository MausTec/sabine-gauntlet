//
// Created by eiser on 2/21/2020.
//

#ifndef GAUNTLETCONTROL_SDCARD_H
#define GAUNTLETCONTROL_SDCARD_H


//#include <SD.h>

#include <SdFat.h>

class SDCard {
public:
  bool initialized = false;

  bool Setup();

  SdFile* open(const char *path);
  SdFile* nextFile();
  SdFile* openRoot();

//  void printDir(File dir);

  void chdir(char *dirname = "/");

private:
  SdFat sd;
  SdFile file;

  bool initsd();
};

extern SDCard Storage;

#endif //GAUNTLETCONTROL_SDCARD_H
