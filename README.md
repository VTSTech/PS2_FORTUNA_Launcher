# PS2_FORTUNA_Launcher
 PS2 FORTUNA Homebrew Launcher

<img src="https://i.gyazo.com/ff6128abdace0d4dcb027e58326cca41.png">

<img src="https://i.gyazo.com/b65197ff89ed315e617fe78fa3e95bc2.png">

In case anyone missed it, There is a new PS2 Exploit by krat0s https://www.ps2-home.com/forum/viewtopic.php?f=107&t=8542

This is designed to work with that package/folder/savefile

Rename FORTUNA_Launcher.elf to BOOT.ELF and copy to your mc0:/FORTUNA/ folder

PSX-Place FORTUNA Launcher Release Thread https://www.psx-place.com/threads/fortuna-launcher-by-vtstech-boot-elf-replacement.27254/

It can use the following paths:

<pre>

wLaunchElf

mc0:/FORTUNA/WLE.ELF
mass:/FORTUNA/WLE.ELF
mc0:/APPS/WLE.ELF
mass:/APPS/WLE.ELF

OPL

mc0:/FORTUNA/OPL.ELF
mass:/FORTUNA/OPL.ELF
mc0:/APPS/OPL.ELF
mass:/APPS/OPL.ELF

GSM

mc0:/FORTUNA/GSM.ELF
mass:/FORTUNA/GSM.ELF
mc0:/APPS/GSM.ELF
mass:/APPS/GSM.ELF

ESR

mc0:/FORTUNA/ESR.ELF
mass:/FORTUNA/ESR.ELF
mc0:/APPS/ESR.ELF
mass:/APPS/ESR.ELF

RetroArch

mc0:/FORTUNA/retroarchps2_2048.elf
mc0:/FORTUNA/retroarchps2_fceumm.elf
mc0:/FORTUNA/retroarchps2_mgba.elf
mc0:/FORTUNA/retroarchps2_picodrive.elf
mc0:/FORTUNA/retroarchps2_quicknes.elf
mass:/FORTUNA/retroarchps2_2048.elf
mass:/FORTUNA/retroarchps2_fceumm.elf
mass:/FORTUNA/retroarchps2_mgba.elf
mass:/FORTUNA/retroarchps2_picodrive.elf
mass:/FORTUNA/retroarchps2_quicknes.elf
mc0:/APPS/retroarchps2_2048.elf
mc0:/APPS/retroarchps2_fceumm.elf
mc0:/APPS/retroarchps2_mgba.elf
mc0:/APPS/retroarchps2_picodrive.elf
mc0:/APPS/retroarchps2_quicknes.elf
mass:/APPS/retroarchps2_2048.elf
mass:/APPS/retroarchps2_fceumm.elf
mass:/APPS/retroarchps2_mgba.elf
mass:/APPS/retroarchps2_picodrive.elf
mass:/APPS/retroarchps2_quicknes.elf

SNESStation

mc0:/FORTUNA/snes_emu.elf
mass:/FORTUNA/snes_emu.elf
mc0:/APPS/snes_emu.elf
mass:/APPS/snes_emu.elf

PS2Ident

mc0:/FORTUNA/PS2Ident.elf
mass:/FORTUNA/PS2Ident.elf
mc0:/APPS/PS2Ident.elf
mass:/APPS/PS2Ident.elf
</pre>


Changelog  
<pre>
v0.41
Correct release date of OPL
Minor text display adjustments

v0.4
Minor code cleanup
Removed few debug messages
Added support for ESR
Bump OPL to r1650

v0.3
Can now use different paths and devices!
Can select mc0 or mass
Can select FORTUNA or APPS
No more sub folders
Source Code released

v0.2
Added GSM
Added PS2Ident
Added many more RetroArch Cores
Now Initializes DVD Drive and stops CD if it is present.

v0.1
First release
pad.c and pad related functions from wLaunchElf.elf 8d4a0c2
Function ResetIOP() from main.c MPLUS-LOADER3.ELF
Function LoadElf() from main.c MPLUS-LOADER3.ELF </pre>
