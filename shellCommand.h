#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#define SYSTEM_NAME "powershell.exe -c \"Get-CimInstance -ClassName Win32_ComputerSystem | Select-Object Model\""
#define SN_ID "Get-CimInstance -ClassName Win32_Bios | Select-Object SerialNumber"
#define CPU_NAME "Get-CimInstance -ClassName Win32_Processor | Select-Object Name"
#define MEMORY_SIZE "(Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory"
#define SSD_SIZE "Get-PhysicalDisk | Select-Object Size"
#define HDD_SIZE "Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'SSD'} | Select-Object Size"
#define GPU_NAME "Get-CimInstance -ClassName Win32_VideoController | Select-Object Name"
#define BATTERY_STATS

#endif