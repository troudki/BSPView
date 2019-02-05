.globl vline_native

vline_native:
	| vline_native(u8* buf, s16 dy, u8 col)
	move.l 4(%sp), %a0		| a0 is buf
	moveq.l #0, %d0
	
	move.w #159, %d0
	sub.w 10(%sp), %d0		| d0 is 159-dy
	
	move.b 15(%sp), %d1		| d1 is col

	lsl.w #2, %d0			| d0 is (159-(dy/cnt))*4
	
	jmp draw_table(%pc, %d0.W)	| jumps to after_unrolled_loop when finished


	|	jmp draw_table_slot_0
	| each write in the table below is 4 bytes
	
	
	| subq.w #1, %d0
	| ble end_vline_native
	| btst #0, %d0
	| bne lp

	| move.b %d1, (%a0)
	| sub.w #128, %a0

	| subq #1, %d0

lp:	
	| move.b %d1, (%a0)
	| sub.w #128, %a0
	| move.b %d1, (%a0)
	| sub.w #128, %a0
	| subq.w #1, %d0
	| dbeq %d0, lp
	
| end_vline_native:	
|	movem.l (%sp)+, %d2/%a1 
|	rts
	
	
draw_table:
draw_table_slot_159:	
	move.b %d1, 20352(%a0)
