
arquivo2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <funcao>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	bf 00 00 00 00       	mov    $0x0,%edi
   9:	e8 00 00 00 00       	callq  e <funcao+0xe>
   e:	90                   	nop
   f:	5d                   	pop    %rbp
  10:	c3                   	retq   

Disassembly of section .rodata:

0000000000000000 <.rodata>:
   0:	45 73 74             	rex.RB jae 77 <funcao+0x77>
   3:	6f                   	outsl  %ds:(%rsi),(%dx)
   4:	75 20                	jne    26 <funcao+0x26>
   6:	6e                   	outsb  %ds:(%rsi),(%dx)
   7:	6f                   	outsl  %ds:(%rsi),(%dx)
   8:	20 61 72             	and    %ah,0x72(%rcx)
   b:	71 75                	jno    82 <funcao+0x82>
   d:	69 76 6f 20 32 21 00 	imul   $0x213220,0x6f(%rsi),%esi

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%rdi)
   3:	43 3a 20             	rex.XB cmp (%r8),%spl
   6:	28 47 4e             	sub    %al,0x4e(%rdi)
   9:	55                   	push   %rbp
   a:	29 20                	sub    %esp,(%rax)
   c:	36 2e 33 2e          	ss xor %cs:(%rsi),%ebp
  10:	31 20                	xor    %esp,(%rax)
  12:	32 30                	xor    (%rax),%dh
  14:	31 36                	xor    %esi,(%rsi)
  16:	31 32                	xor    %esi,(%rdx)
  18:	32 31                	xor    (%rcx),%dh
  1a:	20 28                	and    %ch,(%rax)
  1c:	52                   	push   %rdx
  1d:	65 64 20 48 61       	gs and %cl,%fs:0x61(%rax)
  22:	74 20                	je     44 <funcao+0x44>
  24:	36 2e 33 2e          	ss xor %cs:(%rsi),%ebp
  28:	31                   	.byte 0x31
  29:	2d                   	.byte 0x2d
  2a:	31 29                	xor    %ebp,(%rcx)
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	00 00                	add    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	01 7a 52             	add    %edi,0x52(%rdx)
   b:	00 01                	add    %al,(%rcx)
   d:	78 10                	js     1f <.eh_frame+0x1f>
   f:	01 1b                	add    %ebx,(%rbx)
  11:	0c 07                	or     $0x7,%al
  13:	08 90 01 00 00 1c    	or     %dl,0x1c000001(%rax)
  19:	00 00                	add    %al,(%rax)
  1b:	00 1c 00             	add    %bl,(%rax,%rax,1)
  1e:	00 00                	add    %al,(%rax)
  20:	00 00                	add    %al,(%rax)
  22:	00 00                	add    %al,(%rax)
  24:	11 00                	adc    %eax,(%rax)
  26:	00 00                	add    %al,(%rax)
  28:	00 41 0e             	add    %al,0xe(%rcx)
  2b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  31:	4c 0c 07             	rex.WR or $0x7,%al
  34:	08 00                	or     %al,(%rax)
	...
