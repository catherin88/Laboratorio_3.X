;ESTA RUTINA ES UNA DE LAS MÁS IMPORTANTES DE TODO EL PROGRAMA, PORQUE ES LA QUE LLAMA LAS SUBRUTINAS DE INTERFACES 
;GRAFICAS, ADEMÁS SE ENCARGA DE DETERMINAR QUE TIPO DE INTRUCCIONES Y COMANDOS SE LE ESTAN INGRESANDO.
;EN PRIMERA INSTANCIA SE DETERMINA QUE TIPO DE DATO SE HA INGRESADO (TAG_1, TAG_2, TAG_3) Y SE COLOCA SU 
;RESPECTIVA INTERFAZ GRAFICA CORRESPONDIENTE, AL INICIO DE CADA INTRUCCIÓN, EXCEPTO CUANDO HAY 
;UN ERROR (DEFAULT) SE PREGUNTA  LA CONTRASEÑA (ING_CONTR_TAG_1, ING_CONTR_TAG_2, ING_CONTR_TAG_3), LUEGO
; SE PROSIGUE EN LA CORRESPONDIENTE INTERFAZ GRAFICA DE LA INTRUCCIÓN Y SE ESPERAN LOS COMANDOS O CARACTERES 
;CORRESPONDIENTES(EN CASO DE 2 NO SE OCUPA) Y SE PROSIGUE CON LA EJECUCIÓN DE LA INSTRUCCIÓN HASTA ACABAR EN 
;END_TAG_1, END_TAG_2, END_TAG_3. CABE ACLARAR QUE EN CADA UNA SE EVALUA EL NÚMERO DE VECES QUE SE HA INGRESADO
;LA CONTRASEÑA Y SI ES IGUAL A 4 SE BLOQUEA
MENU_BANCO:
    BTFSS	FLAG_ISR,1
	GOTO	DEFAULT
    TAG_1:
    MOVLW	0X01	    ;EVALIACIÓN DEL TIPO DE INSTRUCCIÓN
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	TAG_2 
    CLRF	FLAG_ISR    ;SE LIMPIA PARA INDICAR QUE SE ATENDIO LA INTERRUPCIÓN
    ING_CONTR_TAG_1:	    ;INTERFAZ GRAFICA Y EVALUACIÓN DE EJECUCIÓN DE COMANDOS
    CLRF	CONT_CONTRASENA
    CALL	INGRESO_CONTRASENA
    BTFSS	FLAG_ISR,2
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    BTFSS	FLAG_ISR,4
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    BTFSS	FLAG,0
	GOTO	TAG_1_1
    BCF		FLAG,0
    CALL	M_CONTRASENA_INCORR
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    INCF	INTENTOS,1
    MOVLW	.4
    XORWF	INTENTOS,0
    BTFSS	STATUS,Z
	GOTO	ING_CONTR_TAG_1
    CALL	M_BLOQUEO_BLOQUEO
    CLRF	J
    CALL	RET2s
    INCF	J,1
    MOVLW	.5	    ;30*2 = 60s
    XORWF	J,0
    BTFSS	STATUS,Z
	GOTO	$-5	
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    
    TAG_1_1:
    CALL	M_RETIRO
    MOVLW	.150
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    MOVLW	.100
    MOVWF	LIM_ESP
    INI_DESPLAZAMIENTO_BANCO:
    BTFSS	FLAG_ISR,0
	GOTO	DESPLAZAMIENTO_BANCO
    BCF		FLAG_ISR,0
    BTFSS	FLAG_ISR,1
	GOTO	CMD
	
    MOVLW	.1
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	$+8
    MOVLW	.5
    MOVWF	0X30
    MOVLW	.0
    MOVWF	0X2F
    MOVLW	.0
    MOVWF	0X2E
    GOTO	RET_VAL
    
    MOVLW	.2
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	$+8
    MOVLW	.0
    MOVWF	0X30
    MOVLW	.1
    MOVWF	0X2F
    MOVLW	.0
    MOVWF	0X2E
    GOTO	RET_VAL
    
    MOVLW	.3
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	$+8
    MOVLW	.5
    MOVWF	0X30
    MOVLW	.1
    MOVWF	0X2F
    MOVLW	.0
    MOVWF	0X2E
    GOTO	RET_VAL
    
    MOVLW	.4
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	$+8
    MOVLW	.0
    MOVWF	0X30
    MOVLW	.2
    MOVWF	0X2F
    MOVLW	.0
    MOVWF	0X2E
    GOTO	RET_VAL	
    
    ERRORES:
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CALL	M_ERROR
    MOVLW	.150
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    GOTO	TAG_1_1
    
    CMD:
    BTFSS	FLAG_ISR,2
	GOTO	$+3
    BCF		FLAG_ISR,2
    GOTO	END_TAG_1
    BTFSS	FLAG_ISR,4
	GOTO	$+6
    BCF		FLAG_ISR,4
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
	GOTO	ERRORES
	
    RET_VAL:
    CALL	RETIRO
    BTFSS	FLAG,1
	GOTO	RET_POSIBLE
    BCF		FLAG,1
    CALL	M_INSUFICIENTE
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    GOTO	END_TAG_1
    RET_POSIBLE:
    CALL	M_SATISFACTORIO
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    CALL	M_PREFERIDO
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    
    GOTO	END_TAG_1
    DESPLAZAMIENTO_BANCO:
    CALL	SHIFT_SCREEN_D
    CALL	ESPERA_Xms
    GOTO	INI_DESPLAZAMIENTO_BANCO
    
    END_TAG_1:
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    
    ;-------------------------------------------------------------------------------------------------------------
    TAG_2:
    MOVLW	0X02
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	TAG_3
    CLRF	FLAG_ISR
    ING_CONTR_TAG_2:
    CLRF	CONT_CONTRASENA
    CALL	INGRESO_CONTRASENA
    BTFSS	FLAG_ISR,2
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    BTFSS	FLAG_ISR,4
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    BTFSS	FLAG,0
	GOTO	TAG_2_1
    BCF		FLAG,0
    CALL	M_CONTRASENA_INCORR
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    INCF	INTENTOS,1
    MOVLW	.4
    XORWF	INTENTOS,0
    BTFSS	STATUS,Z
	GOTO	ING_CONTR_TAG_2
    CALL	M_BLOQUEO_BLOQUEO
    CLRF	J
    CALL	RET2s
    INCF	J,1
    MOVLW	.5	    ;30*2 = 60s
    XORWF	J,0
    BTFSS	STATUS,Z
	GOTO	$-5	
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    TAG_2_1:
    CLRF	INTENTOS
    CALL	M_SALDO
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    
    ;--------------------------------------------------------------------------------------------------------
    TAG_3:
    MOVLW	0X03
    XORWF	0X23,0
    BTFSS	STATUS,Z
	GOTO	DEFAULT
	
    CLRF	FLAG_ISR
    ING_CONTR_TAG_3:
    CLRF	CONT_CONTRASENA
    CALL	INGRESO_CONTRASENA
    BTFSS	FLAG_ISR,2
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    BTFSS	FLAG_ISR,4
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    BTFSS	FLAG,0
	GOTO	TAG_3_1
    BCF		FLAG,0
    CALL	M_CONTRASENA_INCORR
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    INCF	INTENTOS,1
    MOVLW	.4
    XORWF	INTENTOS,0
    BTFSS	STATUS,Z
	GOTO	ING_CONTR_TAG_3
    CALL	M_BLOQUEO_BLOQUEO
    CLRF	J
    CALL	RET2s
    INCF	J,1
    MOVLW	.5	    ;30*2 = 60s
    XORWF	J,0
    BTFSS	STATUS,Z
	GOTO	$-5	
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    
    TAG_3_1:
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    CALL	M_NUEVA_CONTR	
    CLRF	FLAG_ISR
    HAB_BANCO:
    BTFSS	FLAG_ISR,0
	GOTO	$-1
    BCF		FLAG_ISR,0
    SET_INSTRUCT_BANCO:
    BTFSS	FLAG_ISR,3
	GOTO	ATRAS_BANCO
    BCF		FLAG_ISR,3
    CALL	ENTER_CMD_BANCO		
    BTFSS	FLAG,2			
	 GOTO	CAM_CONTR_INV
    BCF		FLAG,2
    MOVF	0X23,0
    MOVWF	0X2D
    MOVF	0X22,0
    MOVWF	0X2C
    MOVF	0X21,0
    MOVWF	0X2B
    MOVF	0X20,0
    MOVWF	0X2A
    CALL	M_CAMB_CONTR
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    CALL	END_TAG_3
    CAM_CONTR_INV:
    CALL	M_CAMB_CONTR_ERR
    MOVLW	.250
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	TAG_3_1
    
    ATRAS_BANCO:
    BTFSS	FLAG_ISR,2
	GOTO	$+3
    BCF		FLAG_ISR,2
    GOTO	END_TAG_3
    BTFSS	FLAG_ISR,4
	GOTO	$+5
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	REINICIO_PROG
    BTFSS	FLAG_ISR,5
	GOTO	DATO_ING_BANCO
    BCF		FLAG_ISR,5
    CALL	CURSOR_I
    MOVLW	" "
    CALL	LCD_DATO
    CALL	CURSOR_I
    GOTO	HAB_BANCO
    DATO_ING_BANCO:
    BTFSS	FLAG_ISR,1
	GOTO    HAB_BANCO
    BCF		FLAG_ISR,1
    MOVLW	"*"
    CALL	LCD_DATO
    GOTO	HAB_BANCO
    
    END_TAG_3:
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CLRF	INTENTOS
    GOTO	MS
    
    
