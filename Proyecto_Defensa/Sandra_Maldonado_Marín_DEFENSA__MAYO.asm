include "EQUS.inc"  

data segment 
    ; AQUI SE PONEN NUEVAS VARIABLES
    ; cad db 6 dup(?)
    MaxColapsos dw ?   
        
  include "VARs.inc"
data ends

stack segment
  dw 128 dup(0)
ends

code segment
  include "PROCS_std.inc"  
  include "PROCS_clase.inc"

;*************************************************************************************                                                                                                                        
;*************************     procedimientos de IU    *******************************
;*************************************************************************************  


  
  ;F: Pinta la pantalla de juego, y pide una cadena de 3 caracteres. La cadena puede ser "DBG" o no.
  ;   Solo si se introduce "DBG" se invoca a PintaTablero 
  ;S: SI: apuntador a TableroJuego (si es un dato numerico) o a TableroJuegoDBG (si es la cadena "DBG")
  ;S: VALORGANAR: contiene el valor numerico introducido por el usuario(si es mayor que 0)
  PintaEntorno PROC 
    
    push dx
    push ax
    
    
    lea dx, decoTablero
    call ImprimirCadena
        
    mov fil, FILINTROVALORG
    mov col, COLINTROVALORG
        
        call ColocarCursor
        lea dx, CadVacia  
        call ImprimirCadena
        call ColocarCursor
        
        lea dx, cad
        mov cad[0], 4
        call LeerCadena 

        cmp cad[1], 3  ; Comprobamos si los caracteres metidos por el usuario son 3
        je comprobarDBG
        jmp imprimirTableroJuego 
        
        comprobarDBG:
        cmp cad[2], 'D' 
        jne imprimirTableroJuego
        cmp cad[3], 'B' 
        jne imprimirTableroJuego
        cmp cad[4], 'G' 
        jne imprimirTableroJuego
        
        lea si, tableroJuegoDBG
        call PintaTablero 
        mov valorGanar, 1   ; Si es modo DBG el valorGanar siempre sera 1
        ;jmp terminar
        jmp numeroColapsos
    
        imprimirTableroJuego:
              
            lea si, tableroJuego ; Si es tableroJuego en blanco, no se imprime nada
               
            ;xor ax, ax    ; LOS XOR NO SON NECESARIOS SI POSTERIORMENTE SE HACE UN ALGUN CALCULO CON ESE REGISTRO, YA QUE SE SOBREESCRIBE
            lea dx, cad[2]
            call CadenaANumero  ; Se guarda en AX el valor introducido por el usuario -> lo que hubiera en AX se elimina y se sobreescribe el nuevo valor
                        
            mov valorGanar, ax ; Pasar valor numerico de usuario a valorGanar
        
        ; DEFENSA:
        numeroColapsos:
            mov fil, FILMSJGNRAL
            mov col, COLMSJGNRAL
            call ColocarCursor 
        
            xor di, di
        
            call LeerTeclaSinEco  ; se almacena en AL
            xor ah, ah
            sub al, 48
            mov di, ax
            
            mov MaxColapsos, di 
            
        terminar:  
            
    pop ax
    pop dx
   

    ret 
  PintaEntorno ENDP  


  
  ;F: Lee un caracter hasta que correponda con un caracter para salir del juego o con un caracter 
  ;   numerico valido que se transformara a numero y se devolvera como salida en formato numero
  ;S: AH=0 si no hay que salir el juego 
  ;     AL numero leido
  ;   AH=1, si hay que salir el juego 
  ComandoEntrada PROC

    push dx
   

    IntroducirColumna:
    
        mov fil, FILINTROCOL  ; Se coloca para indicar una columna 
        mov col, COLINTROCOL
        call ColocarCursor

        xor ax, ax
        call LeerTeclaSinEco
        cmp al, 's' ; Si el usuario teclea 's', se sale del juego
        je salirJuego 
    
        ; Se sigue en el juego:
        sub al, 48  ; Operacion para convertir el caracter ascii que introduce el usuario, en numero
        
        cmp al, MAXCOLSJUEGO-1 ; Comprobar que el numero pueda ser el maximo numero de colmunas o menos
        jle comprobacion
        
        
        jmp IntroducirColumna  
    
   
    comprobacion:   ; Para comprobar que no ha introducido el usuario un valor menor de 0
        cmp al, 0
        jl salirJuego     
    
    
    seguirJuego:
        mov ah, 0 
                
        jmp finalizar
        

    salirJuego:   
        mov ah, 1  ; Porque hay que salir del juego
        
        
    finalizar:
    
 
    pop dx

    ret
  ComandoEntrada ENDP


  ;F: Realiza la insercion en el tablero de juego apuntado por SI, comprobando ademas si implica
  ;   perder, ganar o se sigue jugando.
  ;   Se compactan las celdas que presenten el mismo valor numerico, y eso hace que ese valor se 
  ;   divida entre 2 
  ;E: BL columna en la que introducir el valor
  ;E: nuevoBloque (var) valor a introducir  
  ;E: SI apunta a TableroJuego o TableroJuegoDBG 
  ;E: VALORGANAR contiene el valor numerico introducido por el usuario, y si es modo DBG es 1
  ;S: TableroJuego o TableroJuegoDBG modificados
  ;   DH=0 indica seguir jugando (no se pierde)
  ;   DH=1 indica partida ganada
  ;   DH=2 indica partida perdida
  Insertar PROC

    push ax
    push cx
    push si
    
    ; AHORA MISMO TENEMOS EN BL LA COLUMNA EN LA QUE QUEREMOS PONER EL NUMERO
    
    ; --------- Primero: COMPROBAR SI LA PRIMERA CELDA DE LA COLUMNA ESTA LLENA: ----------

    ;obtenerValorCelda:

    ;mul bl*2 y sumarlo con lo que tenia si
    mov ax, 2
    mul bl
    add si, ax

    cmp [si], word ptr 0
    jne comprobarPrimeraCelda
    
    ; ---------- Segundo: COMPROBAR SI LA ULTIMA CELDA DE LA FILA ESTA LLENA:  -----------
    
    ; Si es 0 la primera celda de la columna:
    mov cx, MAXFILSJUEGO-1
    
    ultimaCelda:
        
        add si, MAXCOLSJUEGO*2 ; Por 2 porque es tipo dw
        
    loop ultimaCelda
    
    cmp [si], word ptr 0 
    je siguePartida
    
    ; ---------- Tercero: LLEGAR A LA CELDA VACIA DE ESA COLUMNA: ------------------------
    
    subirEnColumna:                
        sub si, MAXCOLSJUEGO*2 
        cmp [si], word ptr 0
        jne subirEnColumna
  
    
    siguePartida:
        mov dh, 0  
          
        mov ax, nuevoBloque
      
        
        ; ------ Cuarto: COMPROBAR SI LA CELDA DE ABAJO TIENE EL MISMO VALOR QUE LA QUE INSERTAMOS  ------

        
        comprobarCeldasIguales:
        
             
    
            add si, MAXCOLSJUEGO*2 ; Vamos a la celda justo de abajo
            cmp [si], ax
            je compactar
        
            ; Si no son iguales el valor de las celdas
            noIguales: 
            
                 
                
                sub si, MAXCOLSJUEGO*2 ; Vuelvo a la celda de arriba  
                mov [si], ax  ;CON ESTO SE INSERTA EL NUMERO ALEATORIO EN LA CELDA QUE CORRESPONDA 
                
                  
                
                jmp terminarInsertar
        
        compactar: 
            cmp MaxColapsos, 0
            je terminanColapsos
            
            
            shr ax, 1 ; Para dividir el valor de la celda entre 2 -> 2^1 
            dec MaxColapsos
            
            
                    
            sub si, MAXCOLSJUEGO*2
            mov [si], word ptr 0 ; Esto para poner esa celda en blanco 
            add si, MAXCOLSJUEGO*2 
            
            
            
            cmp ax, valorGanar ; Comparamos para ver si es menor igual el numero colapsado que el de valorGanar
            ; Tambien se gana si es 1
            jle ganarPartida
            
            jmp comprobarCeldasIguales
        
        compactar2: ; Este compactar es para cuando detectamos que la primera celda de la columna se puede compactar
        
            shr ax, 1 ; Para dividir el valor de la celda entre 2 -> 2^1
            dec MaxColapsos
            
            jmp comprobarCeldasIguales
            
        comprobarPrimeraCelda: ; Esta comprobacion es cuando la primera celda de la columna que hemos seleccionado, esta llena
            
            mov dh, 0  
            mov ax, nuevoBloque
            cmp [si], ax
            je compactar2  
             
    terminanColapsos:
        
        sub si, MAXCOLSJUEGO*2
        mov [si], word ptr 0
        add si, MAXCOLSJUEGO*2
        mov [si], ax
        jmp terminarInsertar    
            
      
    pierdePartida:
        mov dh, 2  ; Indica que pierde la partida
        jmp terminarInsertar
        
    ganarPartida:
        mov dh, 1
        mov [si], ax ; Para imprimir el valor colapsado menor o igual que valorGanar

    terminarInsertar:
    
    pop si
    pop cx
    pop ax
    
    ret
  Insertar ENDP
  


