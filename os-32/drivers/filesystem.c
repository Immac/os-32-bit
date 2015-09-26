#include "filesystem.h"

void InitMbr()
{
    Mbr mbr;
    FatBootRecord fbr;

    ide_read_blocks(0,0,1,&mbr);
    FileSystem_StartLogicBlockAddress = mbr.partitions[0].StartLogicBlockAddress;

    ide_read_blocks(0,FileSystem_StartLogicBlockAddress,1,&fbr);
    DirectoryRecord dir[16];

    FileSystem_RootDirectoryAddress = FileSystem_StartLogicBlockAddress
    + fbr.BPB_ReservedSectorCount
    + fbr.BPB_Fat16z16 * fbr.BPB_NumberOfFatStructures;

    int bytes_per_sector = fbr.BPB_BytesPerSector;
    int directory_record_size = sizeof(DirectoryRecord);
    FileSystem_DataEntry = FileSystem_RootDirectoryAddress + fbr.BPB_RootEntryCount * directory_record_size/bytes_per_sector;
    FileSystem_SectorsPerCluster = fbr.BPB_SectorsPerCluster;
}