;-----------------------------------------------------------------------------------------------------------------
    DEFAULT:
    CLRF	FLAG_ISR
    CLRF	CONT_CONTRASENA
    CALL	M_ERROR
    MOVLW	.150
    MOVWF	LIM_ESP
    CALL	ESPERA_Xms
    CALL	ESPERA_Xms
    GOTO	MS
;----------------------------------------------------------------------------------------------------------------                                                    

    ;RUTINA ENCARGADA DE HACER LA INTERFAZ GRAFICA DE LA LCD, ADEMAS QUE SE ENCARGA DE TOMAR DECICIONES COMO
    ;RETROCEDER, IR AL INICIO, BORRAR CARACTER, INGRESAR CARACTER Y LA ACCIÓN DE ENTER (COMPARAR LOS DATOS INGRESADOS
    ;CON LOS GUARDADOS)
    INGRESO_CONTRASENA:
    CALL	M_INGRESE_CONTR		;cargar mensaje en LCD
    CALL	ENTER
    HAB:
    BTFSS	FLAG_ISR,0
	GOTO	$-1
    BCF		FLAG_ISR,0
    SET_INSTRUCT:
    BTFSS	FLAG_ISR,3
	GOTO	ATRAS
    CALL	ENTER_CMD
    GOTO	FIN_INGRESO_CONTRASENA
    ATRAS:
    BTFSC	FLAG_ISR,2
	GOTO	FIN_INGRESO_CONTRASENA
    BTFSC	FLAG_ISR,4
	GOTO	FIN_INGRESO_CONTRASENA
    BTFSS	FLAG_ISR,5
	GOTO	DATO_ING
    BCF		FLAG_ISR,5
    CALL	CURSOR_I
    MOVLW	" "
    CALL	LCD_DATO
    CALL	CURSOR_I
    GOTO	HAB
    DATO_ING:
    BTFSS	FLAG_ISR,1
	GOTO    HAB
    BCF		FLAG_ISR,1
    MOVLW	"*"
    CALL	LCD_DATO
    GOTO	HAB
