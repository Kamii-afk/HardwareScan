#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#define SYSTEM_NAME "powershell.exe -c \"Get-CimInstance -ClassName Win32_ComputerSystem | Select-Object Model\""
#define SN_ID "powershell.exe -c \"Get-CimInstance -ClassName Win32_Bios | Select-Object SerialNumber\""
#define CPU_NAME "powershell.exe -c \"Get-CimInstance -ClassName Win32_Processor | Select-Object Name\""
#define MEMORY_SIZE "powershell.exe -c \"(Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory\""
/* #define SSD_SCAN "powershell.exe -c \"Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'SSD'} | Select-Object FriendlyName, BusType\"" */
#define SSD_SCAN "powershell.exe -c \"Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'SSD'} | ForEach-Object {\"$($_.FriendlyName)|$($_.BusType)|$($_.Size)}\""
/* #define SSD_SIZE "powershell.exe -c \"Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'SSD'} | Select-Object Size\"" */
#define HDD_NAME "powershell.exe -c \"Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'HDD'} | Select-Object FriendlyName\""
#define HDD_SIZE "powershell.exe -c \"Get-PhysicalDisk | Where-Object {$_.MediaType -eq 'HDD'} | Select-Object Size\""
#define GPU_NAME "powershell.exe -c \"Get-CimInstance -ClassName Win32_VideoController | Select-Object Name\""
#define BATTERY_STATS

#endif