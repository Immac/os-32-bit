#include "shell.h"

char *Shell_RepairDataSegmentOffset(char *string);
char *GetArgument(char *userInput,int argumentNumber);
int GetCommand(char *userInput);
#define InputSize 80 // static const int InputSize = 80;
//Direc
DirectoryRecord *currentDir = 0;
typedef enum Command
{
    Exit,
    Test,
    Ls,
    FileOpen,
    CommandCount
} Command_type;

typedef struct
{
    char *WelcomeMessage1;
    char *NewLine;
    char *InvalidCommand;
    char *MikosShell;
    char *NotYetImplemented;
} Vocabulary_type;
Vocabulary_type Vocabulary;

typedef enum ExitCode
{
    Normal,
    Error,
    UserRequest,
    InvalidCommand,
    Continue
} ExitCode_type;

typedef MikosLib_StoI_MapEntry_type Shell_MapEntry;
typedef MikosLib_StoI_Map_type Shell_Map;


int ShellConstructed = 0;
char *DataSegmentAddress;
char *Commands[CommandCount];

Shell_MapEntry CommandEntries[CommandCount];
Shell_Map CommandMap;

ExitCode_type (*Actions[CommandCount])(char *userInput);
ExitCode_type Shell_UserRequest(char *userInput);
ExitCode_type Shell_Test(char *userInput);
ExitCode_type PerformAction(char *userInput);
ExitCode_type Shell_OpenFile(char *userInput);
ExitCode_type Shell_List(char *userInput);

int Shell_Construct(char *dataSegmentAddress)
{
    DataSegmentAddress = dataSegmentAddress;
    Commands[Exit] = Shell_RepairDataSegmentOffset("exit");
    Commands[Test] = Shell_RepairDataSegmentOffset("test");
    Commands[Ls] = Shell_RepairDataSegmentOffset("ls");
    Commands[FileOpen] = Shell_RepairDataSegmentOffset("f-open");

    Vocabulary.WelcomeMessage1 = Shell_RepairDataSegmentOffset("Welcome to MikOS II [Sanae]!\n");
    Vocabulary.NewLine = Shell_RepairDataSegmentOffset("\n");
    Vocabulary.InvalidCommand = Shell_RepairDataSegmentOffset("The \"Command\" entered was not found, please try again! The command was: ");
    Vocabulary.MikosShell = Shell_RepairDataSegmentOffset("\nMikOS >");
    Vocabulary.NotYetImplemented = Shell_RepairDataSegmentOffset("\nThis \"Command\" is yet to be Implemented!: ");

    Actions[Exit] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_UserRequest);
    Actions[Test] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_Test);
    Actions[FileOpen] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_OpenFile);
    Actions[Ls] = (void *)Shell_RepairDataSegmentOffset((char*)Shell_List);

    for(int i = 0; i < CommandCount; i++)
    {
        CommandEntries[i].key = Commands[i];
        CommandEntries[i].value = i;
    }
    MikosLib_StoI_Map_Construct(&CommandMap,CommandEntries);
}

int Shell_MainLoop()
{
    char user_input[InputSize] = {0};
    int exit_code = Continue;
    Mikos_PrintString(Vocabulary.WelcomeMessage1);
    while(exit_code == Continue)
    {
        Mikos_PrintString(Vocabulary.MikosShell);
        Mikos_ReadString(user_input,InputSize);
        Mikos_PrintString(Vocabulary.NewLine);
        exit_code = PerformAction(user_input);
        MikosLib_Util_ArrayClear(user_input,InputSize);
    }

    return 0;
}

ExitCode_type PerformAction(char *user_input)
{
    Vocabulary_type vocab;
    int command = GetCommand(user_input);
    if (command != -1)
    {
        return Actions[command](user_input);
    }
    Mikos_PrintString(Vocabulary.InvalidCommand);
    Mikos_PrintString(user_input);
    return Continue;
}

ExitCode_type Shell_UserRequest(char *userInput)
{
    return UserRequest;
}

int GetCommand(char *userInput)
{
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int output = MikosLib_StoI_Map_EvaluateKey(&CommandMap,command,InputSize);

    Mikos_Free(command);
    return output;
}

char *Shell_RepairDataSegmentOffset(char *string)
{
    return (char*)((unsigned int)DataSegmentAddress + (unsigned int)string);
}

ExitCode_type Shell_Test(char *userInput)
{
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int command_size = MikosLib_StringLength(command);
    char *arg = GetArgument(userInput,2);
    Mikos_PrintString(Shell_RepairDataSegmentOffset("\nThe argument is: "));
    Mikos_PrintString(arg);
    Mikos_PrintString(Vocabulary.NewLine);

    Mikos_Free(command);
    Mikos_Free(arg);

    return Continue;
}

ExitCode_type Shell_List(char *userInput)
{
    Mikos_ListDirectories(0);
    return Continue;
}

ExitCode_type Shell_OpenFile(char *userInput)
{
    Mikos_PrintString(Vocabulary.NotYetImplemented);
    return Continue;
}

/**
* Free the \return argument once it's no longer needed.
*/
char *GetArgument(char *userInput,int argumentNumber)
{
    if(argumentNumber == 0)
    {
        return 0;
    }
    char *command = MikosLib_Util_StringSubstring(userInput,' ',InputSize,0);
    int command_size = MikosLib_StringLength(command);
    char* arg = command;
    int arg_offset = command_size + 1;
    for(int i =0; i < argumentNumber; i++)
    {
        arg = MikosLib_Util_StringSubstring(userInput,' ',InputSize - arg_offset,arg_offset);
        arg_offset += MikosLib_StringLength(arg) + 1;
    }

    Mikos_Free(command);
    return arg;
}
