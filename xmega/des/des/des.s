#define __22_BIT_PC__

.global DES_Encrypt
DES_Encrypt:
	rcall	DES_INTERNAL_Prolog
	rcall	DES_INTERNAL_Load_Data
	clr	r16
	rcall	DES_INTERNAL_DES_Encrypt
	rcall	DES_INTERNAL_Store_Data
	rjmp	DES_INTERNAL_Epilog

.global DES_Decrypt
DES_Decrypt:
	rcall	DES_INTERNAL_Prolog
	rcall	DES_INTERNAL_Load_Data
	clr	r16
	rcall	DES_INTERNAL_DES_Decrypt
	rcall	DES_INTERNAL_Store_Data
	rjmp 	DES_INTERNAL_Epilog

.global DES_3DES_Encrypt
DES_3DES_Encrypt:
	rcall	DES_INTERNAL_Prolog
	rcall	DES_INTERNAL_Load_Data
	ser	r16
	rcall	DES_INTERNAL_DES_Encrypt
	rcall	DES_INTERNAL_Store_Data
	rjmp	DES_INTERNAL_Epilog

.global DES_3DES_Decrypt
DES_3DES_Decrypt:
	rcall	DES_INTERNAL_Prolog
	rcall	DES_INTERNAL_Load_Data
	ser	r16
	rcall	DES_INTERNAL_DES_Decrypt
	rcall	DES_INTERNAL_Store_Data
	rjmp	DES_INTERNAL_Epilog

.global DES_CBC_Encrypt
DES_CBC_Encrypt:
	rcall	DES_INTERNAL_Prolog
	movw	r26, r14
	rcall	DES_INTERNAL_Load_Data
	movw	r30, r18
	rcall	DES_INTERNAL_Load_Into_R15_R8
DES_INTERNAL_CBC_Encrypt_Next:
	rcall	DES_INTERNAL_XOR_Routine
	rcall	DES_INTERNAL_DES_Encrypt
	rcall	DES_INTERNAL_Store_Data
	sbiw	r26, 1
	breq	DES_INTERNAL_CBC_Encrypt_End
	movw	r30, r24
	rcall	DES_INTERNAL_Load_Into_R15_R8
	movw	r24, r30	
	rjmp	DES_INTERNAL_CBC_Encrypt_Next
DES_INTERNAL_CBC_Encrypt_End:
	rjmp	DES_INTERNAL_Epilog

.global DES_CBC_Decrypt
DES_CBC_Decrypt:
	rcall	DES_INTERNAL_Prolog
	movw	r26, r14
	rcall	DES_INTERNAL_Load_Data
	rcall	DES_INTERNAL_DES_Decrypt
	movw	r30, r18
DES_INTERNAL_CBC_Decrypt_Next:
	rcall	DES_INTERNAL_Load_Into_R15_R8
	rcall	DES_INTERNAL_XOR_Routine
	rcall	DES_INTERNAL_Store_Data
	sbiw	r26, 1
	breq	DES_INTERNAL_CBC_Decrypt_End
	rcall	DES_INTERNAL_Load_Data
	rcall	DES_INTERNAL_DES_Decrypt
	movw	r30, r24
	sbiw	r30, 16
	rjmp	DES_INTERNAL_CBC_Decrypt_Next
DES_INTERNAL_CBC_Decrypt_End:
	rjmp	DES_INTERNAL_Epilog

DES_INTERNAL_DES_Encrypt:
	movw	r30, r20
	rcall	DES_INTERNAL_Load_Into_R15_R8
	clh
	rcall	DES_INTERNAL_DES_Routine
	tst	r16
	breq	DES_INTERNAL_DES_Single_Encrypt
	movw	r30, r20
	adiw	r30, 8
	rcall	DES_INTERNAL_Load_Into_R15_R8
	seh
	rcall	DES_INTERNAL_DES_Routine
	movw	r30, r20
	adiw	r30, 16
	rcall	DES_INTERNAL_Load_Into_R15_R8
	clh
	rcall	DES_INTERNAL_DES_Routine
DES_INTERNAL_DES_Single_Encrypt:
	ret

DES_INTERNAL_DES_Decrypt:
	tst	r16
	breq	DES_INTERNAL_DES_Single_Decrypt
	movw	r30, r20
	adiw	r30, 16
	rcall	DES_INTERNAL_Load_Into_R15_R8
	seh
	rcall	DES_INTERNAL_DES_Routine
	movw	r30, r20
	adiw	r30, 8
	rcall	DES_INTERNAL_Load_Into_R15_R8
	clh
	rcall	DES_INTERNAL_DES_Routine
DES_INTERNAL_DES_Single_Decrypt:
	movw	r30, r20
	rcall	DES_INTERNAL_Load_Into_R15_R8
	seh
	rcall	DES_INTERNAL_DES_Routine
	ret

DES_INTERNAL_Load_Data:
	movw	r30, r24
	ld	r7, Z+
	ld	r6, Z+
	ld	r5, Z+
	ld	r4, Z+
	ld	r3, Z+
	ld	r2, Z+
	ld	r1, Z+
	ld	r0, Z+
	movw	r24, r30
	ret

DES_INTERNAL_Load_Into_R15_R8:
	ld	r15, Z+
	ld	r14, Z+
	ld	r13, Z+
	ld	r12, Z+
	ld	r11, Z+
	ld	r10, Z+
	ld	r9,  Z+
	ld	r8,  Z+
	ret

DES_INTERNAL_XOR_Routine:
	eor	r7, r15
	eor	r6, r14
	eor	r5, r13
	eor	r4, r12
	eor	r3, r11
	eor	r2, r10
	eor	r1,  r9
	eor	r0,  r8
	ret		

DES_INTERNAL_Store_Data:
	movw	r30, r22
	st	Z+,  r7
	st	Z+,  r6
	st	Z+,  r5
	st	Z+,  r4
	st	Z+,  r3
	st	Z+,  r2
	st	Z+,  r1
	st	Z+,  r0
	movw	r22, r30
	ret

DES_INTERNAL_DES_Routine:
	des	0
	des	1
	des	2
	des	3
	des	4
	des	5
	des	6
	des	7
	des	8
	des	9
	des	10
	des	11
	des	12
	des	13
	des	14
	des	15
	ret

DES_INTERNAL_Prolog:
#ifdef __22_BIT_PC__
	pop	r27
#endif
	pop	r30
	pop	r31
	push	r0
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	push	r16
	push	r17
	push	r28
	push	r29
	push	r31
	push	r30
#ifdef __22_BIT_PC__
	push	r27
#endif
	ret

DES_INTERNAL_Epilog:
	pop	r29
	pop	r28
	pop	r17
	pop	r16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r1
	pop	r0
	ret
