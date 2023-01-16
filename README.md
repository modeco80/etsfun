
# ETSfun

After learning the [Hydro Thunder](https://en.wikipedia.org/wiki/Hydro_Thunder) arcade cabinets use the Phar Lap TNT Embedded ToolSuite RTOS (and that the Monitor just loads PE files), I decided to have a go at playing around with the upgrade floppy to see if it would boot a PE file I wrote myself.

I got it working fairly quickly, and I played around with it some until deciding to clean it up.

# How to build?

You will need mingw-w64 tools. MSVC could be used too but eh

`make` will build the EXE and copy it on to the boot floppy

`make test` will test in the [Bochs emulator](https://en.wikipedia.org/wiki/Bochs). I'd use QEMU but the boot loader literally doesn't work.

# Notes

The TNT RTOS seems to be structured like so:

- Monitor (loader & seems to provide very basic bootstrap calls)
    - Application (PE file)
        - TNT Kernel libraries
	        - Runtime (unpacking compressed ROMDATA/such)
	        - Multitasking
	        - Realtime (seemingly optional, weirdly enough)
	        - Filesystem
	        - TCP/IP stack (of note; used by Hydro Thunder)
	        - Win32 API source compatibility (for the most part)

 This repository basically only reimplements the Application PE file, however one could in theory write a replacement kernel with modern code for fun. I kinda wanna do that honestly.
