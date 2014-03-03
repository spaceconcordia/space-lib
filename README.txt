Usage:
See shakespeare/src/test.cpp

Use get_filename() to return a shakespeare log file given your custom input
Use Log() to make entries on this log file

Currently:
You must provide a closing slash or else your provided directory will be prepended to the filename
You must provide a dot ('.')

TODO 
- check if provided directory ends with '/', else add it
- check if provided suffix starts with '.', else add it
- check for illegal filepath characters
- determine and apply max log and file length
- make get_filename return full file path as char* rather than string
- minimize log data, i.e. use timestamp, less "::", etc.
- log rotation: decide when to make new file, when to delete old, and how
- test timestamp extremes
- look at leap second considerations
- ms/ns rather than s for log entires
