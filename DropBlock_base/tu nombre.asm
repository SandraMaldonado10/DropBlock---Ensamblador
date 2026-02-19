include "EQUS.inc"  

data segment        
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
  PintaEntorno PROC 
    


    ret 
  PintaEntorno ENDP  


  
  ;F: Lee un caracter hasta que correponda con un caracter para salir del juego o con un caracter 
  ;   numerico valido que se transformara a numero y se devolvera como salida en formato numero
  ;S: AH=0 si no hay que salir el juego 
  ;     AL numero leido
  ;   AH=1, si hay que salir el juego 
  ComandoEntrada proc



    ret
  ComandoEntrada endp



  ;F: Realiza la insercion en el tablero de juego apuntado por SI, comprobando ademas si implica
  ;   perder, ganar o se sigue jugando. Esta semana implementaremos una primera version que 
  ;   no es completa y terminaremos en la proxima sesion
  ;E: BL columna en la que introducir el valor
  ;E: nuevoBloque (var) valor a introducir  
  ;E: SI apunta a TableroJuego o TableroJuegoDBG
  ;S: TableroJuego o TableroJuegoDBG modificados
  ;   DH=0 indica seguir jugando (no se pierde)
  ;   DH=2 indica partida perdida
  InsertarAlpha PROC



    ret
  InsertarAlpha ENDP



;************************ PROGRAMA PRINCIPAL ***************
principal:
    mov ax, data
    mov ds, ax         

          
	
    mov ah, 4ch
    int 21h        
 ends 
end principal   
     