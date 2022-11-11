# [utils]

### Links :

#### Frontend 
https://caniuse.com  
   
https://htmlcheatsheet.com/   
  
https://www.magicpattern.design/tools   
https://bennettfeely.com/     
https://css-tricks.com/   
https://www.inventiontricks.com/  

https://flexbox.help/  
https://grid.layoutit.com/  
  
  
#### others :
https://sourceware.org/projects.html | links to lot of sources.   
https://catonmat.net/tools | usefuls various tools  
https://rosettacode.org/wiki/Rosetta_Code | lot of good code sample / functions  
  
### Windows :
fw_block_all_exe.bat  | script pour bloquer/gerer plusieurs .exe a la fois dans le firewall. 
-cheatsheet

### Unix :
```
sudo apt install moreutils
```
Useful package with some tools more infos here => https://packages.debian.org/unstable/utils/moreutils
Permit to see errno code fast in cli :
```
$ errno 98
EADDRINUSE 98 Address already in use
``` 
### Ubuntu
restore_and_backup_apt_source_list.sh  | script to backup and restore default apt source liste. 
Ubuntu/backup  | sources.list backup

### Code :
rectangle_draw.c  | Light c code to draw rectangle in ascii with custom size. 

### Commands :

Allow commit without message ("-a" auto stage files that have been modified but not newly created) :
```
git commit -a --allow-empty-message -m ""
```


#### little and big endian : 2 method

fisrt with builtin:
```
	uint32_t be = __builtin_bswap32(port);
	printf(" Big endian big=%x\n", be);
```
  
  
second with C function:
```
	unsigned int little=0x1234578, big = 0;
	unsigned char tmp = 0;

	printf("Little endian little= %x \n", little);

	for(int l = 0; l < 4; l++) 
	{
    		tmp = 0;
		tmp = little | tmp;
		big = tmp | (big << 8);
		little = little >> 8;
	}
	printf("Big endian big =%x \n", big);
  ```
