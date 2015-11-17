	.syntax unified
	.text
	.align 2
	.thumb
	.thumb_func

	.global fibonacci
	.type fibonacci, function
 
@Optimization with thumb2 IT & reduce one register
fibonacci:
        @ ADD/MODIFY CODE BELOW
        @ PROLOG
        push {r3, r4, lr}
        
        
        @mov r3,r0 and subs r3, #1 can be combined to subs r3, r0, #1 
        mov r3, r0
        subs r3, #1
        it le
        pople {r3, r4, pc}      
       

	mov r0, r3
        bl fibonacci
                
        mov r4, r0
        sub r0, r3, #1 
        bl fibonacci 

        add r0, r0, r4

        pop {r3, r4, pc}                @EPILOG

        @ END CODE MODIFICATION
        .size fibonacci, .-fibonacci
        .end

