from spiffs import *


with file("workspace/back.bin", "r+wb") as bf:
	s = SpiffsFileBack(bf)
	fd = s.fopen("workspace/back.bin", SPIFFS_CREAT | SPIFFS_WRONLY)
	print(fd)
