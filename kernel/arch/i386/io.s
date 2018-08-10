.section .text
.global outb
.type outb, @function
/*
outb
	Write a byte to an I/O port
	; stack: 	[esp + 8] the data byte
	; 			[esp + 4] the I/O port
	; 			[esp    ] return address
*/
outb:
	mov 8(%esp), %al /* move the data to be sent into the al register */
	mov 4(%esp), %dx /* move the address of the I/O port into the dx register */
	out %al, %dx
	ret	