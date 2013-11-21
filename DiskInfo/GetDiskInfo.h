#include "stdafx.h"


//#pragma argsused

#define   DFP_GET_VERSION   0x00074080
#define   DFP_SEND_DRIVE_COMMAND   0x0007c084
#define   DFP_RECEIVE_DRIVE_DATA   0x0007c088

#define  SENDIDLENGTH  sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE
#define  IDENTIFY_BUFFER_SIZE  512
#define  FILE_DEVICE_SCSI              0x0000001b
#define  IOCTL_SCSI_MINIPORT_IDENTIFY  ((FILE_DEVICE_SCSI << 16) + 0x0501)
#define  IOCTL_SCSI_MINIPORT 0x0004D008  //  see NTDDSCSI.H for definition
#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.
#define  IOCTL_GET_DRIVE_INFO   0x0007c088
#define  IOCTL_GET_VERSION          0x00074080


#pragma   pack(1)
typedef   struct   _GETVERSIONOUTPARAMS   
{
    BYTE   bVersion;        //Binary   driver   version.
    BYTE   bRevision;       //Binary   driver   revision.
    BYTE   bReserved;       //Not   used.
    BYTE   bIDEDeviceMap;   //Bit   map   of   IDE   devices.
    DWORD   fCapabilities; //Bit   mask   of   driver   capabilities.
    DWORD   dwReserved[4]; //For   future   use.
}   GETVERSIONOUTPARAMS,   *PGETVERSIONOUTPARAMS,   *LPGETVERSIONOUTPARAMS;   

typedef   struct   _IDEREGS   {
    BYTE   bFeaturesReg;     //Used for   specifying   SMART   "commands".
    BYTE   bSectorCountReg;   //IDE   sector   count   register
    BYTE   bSectorNumberReg;   //IDE   sector   number   register
    BYTE   bCylLowReg;       //   IDE   low   order   cylinder   value     
    BYTE   bCylHighReg;     //   IDE   high   order   cylinder   value     
    BYTE   bDriveHeadReg;     //   IDE   drive/head   register     
    BYTE   bCommandReg;     //   Actual   IDE   command.     
    BYTE   bReserved;       //   reserved   for   future   use.     Must   be   zero.     
}   IDEREGS,   *PIDEREGS,   *LPIDEREGS;    

typedef   struct   _SENDCMDINPARAMS   {     
    DWORD   cBufferSize;     //   Buffer   size   in   bytes     
    IDEREGS   irDriveRegs;     //   Structure   with   drive   register   values.     
    BYTE   bDriveNumber;     //   Physical   drive   number   to   send     
    //   command   to   (0,1,2,3).     
    BYTE   bReserved[3];     //   Reserved   for   future   expansion.     
    DWORD   dwReserved[4];     //   For   future   use.     
    //BYTE     bBuffer[1];       //   Input   buffer.     
}   SENDCMDINPARAMS,   *PSENDCMDINPARAMS,   *LPSENDCMDINPARAMS;    

typedef   struct   _DRIVERSTATUS   {     
    BYTE   bDriverError;     //   Error   code   from   driver,     
    //   or   0   if   no   error.     
    BYTE   bIDEStatus;       //   Contents   of   IDE   Error   register.     
    //   Only   valid   when   bDriverError     
    //   is   SMART_IDE_ERROR.     
    BYTE   bReserved[2];     //   Reserved   for   future   expansion.     
    DWORD   dwReserved[2];     //   Reserved   for   future   expansion.     
}   DRIVERSTATUS,   *PDRIVERSTATUS,   *LPDRIVERSTATUS;    

typedef   struct   _SENDCMDOUTPARAMS   {     
    DWORD         cBufferSize;     //   Size   of   bBuffer   in   bytes     
    DRIVERSTATUS   DriverStatus;     //   Driver   status   structure.     
    BYTE       bBuffer[512];       //   Buffer   of   arbitrary   length     
    //   in   which   to   store   the   data   read   from   the   drive.     
}   SENDCMDOUTPARAMS,   *PSENDCMDOUTPARAMS,   *LPSENDCMDOUTPARAMS;    

