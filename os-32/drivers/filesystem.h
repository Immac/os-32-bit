#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "../kernel/system.h"
#include "screen.h"
#include "../kernel/types.h"

typedef enum
{
    DirectoryAttribute_ReadOnly = 0x01,
    DirectoryAttribute_Hidden = 0x02,
    DirectoryAttribute_System = 0x04,
    DirectoryAttribute_VolumeId = 0x08,
    DirectoryAttribute_Directory = 0x10,
    DirectoryAttribute_Archive = 0x20,
    DirectoryAttribute_LongName = DirectoryAttribute_ReadOnly | DirectoryAttribute_Hidden | DirectoryAttribute_System | DirectoryAttribute_VolumeId
} DirectoryAttribute;

typedef struct
{
    unsigned char BS_jmpBoot[3];
    unsigned char BS_OEMName[8];
    unsigned short BPB_BytesPerSector;
    unsigned char BPB_SectorsPerCluster;
    unsigned short BPB_ReservedSectorCount;
    unsigned char BPB_NumberOfFatStructures;
    unsigned short BPB_RootEntryCount;
    unsigned short BPB_TotalSector16;
    unsigned char BPB_media;
    unsigned short BPB_Fat16z16;
    unsigned short BPB_SectorsPerTrack;
    unsigned short BPB_NumberOfHeads;
    unsigned int BPB_HiddenSector;
    unsigned int BPB_TotalSector32;

    unsigned char BS_DriveNumber;
    unsigned char BS_Reserved1;
    unsigned char BS_BootSignature;
    unsigned int BS_VolumeId;
    unsigned char BS_VolumeLabel[11];
    unsigned char BS_FileSystemType[8];

    unsigned char Fill_BootSectorCode[448];
    unsigned char Fill_Signature[2];
} __attribute__((packed)) FatBootRecord;

typedef struct
{
    unsigned char Name[11];
    unsigned char Attributes;
    unsigned char WindowsNtReserved;
    unsigned char CreationTimeTenths;
    unsigned short CreationTime;
    unsigned short CreationDate;
    unsigned short LastAccessDate;
    unsigned short FirstClusterHigh;
    unsigned short WriteTime;
    unsigned short WriteDate;
    unsigned short FirstClusterLow;
    unsigned int FileSize;
} __attribute__((packed)) DirectoryRecord;

typedef struct
{
    unsigned char State;
    unsigned char HeadStart;
    unsigned char StartSector;
    unsigned char StartCylinder;
    unsigned char Type;
    unsigned char EndHead;
    unsigned char EndSector;
    unsigned char EndCylinder;
    unsigned int StartLogicBlockAddress;
    unsigned int SectorCountLogicBlockAddress;
} __attribute__((packed)) PartitionEntry;

typedef struct
{
    char boot[446];
    PartitionEntry partitions[4];
    unsigned char signature[2];
} __attribute__((packed)) Mbr;

typedef enum
{
    NoError

}
__attribute__((packed)) ErrorNumber;

void InitMbr(void);
unsigned int FileSystem_StartLogicBlockAddress;
unsigned int FileSystem_RootDirectoryAddress;
unsigned int FileSystem_DataEntry;
unsigned int FileSystem_SectorsPerCluster;
#endif // FILESYSTEM_H