;************************ PROGRAMA PRINCIPAL ***************
principal:
    mov ax, data
    mov ds, ax         

    
    call PintaEntorno
    
    ;  PARA GENERAR EL NUMERO ALEATORIO:
    generarNumeroAleatorio: 
    
        call GeneraYPintaValorAleatorio

    
        call ComandoEntrada
    
        cmp ah, 1
        je salir     
  
        cmp ah, 0
        je seguirPartida
       
        seguirPartida:    
        
        mov bl, al
        call Insertar
        
        
        
            cmp dh, 1
            je ganar
        
            cmp dh, 2
            je perder
        
            ;si DH=0 se pinta la columna 
            
            
          
        call PintaColumna
        
        cmp MaxColapsos, 0  ; Si el numero de colapsos esta en 0 se pierde la partida
        je perder
    
    jmp generarNumeroAleatorio
    
    salir:
    
        mov fil, FILMSJGNRAL
        mov col, COLMSJGNRAL
        call ColocarCursor
        
        lea dx, msjAdios
        call ImprimirCadena
        
        jmp finPartida
    
    ganar: 
    
        call PintaColumna
        
        mov fil, FILMSJGNRAL
        mov col, COLMSJGNRAL
        call ColocarCursor
        
        lea dx, msjGanada
        call ImprimirCadena
        jmp finPartida  
    
    perder:  
    
        mov fil, FILMSJGNRAL
        mov col, COLMSJGNRAL
        call ColocarCursor
        
        lea dx, msjPerdida
        call ImprimirCadena    
    
    finPartida:      
	
    mov ah, 4ch
    int 21h        
 ends 
end principal   
     