FIN_INGRESO_CONTRASENA:
    RETURN
	
    
    ;RUTINA QUE SE ENCARGA DE COMPARAR LOS DATOS INGRESADOS COMO CARACTERES DE LA CONTRASEÑA
    ; Y RETORNA UNA BANDERA QUE INDICA SI SON IGUALES O NO  FLAG,0
ENTER_CMD:
    MOVLW	0X04
    XORWF	CONT_CONTRASENA,0
    BTFSC	STATUS,Z
	GOTO	$+3
    BSF		FLAG,0
    RETURN
    BCF		FLAG,0
    MOVLW	NUMERO
    MOVWF	FSR
    INICIO_CONTR:
    MOVF	INDF,0
    MOVWF	NUMERO_TEMPORAL
    MOVLW	.10
    ADDWF	FSR,1
    MOVF	INDF,0
    XORWF	NUMERO_TEMPORAL,0
    BTFSC	STATUS,Z
	GOTO	$+3
    BSF		FLAG,0
    RETURN
    
    INCF	FSR,1
    MOVLW	.10
    SUBWF	FSR,1
    MOVLW	0X24
    XORWF	FSR,0
    BTFSS	STATUS,Z
	GOTO	INICIO_CONTR	
    BCF		FLAG_ISR,3
    CLRF	CONT_CONTRASENA
    RETURN
    
