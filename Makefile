#!Makefile

CC 	:= gcc
LD 	:= ld
ASM := nasm
GDB	:= gdb

QEMU	:= qemu-system-i386
TERMINAL:= gnome-terminal

MKDIR 	:= mkdir -p
RM		:= rm -f
COPY	:= cp

OBJDIR	:= obj
BINDIR	:= bin

#-------Project----------
KNAME	:= os_kernel

INCLUDE := \
		drivers/ 	\
		fs/ 		\
		init/ 		\
		kernel/ 	\
		lib/ 		\
		mm/

SRCDIR	:= \
		drivers		\
		fs			\
		init		\
		kernel		\
		lib			\
		mm			\
#--------------------------

C_SOURCES	:= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
C_OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(C_SOURCES))))
S_SOURCES	:= $(shell find . -name "*.s")
S_OBJECTS	:= $(patsubst %.s, %.o, $(S_SOURCES))

CFLAGS 	:= -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-pic -fno-builtin -fno-stack-protector
LDFLAGS := -T scripts/kernel.ld -m elf_i386 -nostdlib
AFLAGS 	:= -f elf -g -F stabs

CFLAGS	+= $(addprefix -I ,$(INCLUDE))

define create_target
$(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(1)))) : $(1)
	@echo 编译代码文件 $< ...
	@if [ ! -d $(OBJDIR) ]; then $(MKDIR) $(OBJDIR); fi
	$(CC) -c $(CFLAGS) $$< -o $$@
endef


all: link image-update
	
$(foreach cfile, $(C_SOURCES), $(eval $(call create_target, $(cfile))))

#TODO: Rewrite ASM Target
.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(AFLAGS) $<


link: $(S_OBJECTS) $(C_OBJECTS)
	@echo 链接内核文件...
	$(LD) $(LDFLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $(BINDIR)/$(KNAME)


#TODO: Change this way
.PHONY: image-update image-mount image-umount
image-update:
	@if [ ! -d image ]; then $(MKDIR) image; fi
	sudo mount floppy.img image
	sudo $(COPY) $(BINDIR)/$(KNAME) image/os_kernel
	sleep 1
	sudo umount image

image-mount:
	@if [ ! -d image ]; then $(MKDIR) image; fi
	sudo mount floppy.img image

image-umount:
	sudo umount image


QEMUOPTS := -fda floppy.img -boot a -serial mon:stdio -parallel null

.PHONY: qemu qemu-nox debug debug-nox
qemu:
	$(QEMU) $(QEMUOPTS)

qemu-nox:
	$(QEMU) $(QEMUOPTS) -nographic

debug:
	$(QEMU) $(QEMUOPTS) -S -s 

debug-nox:
	$(QEMU) $(QEMUOPTS) -S -s -nographic


.PHONY: gdb
gdb:
	$(GDB) -x scripts/gdbinit


.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)/$(KNAME)