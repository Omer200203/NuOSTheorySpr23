# Assignment_01

System call Assignment

Have to perform the following commands on the terminal before downloading the kernel...
Pre Requirements:
• sudo apt-get install gcc
• sudo apt-get install libncurses5-dev
• sudo apt-get install bison
• sudo apt-get install flex
• sudo apt install make
• sudo apt-get install libssl-dev
• sudo apt-get install libelf-dev
• sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe"
• sudo apt-get update
• sudo apt-get upgrade

After performing these commands on terminal now have to download the kernel. We must first get a kernel from kernel.org. We may either manually download it by selecting the "tarball" option or use the "wget" command to do it. I download the kernal from tarball rather then using wget command. After that, navigate to the folder where the kernel was downloaded and extract it by either clicking on it and choosing "extract to" from the context menu, or by typing "tar -xvf *filename*" into the address bar.

Go to the folder we just made, launch the terminal, and create a new C code file there by typing "gedit hello.c,".

![image](https://user-images.githubusercontent.com/125944925/220455276-4fe55162-8eb1-4cf1-9fb8-1e22baabbab2.png)

![image](https://user-images.githubusercontent.com/125944925/220454252-a130a47d-21f6-426d-bc53-ad13942bf044.png)

Then paste the code below into it:
#include <linux/kernel.h>
asmlinkage long sys_hello(void)
{
printk("Hello world\n");
return 0;
}

Now that we have a new folder, we need to make a Makefile for it so that anytime the kernel is generated, the code in the subdirectory is always compiled as well. We need to enter "gedit Makefile" and "obj-y:= hello.o" in our terminal to do this.

![image](https://user-images.githubusercontent.com/125944925/220455572-83831b1e-c8d4-4ade-a3bc-8db88a1fc87d.png)

![image](https://user-images.githubusercontent.com/125944925/220456277-9721d113-29b1-4c8f-84b0-f0351898c282.png)

We must add the system call entry to the syscall 64.tbl file, which stores the names of all the system calls in our system, because we are establishing a 64-bit system call in accordance with our system. We would need to add our system call to syscall 32.tbl if our system were a 32-bit system. (We may determine the system type by using "uname -m" on a terminal.) Syscall 64.tbl can be found in the kernel folder under /arch/x86/entry/syscalls. By using the cd command to navigate to this directory, we may modify the file by typing "gedit syscall 64.tbl."

![image](https://user-images.githubusercontent.com/125944925/220456587-4c2a695e-55f5-40d7-b653-b71d5bba850d.png)

Go down to line [334] in the syscall 64.tbl file, insert this line (which will be line 335), and then save the file.

![image](https://user-images.githubusercontent.com/125944925/220456981-d5ccc7f3-ea18-4eeb-9b2e-dd41f4dd4f98.png)

The system call prototype must now be added to the system header file, which is found in the kernel folder and is called "/include/linux/syscalls.h." In this file, we must include the prototype for our system call function.

![image](https://user-images.githubusercontent.com/125944925/220457268-0e57ba71-103c-484a-b8f1-85542955a0bd.png)

We only need to type the function name at the end of this file to add our function call to the system file and save it.

![image](https://user-images.githubusercontent.com/125944925/220457567-38d23369-cfee-4257-8937-0dea0ff67cee.png)

We now need to add our roll number to the extraversion of the kernel's build file and include the newly built module in the make file for our kernel. To do this, we search for "core-y" in the kernel's Makefile, navigate to its second instance under "KBUILD EXTMOD," and add our new module, "hello," at the end of it. Our make file will eventually resemble something like this:

![image](https://user-images.githubusercontent.com/125944925/220458108-e79307fc-2d1a-4d30-b5ed-179afd6b1b47.png)

![image](https://user-images.githubusercontent.com/125944925/220458276-0afeb391-d397-43cd-8306-d2093df7e8bd.png)

We must now make a kernel configuration file. The order of the stages immediately preceding this can change, but the order of this step and the steps that follow it cannot. Either a Menuconfig can be made, or the oldconfig can just be copied. I'll be utilising the oldconfig, which I copied, as the configuration for my new kernel. We first use the command "ls /boot | grep config" to find the configuration we currently have, and we then use the command "cp /boot/config-4.10.0-28-generic *our linux kernel directory*" to copy the configuration that is displayed to us. The system will automatically construct the new configuration for us and choose the default options if we then type "yes" | make oldconfig -j4" to create the old configuration.

![image](https://user-images.githubusercontent.com/125944925/220459181-ed8ff1f0-f79e-4f65-a58c-b178554221d5.png)

![image](https://user-images.githubusercontent.com/125944925/220459235-405190ac-df0b-4757-ba35-e4880a81f19f.png)

Config file successfully created

![image](https://user-images.githubusercontent.com/125944925/220459286-32d5e74e-6e99-44e4-ab13-a83056590246.png)

It is necessary to delete all of our old object and executable files by typing "make clean -j4" (It is preferable to enter super user mode by typing "sudo su" before running the commands after this). Once this is complete, we type "make -j4" to begin creating our kernel (-j4 allocates the multiple cores that our system has for compiling). Otherwise, the system will only use one core to compile the kernel, which is a fairly lengthy process. The use of -j4 will nearly quadruple the speed of our compilation. Note that my laptop has 4 cores, which is the number of cores. Others can enter the appropriate number after executing the command "lscpu" to check their core count.

![image](https://user-images.githubusercontent.com/125944925/220460309-de763384-6727-4c97-8224-cf498e2ea73e.png)

![image](https://user-images.githubusercontent.com/125944925/220460342-f77e3372-e2d1-4d5e-bced-c34e395b04a9.png)



lokmok,

Operating System Muhammad Omer Shoaib 21k-3066