;COMPARA SI SE HAN INGRESADO 4 CARACTERES DESPUÉS DE OPRIMIR ENTER
ENTER_CMD_BANCO:
    BCF		FLAG,2
    MOVLW	0X04
    XORWF	CONT_CONTRASENA,0
    BTFSC	STATUS,Z
	BSF	FLAG,2
    RETURN
;------------------------------------------------------------------------------------------------------------------
    ;ESPERA VARIABLE CON SALIDA POR UNA INTERRUPCIÓN VALIDA EN TECLADO
ESPERA_Xms:
   CLRF		I
   TEMP:
   CALL		RET10ms
   BTFSC	FLAG_ISR,0		;CAMBIO EN TECLADO
	RETURN
   INCF		I,1
   MOVF		LIM_ESP,0
   XORWF	I,0
   BTFSS	STATUS,Z
	GOTO	TEMP
RETURN

;-----------------------------------------------------------------------------------------------------------------
;PARA ESTA RUTINA SE UTILIZA UNA FORMA DE RESTAR SIMILAR A LA DE LOS NÚMERO DECIMALES
; SE RESTAN LA UNIDADES Y SI ESL RESULTADO ES NEGATIVO SE SUMA UN DIEZ PERO SE RESTA UN 1 EL
;EL VALOR DE DECENAS. LUEGO CON EL RESULTADO EN DECENAS, SE RESTAN LAS DECENAS Y SE EVALUA NUEVAMENTE SI ES NEGATIVO
;SI LO ES ENTONCES SE SIMA 10 Y SE RESTA UNO A LAS CENTENAS Y FINALMENTE, SE RESTA EL VALOR OBTENIDO EN CENTENAS
; Y SI EL RESULTADO ES NEGATIVO, NO ES POSIBLE HACER LA RESTA, PERO SI NO LO ES SE ASIGNA EL VALOR OBTENIDO 
; A SALDO
RETIRO:
    MOVF	0X26,0
    MOVWF	0X33
    MOVF	0X25,0
    MOVWF	0X32
    MOVF	0X24,0
    MOVWF	0X31
    
    CLRF	0X27
    CLRF	0X28
    CLRF	0X29
    BCF		FLAG,1
    
    MOVF    	0X30,0
    SUBWF	0X33,0
    MOVWF	0X29
    BTFSC	STATUS,C
	GOTO	$+4
    MOVLW	.10
    ADDWF	0X29,1
    DECF	0X32,1
    
    MOVF    	0X2F,0
    SUBWF	0X32,0
    MOVWF	0X28
    BTFSS	0X28,7
	GOTO	$+4
    MOVLW	.10
    ADDWF	0X28,1
    DECF	0X31,1
    
    MOVF    	0X2E,0
    SUBWF	0X31,0
    MOVWF	0X27
    BTFSS	0X27,7
	GOTO	$+3
    BSF		FLAG,1
    RETURN
    MOVF	0X29,0
    MOVWF	0X26
    MOVF	0X28,0
    MOVWF	0X25
    MOVF	0X27,0
    MOVWF	0X24
RETURN

	
    ;MENSAJE CONTRASEÑA:
M_INGRESE_CONTR:
    CALL	CLRSCR
    MOVLW	"C"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	0XEE
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	":"
    CALL	LCD_DATO
