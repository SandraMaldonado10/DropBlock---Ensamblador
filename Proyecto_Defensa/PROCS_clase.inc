;*************************************************************************************                                                                                                                        
;****************** procedimientos implementados en clase **************************** 
;***************************  NO MODIFICAR  ******************************************                                                                                                                       
;************************************************************************************* 


                                                                                                                      
;*************************************************************************************                                                                                                                        
;*************************     procedimientos de IU    *******************************
;*************************************************************************************  

  

  ;F: Pinta los valores del tablero invocando a PintaColumna para cada columna del tablero de juego
  ;E: SI debe apuntar al tablero de juego a imprimir
  ;   (pese a que no se usa de manera directa, se invoca a PintaColumna que lo requiere) 
  PintaTablero PROC
    push bx
    push cx 
      
    mov cx, MAXCOLSJUEGO 
    
    xor bx, bx
   sigueCol:
    call PintaColumna
    
    inc bx        ;cambia a la siguiente columna
    loop sigueCol
   
    pop cx
    pop bx
    ret
  PintaTablero ENDP

 
 
  ;F: Pinta los valores de una determinada columna del tablero apuntado por SI
  ; en su posicion correcta en pantalla
  ;E: BL columna que pintar 
  ;E: SI apunta a TableroJuego o a TableroJuegoDBG
  PintaColumna PROC 
    push ax
    push bx
    push cx
    push dx
    push si
      
    mov fil, FILINICIOTAB ;primera fila de la pantalla de juego
    mov cx, MAXFILSJUEGO

    mov col, COLINICIOTAB ; primera columna de la pantalla de juego 
    mov al, 5
    mul bl
    add col, al 
    
    xor bh, bh
    shl bx, 1
    add si, bx
   
   sigueFil:
    call ColocarCursor 
        
    lea dx, CadVacia
    call ImprimirCadena
    call ColocarCursor 

    mov ax, [si]    ;si el valor es 0, no imprimirlo
    cmp ax, 0
    je siguecelda 
       
    lea dx, cad
    call NumeroACadena
    call ImprimirCadena
      
   siguecelda:
    add si, MAXCOLSJUEGO*2
    add fil, 3    ; cambia a la fila siguiente
  
    loop sigueFil
        
    pop si
    pop dx
    pop cx
    pop bx
    pop ax 
    ret
  PintaColumna ENDP 



  ;F: Invoca al modulo de GenerarValorAleatorio e imprime el valor en el lugar correspondiente borrando
  ;   el valor previo impreso que pudiera haber
  ;S: nuevoBloque (var) almacenara el valor del bloque generado
  GeneraYPintaValorAleatorio PROC 
    push ax ;ya que GeneraValorAleatorioPot2 modifica AX
    push dx
    
    ;Borrar el bloque previo
    mov fil,FILNUEVOBLOQUE
    mov col,COLNUEVOBLOQUE
    call colocarcursor 
    
    lea dx,cadVacia 
    call imprimirCadena
    
   
    ;Generar Aleatorio y convertirlo a cadena 
    call GeneraValorAleatorioPot2 
    mov nuevoBloque, ax
    
    lea dx, cad
    call NumeroACadena ;ax

    
    ;Imprimir el bloque nuevo
    ;mov fil,FILNUEVOBLOQUE  ;Esta instruccion no es necesaria, fil no ha cambiado de valor
    ;mov col,COLNUEVOBLOQUE  ;Esta instruccion no es necesaria, col no ha cambiado de valor
    call colocarcursor  
    
    lea dx, cad     ;Esta instruccion no es necesaria, DX no ha cambiado de valor
    call imprimirCadena
    
    pop dx 
    pop ax
    ret
  GeneraYPintaValorAleatorio ENDP


  
;*************************************************************************************                                                                                                                        
; *********************    procedimientos funcionalidad    ****************************
;*************************************************************************************    

  ;F: Genera un valor aleatorio potencia de 2 entre 2^1 y 2^10                          
  ;S: AX contiene el valor aleatorio
  GeneraValorAleatorioPot2 PROC
    push bx
    push cx
    
   genAleat:
    mov bl, 10 ;genera un aleatorio entre 0 y 9
    call NumAleatorio
    inc ah     ;se ajusta el resultado para que este entre 1 y 10 incl

    mov cl, ah ;calculo 2^aleat
    mov ax, 1
    shl ax, cl
    
    pop cx
    pop bx
    ret
  GeneraValorAleatorioPot2 ENDP
  

  
