;*************************************************************************************                                                                                                                        
;************************ procedimientos "estandar" ********************************** 
;*****************************  NO MODIFICAR  ****************************************                                                                                                                       
;*************************************************************************************                                                                                                                        

  ;F: Imprime una cadena terminada en $ en la posicion donde se encuentre el cursor 
  ;E: DX direccion de comienzo de la cadena a imprimir    
  ImprimirCadena proc
    push ax

    mov ah, 9
    int 21h

    pop ax
    ret
  ImprimirCadena endp 


  ;F: Lee una cadena por teclado
  ;E: DX contiene la direccion de la cadena donde se almacenar  la cadena leida                        
  ;E: la posicion 0 de esa cadena debe contener el numero maximo de caracteres a leer
  LeerCadena proc
    push ax

    mov ah, 0ah
    int 21h

    pop ax
    ret
  LeerCadena endp

 
  ;Convierte una cadena de caracteres a un numero entero 
  ;E: DX contiene la direccion de la cadena a convertir (terminada en 13 o '$')
  ;S: AX contiene el resultado de la conversion
  CadenaANumero proc
    push bx
    push cx
    push dx ; cambia con MUL de 16bits
    push si 
    push di
    
    mov si, dx
    xor ax, ax    
    mov bx, 10  
    
    cmp [si], '-'
    jne BCadNum
    
    mov di, si  ;Ajustes si viene un '-' como primer caracter
    inc si

   BCadNum:
    mov cl, [si]          ;Controles de fin
    cmp cl, 13
    je compruebaNeg
    cmp cl, '$'
    je compruebaNeg
    
    mul bx
    sub cl, '0'
    xor ch, ch
    add ax, cx
    inc si     
    jmp BCadNum
        
   compruebaNeg:   
    cmp [di], '-'
    jne finCadenaANumero
    neg ax
   
   finCadenaANumero:
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    ret
  CadenaANumero endp
 
 
  ;Convierte un numero entero a una cadena de caracteres terminada en $
  ;E: AX contiene el numero a convertir
  ;E: DX contiene la direccion de la cadena donde almacena la cadena resultado
  NumeroACadena proc 
    push ax
    push bx
    push cx
    push dx
    push di
    
    mov bx, 10
    mov di, dx
    
    xor cx, cx

    cmp ax, 0  
    jge BNumCad

    mov [di], '-'
    inc di 
    neg ax
    
   BNumCad:        ;Bucle que transforma cada digito a caracter, de menor a mayor peso     
    xor dx, dx
    div bx
    add dl, '0'
    push dx 
    inc cx
    cmp ax, 0
    jne BNumCad

   BInvertir:      ;Bucle para invertir los restos    
    pop [di]
    inc di
    loop BInvertir

    mov [di], '$'

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret
  NumeroACadena endp 

                                              
  ;F: coloca el cursor en una determinada fila y colum de pantalla
  ;E: las variables "fil" y "col" deben contener los valores de posicionamiento
  ColocarCursor proc
    push ax
    push bx
    push dx

    mov ah, 2
    mov dh, fil
    mov dl, col
    xor bh, bh
    int 10h

    pop dx
    pop bx
    pop ax
    ret         
  ColocarCursor endp                                                                                                   

  
  ;F: Lee un caracter por teclado sin eco por pantalla
  ;S: AL caracter ASCII leido
  LeerTeclaSinEco proc  
    mov ah, 8 
    int 21h
    ret  
  LeerTeclaSinEco endp    


  ;F: Lee un caracter por teclado con eco por pantalla
  ;S: AL caracter ASCII leido
  LeerTeclaConEco proc  
    mov ah, 1 
    int 21h
    ret  
  LeerTeclaConEco endp 


;  ;F: Imprime un caracter en pantalla
;  ;S: DL caracter ASCII a imprimir
;  ImprimirCaracter proc 
;    push ax 
;    mov ah, 2 
;    int 21h
;    pop ax
;    ret  
;  ImprimirCaracter endp    
                      

  ;F: Calcula un valor aleatorio entre 0 y un valor maximo-1
  ;E: BL valor maximo en el rango [1, 100]
  ;S: AH valor aleatorio calculado en el rango [0, max-1] y AL pierde su valor
  NumAleatorio proc
    push cx
    push dx

    mov ah, 2Ch ;interrupcion que recupera la hora actual del sistema operativo
    int 21h
    ;ch=horas cl=minutos dh=segundos dl=centesimas de segundo, 1/100 secs

    xor ah, ah
    mov al, dl  
    div bl 
        
    pop dx
    pop cx
    ret
  NumAleatorio endp  

 
;  ;F: Borra la pantalla (la deja en negro)
;  BorrarPantalla proc
;    push ax
;    push bx
;    push cx
;    push dx
;
;    mov ah, 6h
;    xor al, al
;    mov bh, 7
;    xor cx, cx
;    mov dh, 24
;    mov dl, 79
;    int 10h 
;
;    pop dx
;    pop cx
;    pop bx
;    pop ax
;    ret
;  BorrarPantalla endp