RETURN
	
    
;MENSAJE SALDO
;	 $ XXX.000
M_SALDO:
    CALL	CLRSCR
    MOVLW	"S"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	":"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	"$"
    CALL	LCD_DATO
    MOVLW	0X30
    ADDWF	0X24,0
    CALL	LCD_DATO
    MOVLW	0X30
    ADDWF	0X25,0
    CALL	LCD_DATO
    MOVLW	0X30
    ADDWF	0X26,0
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
RETURN
	
    
;MENSAJE BIENVENIDO A SU BANCO
M_BIENVENIDO:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"B"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"v"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"B"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
RETURN

;MENSAJE DEL MENÚ PRINCIPAL
;ELIJA UNA DE LAS SIGUIENTES OPCIONES:
;1.RETIRO 2.SALDO 3.CAMBIO DE CONTRASEÑA
 
M_MENU_PRINP:
    CALL	CLRSCR
    MOVLW	"E"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"j"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"g"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"p"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	":"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	"1"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"R"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"2"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"S"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"3"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"C"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"m"
    CALL	LCD_DATO
    MOVLW	"b"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO;
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	0XEE 
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
RETURN
	
;MENSAJE OPCIÓN INVALIDA
M_ERROR:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"O"
    CALL	LCD_DATO
    MOVLW	"p"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"I"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"v"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
RETURN
    
    ;MENSAJE CONTRASEÑA INCORRECTA
    M_CONTRASENA_INCORR:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"C"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	0xEE
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
RETURN
    
    ;MENSAJE CUENTA BLOQUEDA
    ;		ESPERE
    M_BLOQUEO_BLOQUEO:
    CALL	CLRSCR
    MOVLW	"C"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"b"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"q"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"E"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"p"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
RETURN
    
;MENSAJE SELECCIONE EL VALOR DEL RETIRO
;1. 5.000 2. 10.000 3. 15.000 4. 20.000
    M_RETIRO:
    CALL	CLRSCR
    MOVLW	"S"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"v"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	":"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	"1"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"5"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"2"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"1"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"3"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"1"
    CALL	LCD_DATO
    MOVLW	"5"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO;
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"4"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"2"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"."
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0"
    CALL	LCD_DATO
    MOVLW	"0" 
    CALL	LCD_DATO
RETURN
    
;MENSAJE RETIRO SATISFACTORIO
M_SATISFACTORIO:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"R"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"f"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
RETURN
    
;MENSAJE GRACIAS POR PREFERIRNOS
M_PREFERIDO:    
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"G"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"p"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"p"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"f"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
RETURN
    
;MENSAJES INSUFICIENTES
M_INSUFICIENTE:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"F"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"f"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
RETURN
    
;MENSAJE NUEVA CONTRASEÑA
M_NUEVA_CONTR:
    CALL	CLRSCR
    MOVLW	"N"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	"v"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	0XEE
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    CALL	ENTER
RETURN
    
;MENSAJE CAMBIO SU CONTRASEÑA
M_CAMB_CONTR:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"H"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"m"
    CALL	LCD_DATO
    MOVLW	"b"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"u"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"c"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    MOVLW	"n"
    CALL	LCD_DATO
    MOVLW	"t"
    CALL	LCD_DATO
    MOVLW	"r"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"s"
    CALL	LCD_DATO
    MOVLW	"e"
    CALL	LCD_DATO
    MOVLW	0XEE
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
RETURN
  
;MENSAJE DE CAMBIO FALLIDO
M_CAMB_CONTR_ERR:
    CALL	CLRSCR
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"C"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"m"
    CALL	LCD_DATO
    MOVLW	"b"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
    CALL	ENTER
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	" "
    CALL	LCD_DATO
    MOVLW	"f"
    CALL	LCD_DATO
    MOVLW	"a"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"l"
    CALL	LCD_DATO
    MOVLW	"i"
    CALL	LCD_DATO
    MOVLW	"d"
    CALL	LCD_DATO
    MOVLW	"o"
    CALL	LCD_DATO
RETURN
