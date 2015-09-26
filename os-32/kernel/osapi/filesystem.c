#include "filesystem.h"
unsigned int ComputeDirectotyAddress(unsigned int cluster);
void Osapi_ListDirectory(regs_t *r)
{
    unsigned int first_cluster = r->ebx;
    unsigned int address = ComputeDirectotyAddress(first_cluster);

    DirectoryRecord dir[16*FileSystem_SectorsPerCluster];
    ide_read_blocks(0, address, FileSystem_SectorsPerCluster, dir);

    for(int i = 0; i < 16 * FileSystem_SectorsPerCluster; i++)
    {
        if(dir[i].Attributes == DirectoryAttribute_Archive || dir[i].Attributes == DirectoryAttribute_Directory)
        {
            kprintf("%s:\n",dir[i].Name);
        }
    }
}

void Osapi_GetCurrentDirectory(regs_t *r)
{
    unsigned int first_cluster = r->ebx;
    unsigned int address = ComputeDirectotyAddress(first_cluster);
    DirectoryRecord *dir = malloc(sizeof(DirectoryRecord) * 16 * FileSystem_SectorsPerCluster);
    ide_read_blocks(0, address, FileSystem_SectorsPerCluster, dir);
    r->eax = (unsigned int)dir;
}

unsigned int ComputeDirectotyAddress(unsigned int cluster)
{
    return cluster == 0
        ? FileSystem_RootDirectoryAddress
        : (cluster - 2) * FileSystem_SectorsPerCluster;
}
