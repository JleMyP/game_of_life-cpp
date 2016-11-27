#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#ifdef __unix

unsigned long getFreeRam() {
  char line[256];
  unsigned int ram;
  FILE *meminfo = fopen("/proc/meminfo", "r");

  if (meminfo == NULL) return -1;

  while (fgets(line, sizeof(line), meminfo)) {
    if (sscanf(line, "MemTotal: %d kB", &ram) == 1) {
      fclose(meminfo);
      return ram;
    }
  }

  fclose(meminfo);
  return -1;
}

#elif _WIN32

#include <windows.h>

unsigned long getFreeRam() {
  MEMORYSTATUSEX statex;
  statex.dwLength = sizeof(statex);

  GlobalMemoryStatusEx(&statex);

  return (unsigned long)(statex.ullAvailPhys / 1024);
}

#endif //platform
#endif //header
