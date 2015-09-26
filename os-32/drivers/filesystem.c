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
    //kprintf("\n%u\n", DataEntry);
    /*ide_read_blocks(0,RootDirectoryAddress,1,dir);

    for(int i = 0; i < 16; i++)
    {
        if(dir[i].Attributes == 0x20 || dir[i].Attributes == 0x10)
        {
            kprintf("%s: %u \n",dir[i].Name, dir[i].FirstClusterLow);
        }
    }*/
}

//void read()

/*
File *FileSystem_FileOpen(char *fileName, ErrorNumber* errorNumber)
{

    ErrorNumber = NoError;
    return 0;
}
*/
