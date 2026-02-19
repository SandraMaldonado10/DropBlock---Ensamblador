;*************************************************************************************                                                                                                                        
;********************** equivalencias minimas del proyecto ******************************* 
;*****************************  NO MODIFICAR  ****************************************                                                                                                                       
;*************************************************************************************                                                                                                                        


 ; EQUIVALENCIAS USADAS PARA LA ESTRUCTURA DE MATRIZ
 MAXFILSJUEGO   EQU 5  ;1-8
 MAXCOLSJUEGO   EQU 6  ;1-8
 MAXCELDASJUEGO EQU MAXFILSJUEGO*MAXCOLSJUEGO 

 ; EQUIVALENCIAS DE COORDENADAS PARA PINTAR EN PANTALLA (FIL, COL)  
 FILINICIOTAB   EQU 1  ; posicion contenido 1ra celda del tablero
 COLINICIOTAB   EQU 2   

 FILINTROVALORG EQU 8 ; posicion introducir cadena DBG
 COLINTROVALORG EQU 68 
 
 FILNUEVOBLOQUE EQU 16 ; posicion valor bloque aleatorio siguiente
 COLNUEVOBLOQUE EQU 63
 
 FILINTROCOL    EQU 18 ; posicion introducir columna donde posicionar nuevo bloque
 COLINTROCOL    EQU 59

 FILMSJGNRAL    EQU 23 ; posicion msjs ganar, perder y salir 
 COLMSJGNRAL    EQU 55    
 