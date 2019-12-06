//Working Title: 'FORTUNA' Homebrew Launcher
//Written by VTSTech (veritas@vts-tech.org)
//Version: 0.41

#include <debug.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <sbv_patches.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <unistd.h>
#include <input.h>
#include <time.h>
#include <string.h>
#include <libcdvd.h>

#include "FORTUNA_Launcher.h"

u64 Timer(void)
{
	return (clock() / (CLOCKS_PER_SEC / 1000));
}
static int resetiop = 0;

//** Function ResetIOP() from main.c MPLUS-LOADER3.ELF
//** http://lukasz.dk/2008/04/22/datel-memory-plus-64-mb/
void ResetIOP()
{
	if(resetiop)
	{
		fioExit();
		SifExitIopHeap();
		SifLoadFileExit();
		SifExitRpc();
	}

	SifIopReset("rom0:UDNL rom0:EELOADCNF", 0);
    
	while (SifIopSync()) ;

	resetiop = 1;

	SifInitRpc(0);
}

//** Function LoadElf() from main.c MPLUS-LOADER3.ELF
//** http://lukasz.dk/2008/04/22/datel-memory-plus-64-mb/
void LoadElf(const char *elf, char* path)
{
	char* args[1];
	t_ExecData exec;	

	SifLoadElf(elf, &exec);

	#ifdef DEBUG
		scr_printf("Trying to load ELF: %s\n", elf);
	#endif	

	if(exec.epc > 0)
	{	
		FlushCache(0);
		FlushCache(2);

		// Reset IOP, since not all ELF's do it and we've loaded additional IOP
		// modules which need to be unloaded
		ResetIOP();

		if(path != 0)
		{
			args[0] = path;
			ExecPS2((void*)exec.epc, (void*)exec.gp, 1, args);
		}
		else
		{
			ExecPS2((void*)exec.epc, (void*)exec.gp, 0, NULL);
		}
	}
}

extern u64 WaitTime;
extern u64 CurrTime;

u64 Timer(void);

u64 WaitTime;
u64 CurrTime;
u64 init_delay_start;
u64 timeout_start;

void banner()
{
	scr_clear();
  sleep(1);
  scr_printf("============================================= \n");
  scr_printf("==FORTUNA Homebrew Launcher===12.06.2019===== \n");
  scr_printf("==v0.41 Written by VTSTech of PSX-Place.com== \n");
  scr_printf("==FORTUNA Exploit by krat0s of PS2-Home.com== \n");
  scr_printf("==www.vts-tech.org=========================== \n\n");	
}

