这是我的计算机二学位的毕业设计。
它原来是windows平台的，现在将其移植到*nux上。

它使用的MPIR(Multiple Precision Integers and Rationals)库。
其主页为www.mpir.org
我使用的是mpir-2.2.1
编译获得libmpir的方法:
1、./confgure --disble-shared #动态链接库不能编译通过
2、make && make check
3、静态库文件为 ./libs/libmpir.a

本软件的编译:
gcc rsa_cli.c -IL ./libmpir.a -o rsa-cli