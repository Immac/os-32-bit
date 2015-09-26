#ifndef MIKOSLIB_FILESYSTEM_H
#define MIKOSLIB_FILESYSTEM_H

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
}  __attribute__((packed)) DirectoryRecord;

#endif // MIKOSLIB_FILESYSTEM_H