int main(int argc, char *argv[], char **envp)
{
	char *target, *path;
	char device[50];
	char folder[50];
 	SifInitRpc(0);
	init_scr();
	banner();
	SifLoadModule("rom0:SIO2MAN", 0, NULL);
	SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
	SifLoadModule("rom0:PADMAN", 0, NULL);
	sbv_patch_disable_prefix_check();
	path="";
	strcpy(device,"mc0:");
	strcpy(folder,"/FORTUNA/");
	setupPad();
	WaitTime = Timer();
	int state = padGetState(0,0);
	int CdStatus;
	int devshown = 0;
	int devset = 0;
	int menushown = 0;
	sleep(1);
	if (state == 6) {
		//SEL = 1
		//L3  = 2
		//R3  = 4
		//STR = 8
		//UP  = 16
		//RGT = 32
		//DWN = 64
		//LFT = 128
		//L2  = 256
		//R2  = 512
		//L1  = 1024
		//R1  = 2048
		// /\ = 4096
		// O  = 8192
		// X  = 16384
		//[ ] = 32768
		sceCdInit(SCECdINoD);
	  CdStatus = sceCdStatus();
		while(1) {
			//int state;
			state = readpad();
			//CdStatus = sceCdStatus();
			if (devshown == 0 && menushown == 0) {
				scr_printf(" \n *  X * Use Device: mc0 and Folder: FORTUNA \n");
				scr_printf(" \n *  O * Use Device: mass and Folder: FORTUNA \n");
				scr_printf(" \n * /\\ * Use Device: mc0 and Folder: APPS \n");
				scr_printf(" \n * [] * Use Device: mass and Folder: APPS \n");
				devshown = 1;
			}							
			if (state != 1) {
				//scr_printf("Debug: %d \n",state);
				if (menushown == 1 && devshown == 1 && devset == 1) {
					if (new_pad == 32768) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"snes_emu.elf");
						scr_printf(" \nPreparing to run SNESStation v0.2.6c (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);					
					} else if (new_pad == 16384) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"WLE.ELF");
						scr_printf(" \nPreparing to run wLaunchElf v4.43a (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 8192) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"OPL.ELF");
						scr_printf(" \nPreparing to run OPL Open PS2 Loader v0.9.3 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 4096) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"GSM.ELF");
						scr_printf(" \nPreparing to run GSM v0.3.8 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 2048) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"retroarchps2_picodrive.elf");
						scr_printf(" \nPreparing to run RetroArch PicoDrive Core v1.8.1 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 1024) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"retroarchps2_2048.elf");
						scr_printf(" \nPreparing to run RetroArch 2048 Core v1.8.1 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 512) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"retroarchps2_quicknes.elf");
						scr_printf(" \nPreparing to run RetroArch QuickNES Core v1.8.1 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 256) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"retroarchps2_fceumm.elf");
						scr_printf(" \nPreparing to run RetroArch FCEUmm Core v1.8.1 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 16) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"ESR.ELF");
						scr_printf(" \nPreparing to run ESR r9b (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);
					} else if (new_pad == 8) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"BOOT.ELF");
						scr_printf(" \nPreparing to return to OSD ...\n");
						sleep(1);
						break;
					} else if (new_pad == 4) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"PS2Ident.elf");
						scr_printf(" \nPreparing to run PS2Ident v0.835 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);					
					} else if (new_pad == 2) {
						target = device;
						strcat(target,folder);
						path = target;
						strcat(target,"retroarchps2_mgba.elf");
						scr_printf(" \nPreparing to run RetroArch mGBA Core v1.8.1 (%s) ... \n", target);
						sleep(1);
						LoadElf(target,path);										
					}
				} //devshown,devset,menushown							 
			}// state,cdstatus										
			if (menushown == 0 && devset == 1) {
				banner();
				scr_printf("Device: %s Folder: %s \n", device, folder);
				scr_printf(" \n *  X * Run wLaunchElf v4.43a Build: 8d4a0c2 Date: 03.30.2019");
				scr_printf(" \n *  O * Run OPL Open PS2 Loader v0.9.3 r1650 Build: 23e844a Date: 12.04.2019");
				scr_printf(" \n * /\\ * Run GSM v0.3.8 Build: N/A Date: 01.14.2016");
				scr_printf(" \n * [] * Run SNESStation v0.2.6c Build: N/A Date: 11.22.2016");
				scr_printf(" \n * L1 * Run RetroArch 2048 v1.8.1 Build: bfdc8e6 Date: 11.15.2019");
				scr_printf(" \n * L2 * Run RetroArch FCEUmm v1.8.1 Build: bfdc8e6 Date: 11.15.2019");		
				scr_printf(" \n * L3 * Run RetroArch mGBA v1.8.1 Build: bfdc8e6 Date: 11.15.2019");
				scr_printf(" \n * R1 * Run RetroArch PicoDrive v1.8.1 Build: bfdc8e6 Date: 11.15.2019");		
				scr_printf(" \n * R2 * Run RetroArch QuickNES v1.8.1 Build: bfdc8e6 Date: 11.15.2019");		
				scr_printf(" \n * R3 * Run PS2Ident v0.835 Build: N/A Date: 11.08.2019");
				scr_printf(" \n * UP * Run ESR r9b Build: N/A Date: 09.05.2008");
				scr_printf(" \n \nPush START to exit. \n");
				//scr_printf(" \n \nController ready. Waiting for input... \n");
				menushown = 1;
			}		
			if (devshown == 1 && devset == 0) {							
				if (new_pad != 0) {
					//scr_printf("Debug: %d \n", new_pad);
					}
				if (new_pad == 16384) {
					strcpy(device,"mc0:");
					strcpy(folder,"/FORTUNA/");							
					scr_setXY(1,7);
					sleep(1);
					scr_printf("Device: %s Folder: %s \n", device, folder);
					devset = 1;		
				}	else if (new_pad == 8192) {
					strcpy(device,"mass:");
					strcpy(folder,"/FORTUNA/");								
					scr_setXY(1,7);
					sleep(1);
					scr_printf("Device: %s Folder: %s \n", device, folder);				
					devset = 1;
				}	else if (new_pad == 4096) {
					strcpy(device,"mc0:");
					strcpy(folder,"/APPS/");							
					scr_setXY(1,7);
					sleep(1);
					scr_printf("Device: %s Folder: %s \n", device, folder);			
					devset = 1;
				}	else if (new_pad == 32768) {
					strcpy(device,"mass:");
					strcpy(folder,"/APPS/");							
					scr_setXY(1,7);
					sleep(1);
					scr_printf("Device: %s Folder: %s \n", device, folder);			
					devset = 1;
				}
			}
			//scr_printf("Debug: %d \n", devset);
		} //main loop
	} // controller ready
	return 0;
}
