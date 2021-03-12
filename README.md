# OS

## 目录结构说明

```
.
├── bin						# 编译输出目录
├── boot			# bootloader相关代码
├── drivers			# 系统驱动代码
├── floppy.img    			# 操作系统软盘镜像
├── fs				# 文件系统代码
├── image					# 镜像临时挂载点
├── init			# 内核初始化代码
├── kernel        	# 主要的内核代码
├── lib				# 内核库代码
├── mm				# 内存管理代码
└── scripts					# 配置文件
```

## 需要注意的问题

1. 使用nasm作为汇编器，可能需要安装。
2. 使用了mount指令，只能在超级用户模式下运行。
3. 如果需要添加源文件目录或头文件目录，需要在Makefile中的SRCDIR和INCLUDE变量里对应加入目录名。