typedef   struct   _IDSECTOR   {     
    USHORT   wGenConfig;     
    USHORT   wNumCyls;     
    USHORT   wReserved;     
    USHORT   wNumHeads;     
    USHORT   wBytesPerTrack;     
    USHORT   wBytesPerSector;     
    USHORT   wSectorsPerTrack;     
    USHORT   wVendorUnique[3];     
    CHAR   sSerialNumber[20];     
    USHORT   wBufferType;     
    USHORT   wBufferSize;     
    USHORT   wECCSize;     
    CHAR   sFirmwareRev[8];     
    CHAR   sModelNumber[40];     
    USHORT   wMoreVendorUnique;     
    USHORT   wDoubleWordIO;     
    USHORT   wCapabilities;     
    USHORT   wReserved1;     
    USHORT   wPIOTiming;     
    USHORT   wDMATiming;     
    USHORT   wBS;     
    USHORT   wNumCurrentCyls;     
    USHORT   wNumCurrentHeads;     
    USHORT   wNumCurrentSectorsPerTrack;     
    ULONG   ulCurrentSectorCapacity;     
    USHORT   wMultSectorStuff;     
    ULONG   ulTotalAddressableSectors;     
    USHORT   wSingleWordDMA;     
    USHORT   wMultiWordDMA;     
    BYTE   bReserved[128];     
}   IDSECTOR,   *PIDSECTOR;
typedef struct _SRB_IO_CONTROL
{
    ULONG HeaderLength;
    UCHAR Signature[8];
    ULONG Timeout;
    ULONG ControlCode;
    ULONG ReturnCode;
    ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

VOID   ChangeByteOrder(PCHAR   szString,   USHORT   uscStrSize) 
{
    USHORT   i;
    CHAR   temp;    

    for   (i   =   0;   i   <   uscStrSize;   i+=2)
    {
        temp   =   szString[i];
        szString[i]   =   szString[i+1];
        szString[i+1]   =   temp;
    }
}

PCHAR DeleteHeadSpace(PCHAR TheString) //删除获取序列号开头的空格，便于其他调用
{
    int j=0;
    for(int i=0;i<strlen(TheString);i++)
    {
        if(!isspace(TheString[i])) break;
        j++;
    }

    return &TheString[j];
}

bool HD_IDE_NT(CString& ret)
{
    GETVERSIONOUTPARAMS   vers;     
    SENDCMDINPARAMS   in;     
    SENDCMDOUTPARAMS   out;     
    HANDLE   h;     
    DWORD   i;
    BYTE   j;
    char HardDiskNO[200];
    bool IDEFlag=false;
    char hd[80];
    PIDSECTOR   phdinfo;
    char s[61];

    ZeroMemory(&vers,sizeof(vers)); 

    for (j = 0; j < 4; j++)
    {
        sprintf(hd,"\\\\.\\PhysicalDrive%d",j);
        h = CreateFile(hd,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        //  Windows NT/2000/XP下创建文件需要管理员权限
        if (!h) continue;
        if (!DeviceIoControl(h,DFP_GET_VERSION,0,0,&vers,sizeof(vers),&i,0))
            // 得到驱动器的IO控制器版本
        {
            CloseHandle(h);
            continue;
        }

        if (!(vers.fCapabilities&1)){
            CloseHandle(h);
            return false;
        }

        ZeroMemory(&in,sizeof(in));
        ZeroMemory(&out,sizeof(out));

        if (j&1)
        {
            in.irDriveRegs.bDriveHeadReg=0xb0;
        }
        else
        {
            in.irDriveRegs.bDriveHeadReg=0xa0;
        }
        if (vers.fCapabilities&(16>>j)) continue;
        else
        {
            in.irDriveRegs.bCommandReg=0xec;
        }
        in.bDriveNumber=j;
        in.irDriveRegs.bSectorCountReg=1;
        in.irDriveRegs.bSectorNumberReg=1;
        in.cBufferSize=512;

        if (!DeviceIoControl(h,DFP_RECEIVE_DRIVE_DATA,&in,sizeof(in),&out,sizeof(out),&i,0))
        {
            CloseHandle(h);
            return IDEFlag;
        }

        phdinfo=(PIDSECTOR)out.bBuffer;

        memcpy(s,phdinfo->sModelNumber,sizeof(phdinfo->sModelNumber));     
        s[sizeof(phdinfo->sModelNumber)]=0;
        ChangeByteOrder(s,sizeof(phdinfo->sModelNumber));

        memcpy(s,phdinfo->sSerialNumber,sizeof(phdinfo->sSerialNumber));
        s[sizeof(phdinfo->sSerialNumber)]=0;
        ChangeByteOrder(s,sizeof(phdinfo->sSerialNumber)); 

        strcpy(HardDiskNO, DeleteHeadSpace(s)); 
        ret = HardDiskNO;
        IDEFlag=true;
        CloseHandle(h);
        break;
    }

    return  IDEFlag; 
}
