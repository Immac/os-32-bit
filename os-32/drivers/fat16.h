#ifndef FAT16_DRIVER
#define FAT16_DRIVER
typedef struct
{
    unsigned char BS_jmpBoot[3];
    unsigned char BS_OEMName[8];
    unsigned short BPB_BytesPerSecond;
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
    unsigned char BS_FyleSystemType[8];

} BsBpb;

#endif // FAT16_DRIVER
