;CBLOCK
;    m
;    n
;    o
;ENDC
    
;ESTA RUTINA CONTIENE RETARDOS PARA USO GENERAL
    
RET2.56s:                ;RETARDO DE 2.56s
    movlw   .0
    goto    start
RET2s:                ;RETARDO DE 2.0s
    movlw   .200
    goto    start
RET1s:                ;RETARDO DE 1s
    movlw   .100
    goto    start
RET500ms:                ;RETARDO DE 500ms
    movlw   .50
    goto    start
RET400ms:                ;RETARDO DE 400ms
    movlw   .40
    goto    start
RET300ms:		  ;RETARDO DE 300ms
    movlw   .30
    goto    start
RET200ms:		    ;RETARDO DE 200ms
    movlw   .20
    goto    start
RET100ms:                ;RETARDO DE 100ms
    movlw   .10
    goto    start
RET90ms:                ;RETARDO DE 90ms
    movlw   .9
    goto    start
RET80ms:                ;RETARDO DE 80ms
    movlw   .8
    goto    start
RET70ms:                ;RETARDO DE 70ms
    movlw   .7
    goto    start
RET60ms:                ;RETARDO DE 60ms
    movlw   .6
    goto    start
RET50ms:                ;RETARDO DE 50ms
    movlw   .5
    goto    start
RET40ms:                ;RETARDO DE 40ms
    movlw   .4
    goto    start
RET30ms:                ;RETARDO DE 30ms
    movlw   .3
    goto    start
RET20ms:                ;RETARDO DE 20ms
    movlw   .2
    goto    start
RET10ms:                ;RETARDO DE 10ms
    movlw   .1
    goto    start
start:
    movwf   m
    movlw   .29
    movwf   n
    movlw   .228
    movwf   o
    decfsz  o,1
        goto    $-1
    nop
    decfsz  n,1
        goto    $-6
    nop
    decfsz  m,1
        goto    $-.11
    nop
return
    
    
    RET9ms:                ;RETARDO DE 9ms
    movlw   .9
    goto    start_1ms
    RET8ms:                ;RETARDO DE 8ms
    movlw   .8
    goto    start_1ms
    RET7ms:                ;RETARDO DE 8ms
    movlw   .7
    goto    start_1ms
    RET6ms:                ;RETARDO DE 6ms
    movlw   .6
    goto    start_1ms
    RET5ms:                ;RETARDO DE 5ms
    movlw   .5
    goto    start_1ms
    RET4ms:                ;RETARDO DE 4ms
    movlw   .4
    goto    start_1ms
    RET3ms:                ;RETARDO DE 3ms
    movlw   .3
    goto    start_1ms
    RET2ms:                ;RETARDO DE 2ms
    movlw   .2
    goto    start_1ms
    RET1ms:                ;RETARDO DE 1ms
    movlw   .1
    goto    start_1ms
    start_1ms:
    movwf   m
    movlw   .10
    movwf   n
    movlw   .65
    movwf   o
    decfsz  o,1
        goto    $-1
    nop
    decfsz  n,1
        goto    $-6
    nop
    decfsz  m,1
        goto    $-.11
    nop
return
    
    RET5s:                ;RETARDO ESPECIALIZADO DE 5s
    movlw   .100
    movwf   m
    movlw   .210
    movwf   n
    movlw   .157
    movwf   o
    decfsz  o,1
        goto    $-1
    nop
    decfsz  n,1
        goto    $-6
    nop
    decfsz  m,1
        goto    $-.11
    nop
return