draw_table_slot_158:	
	move.b %d1, 20224(%a0)
	move.b %d1, 20096(%a0)
	move.b %d1, 19968(%a0)
	move.b %d1, 19840(%a0)
	move.b %d1, 19712(%a0)
	move.b %d1, 19584(%a0)
	move.b %d1, 19456(%a0)
	move.b %d1, 19328(%a0)
	move.b %d1, 19200(%a0)
	move.b %d1, 19072(%a0)
	move.b %d1, 18944(%a0)
	move.b %d1, 18816(%a0)
	move.b %d1, 18688(%a0)
	move.b %d1, 18560(%a0)
	move.b %d1, 18432(%a0)
	move.b %d1, 18304(%a0)
	move.b %d1, 18176(%a0)
	move.b %d1, 18048(%a0)
	move.b %d1, 17920(%a0)
	move.b %d1, 17792(%a0)
	move.b %d1, 17664(%a0)
	move.b %d1, 17536(%a0)
	move.b %d1, 17408(%a0)
	move.b %d1, 17280(%a0)
	move.b %d1, 17152(%a0)
	move.b %d1, 17024(%a0)
	move.b %d1, 16896(%a0)
	move.b %d1, 16768(%a0)
	move.b %d1, 16640(%a0)
	move.b %d1, 16512(%a0)
	move.b %d1, 16384(%a0)
	move.b %d1, 16256(%a0)
	move.b %d1, 16128(%a0)
	move.b %d1, 16000(%a0)
	move.b %d1, 15872(%a0)
	move.b %d1, 15744(%a0)
	move.b %d1, 15616(%a0)
	move.b %d1, 15488(%a0)
	move.b %d1, 15360(%a0)
	move.b %d1, 15232(%a0)
	move.b %d1, 15104(%a0)
	move.b %d1, 14976(%a0)
	move.b %d1, 14848(%a0)
	move.b %d1, 14720(%a0)
	move.b %d1, 14592(%a0)
	move.b %d1, 14464(%a0)
	move.b %d1, 14336(%a0)
	move.b %d1, 14208(%a0)
	move.b %d1, 14080(%a0)
	move.b %d1, 13952(%a0)
	move.b %d1, 13824(%a0)
	move.b %d1, 13696(%a0)
	move.b %d1, 13568(%a0)
	move.b %d1, 13440(%a0)
	move.b %d1, 13312(%a0)
	move.b %d1, 13184(%a0)
	move.b %d1, 13056(%a0)
	move.b %d1, 12928(%a0)
	move.b %d1, 12800(%a0)
	move.b %d1, 12672(%a0)
	move.b %d1, 12544(%a0)
	move.b %d1, 12416(%a0)
	move.b %d1, 12288(%a0)
	move.b %d1, 12160(%a0)
	move.b %d1, 12032(%a0)
	move.b %d1, 11904(%a0)
	move.b %d1, 11776(%a0)
	move.b %d1, 11648(%a0)
	move.b %d1, 11520(%a0)
	move.b %d1, 11392(%a0)
	move.b %d1, 11264(%a0)
	move.b %d1, 11136(%a0)
	move.b %d1, 11008(%a0)
	move.b %d1, 10880(%a0)
	move.b %d1, 10752(%a0)
	move.b %d1, 10624(%a0)
	move.b %d1, 10496(%a0)
	move.b %d1, 10368(%a0)
	move.b %d1, 10240(%a0)
	move.b %d1, 10112(%a0)
	move.b %d1, 9984(%a0)
	move.b %d1, 9856(%a0)
	move.b %d1, 9728(%a0)
	move.b %d1, 9600(%a0)
	move.b %d1, 9472(%a0)
	move.b %d1, 9344(%a0)
	move.b %d1, 9216(%a0)
	move.b %d1, 9088(%a0)
	move.b %d1, 8960(%a0)
	move.b %d1, 8832(%a0)
	move.b %d1, 8704(%a0)
	move.b %d1, 8576(%a0)
	move.b %d1, 8448(%a0)
	move.b %d1, 8320(%a0)
	move.b %d1, 8192(%a0)
	move.b %d1, 8064(%a0)
	move.b %d1, 7936(%a0)
	move.b %d1, 7808(%a0)
	move.b %d1, 7680(%a0)
	move.b %d1, 7552(%a0)
	move.b %d1, 7424(%a0)
	move.b %d1, 7296(%a0)
	move.b %d1, 7168(%a0)
	move.b %d1, 7040(%a0)
	move.b %d1, 6912(%a0)
	move.b %d1, 6784(%a0)
	move.b %d1, 6656(%a0)
	move.b %d1, 6528(%a0)
	move.b %d1, 6400(%a0)
	move.b %d1, 6272(%a0)
	move.b %d1, 6144(%a0)
	move.b %d1, 6016(%a0)
	move.b %d1, 5888(%a0)
	move.b %d1, 5760(%a0)
	move.b %d1, 5632(%a0)
	move.b %d1, 5504(%a0)
	move.b %d1, 5376(%a0)
	move.b %d1, 5248(%a0)
	move.b %d1, 5120(%a0)
	move.b %d1, 4992(%a0)
	move.b %d1, 4864(%a0)
	move.b %d1, 4736(%a0)
	move.b %d1, 4608(%a0)
	move.b %d1, 4480(%a0)
	move.b %d1, 4352(%a0)
	move.b %d1, 4224(%a0)
	move.b %d1, 4096(%a0)
	move.b %d1, 3968(%a0)
	move.b %d1, 3840(%a0)
	move.b %d1, 3712(%a0)
	move.b %d1, 3584(%a0)
	move.b %d1, 3456(%a0)
	move.b %d1, 3328(%a0)
	move.b %d1, 3200(%a0)
	move.b %d1, 3072(%a0)
	move.b %d1, 2944(%a0)
	move.b %d1, 2816(%a0)
	move.b %d1, 2688(%a0)
	move.b %d1, 2560(%a0)
	move.b %d1, 2432(%a0)
	move.b %d1, 2304(%a0)
	move.b %d1, 2176(%a0)
	move.b %d1, 2048(%a0)
	move.b %d1, 1920(%a0)
	move.b %d1, 1792(%a0)
	move.b %d1, 1664(%a0)
	move.b %d1, 1536(%a0)
	move.b %d1, 1408(%a0)
	move.b %d1, 1280(%a0)
	move.b %d1, 1152(%a0)
	move.b %d1, 1024(%a0)
	move.b %d1, 896(%a0)
	move.b %d1, 768(%a0)
	move.b %d1, 640(%a0)
	move.b %d1, 512(%a0)
	move.b %d1, 384(%a0)
	move.b %d1, 256(%a0)
	move.b %d1, 128(%a0)
draw_table_slot_0:	
	move.b %d1, 0(%a0)
	rts

