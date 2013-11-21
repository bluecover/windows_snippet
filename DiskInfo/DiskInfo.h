#pragma once

class CDiskInfo  
{
public:
    int GetDiskInfo(int driver=0);
    char m_ModelNumber[64];
    char m_SerialNumber[64];
    CDiskInfo();
    virtual ~CDiskInfo();

};
