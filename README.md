# c++ Logger 
c++ logger for printing out info, debug and error messages into log file or standard output

## Usage example
```
#include "Logger.h"

int main(){
    Logger stdLogger;
    Logger fileLogger("file.log");
    stdLogger.log(LogType::Info, "Some information logging");
    fileLogger.log(LogType::Debug, "Some debugging logging");
    return 0;
}
```
Standard output:
```
[22:30:54:554:228][INFO] Some information logging
```
Content of file.log
```
[22:30:54:554:636][DEBUG] Some debugging logging
```
