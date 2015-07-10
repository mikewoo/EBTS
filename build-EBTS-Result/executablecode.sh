#!/bin/sh 

readelf -h  test > ./Static_detection/ELF_Header_File
readelf -s  test > ./Static_detection/Symbol_Table_File
readelf -r  test > ./Static_detection/Relocation_Section_File
readelf -wi test > ./Static_detection/Debug_Info_File
readelf -S  test > ./Static_detection/Section_Headers_File

cd ./Static_detection

sh latELF.sh
sh latSymbol.sh
sh latRelocation.sh
sh latDebug.sh
sh latSection.sh

cp *_File ../test_report/

