;*************************************************************************************                                                                                                                        
;********************** variables minimas del proyecto ******************************* 
;*****************************  NO MODIFICAR  ****************************************                                                                                                                       
;*************************************************************************************                                                                                                                        

   nuevoBloque     dw ?   ; almacena el nuevo bloque generado
   
   ;estructura que almacena el tablero de juego, se proporciona una version de debug y otra vacia 
   tableroJuegoDBG dw 0,64,0,0,256,32,  0,32,0,0,128,16,  128,64,0,0,64,8,  64,32,1024,1024,32,4,  32,128,256,512,64,2 ;contiene los datos del tablero en el momento actual

   tableroJuego    dw MAXCELDASJUEGO dup(0) ;contiene los datos del tablero en el momento actual
   
   ;la siguiente serviria para probar un tablero de debug de 8x8
   ;tableroJuegoDBG dw 1024,1024,0,0,0,0,1024,256,  256,512,0,0,0,0,256,128,  16,32,0,0,0,0,512,64,  32,64,0,0,0,0,256,32,  64,32,0,0,0,0,128,16,  128,64,0,0,0,0,64,8,  64,32,1024,1024,0,0,32,4,  32,128,256,512,1024,2,64,2 ;contiene los datos del tablero en el momento actual
   
   valorGanar      dw ?  ; valor a alcanzar para ganar, se gana si se obtiene un valor menor o igual a este
   
   fil             db ?  ; necesarias para ColocarCursor
   col             db ? 

   ;Mensajes de Interfaz                      
   cad             db 6 dup(?)  ;almacena numeros tras convertirlos a cadena , peticion de cadenas...
   cadVacia        db "    $"  ;usado para borrar el numero de una celda

   msjGanada       db "Has ganado!  ;-)$" 
   msjPerdida      db "Has perdido! ;-($"
   msjAdios        db "Hasta pronto!!! $"

   decoTablero     db " |--0-|--1-|--2-|--3-|--4-|--5-|                  ___"                      ,10,13
                   db " |    |    |    |    |    |    |                 / _ \_______  ___"         ,10,13         
                   db " |____|____|____|____|____|____|                / // / __/ _ \/ _ \"        ,10,13
                   db " |    |    |    |    |    |    |               /____/_/  \___/ .__/ __"     ,10,13
                   db " |    |    |    |    |    |    |                   / _ )/ /_/_/____/ /__"   ,10,13          
                   db " |____|____|____|____|____|____|                  / _  / / _ \/ __/  '_/"   ,10,13     
                   db " |    |    |    |    |    |    |                 /____/_/\___/\__/_/\_\"    ,10,13
                   db " |    |    |    |    |    |    |          "                                 ,10,13
                   db " |____|____|____|____|____|____|             Jugamos en modo debug?"        ,10,13    
                   db " |    |    |    |    |    |    |          "                                 ,10,13
                   db " |    |    |    |    |    |    |          "                                 ,10,13
                   db " |____|____|____|____|____|____|                 -= INSTRUCCIONES =-"       ,10,13         
                   db " |    |    |    |    |    |    |          "                                 ,10,13
                   db " |    |    |    |    |    |    |             Introduce un numero de columna",10,13
                   db " |____|____|____|____|____|____|             donde colocar el siguiente"    ,10,13           
                   db "                                             bloque con valor:   "          ,10,13
                   db "                                          "                                 ,10,13
                   db "                                          "                                 ,10,13               
                   db "                                                  Columna:"                 ,10,13
                   db "                                                  ('s' para salir)$"


  ;decoTablero      db " |--0-|--1-|--2-|--3-|--4-|--5-|--6-|--7-|        ___"                      ,10,13
 ;                  db " |    |    |    |    |    |    |    |    |       / _ \_______  ___"         ,10,13         
 ;                  db " |____|____|____|____|____|____|____|____|      / // / __/ _ \/ _ \"        ,10,13
;                   db " |    |    |    |    |    |    |    |    |     /____/_/  \___/ .__/ __"     ,10,13
;                   db " |    |    |    |    |    |    |    |    |         / _ )/ /_/_/____/ /__"   ,10,13          
;                   db " |____|____|____|____|____|____|____|____|        / _  / / _ \/ __/  '_/"   ,10,13     
;                   db " |    |    |    |    |    |    |    |    |       /____/_/\___/\__/_/\_\"    ,10,13
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |____|____|____|____|____|____|____|____|   Jugamos en modo debug?"        ,10,13    
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |____|____|____|____|____|____|____|____|       -= INSTRUCCIONES =-"       ,10,13         
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |    |    |    |    |    |    |    |    |   Introduce un numero de columna",10,13
;                   db " |____|____|____|____|____|____|____|____|   donde colocar el siguiente"    ,10,13           
;                   db " |    |    |    |    |    |    |    |    |   bloque con valor:   "          ,10,13
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |____|____|____|____|____|____|____|____|"                                 ,10,13               
;                   db " |    |    |    |    |    |    |    |    |        Columna:"                 ,10,13
;                   db " |    |    |    |    |    |    |    |    |        ('s' para salir)"         ,10,13
;                   db " |____|____|____|____|____|____|____|____|"                                 ,10,13
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |    |    |    |    |    |    |    |    |"                                 ,10,13
;                   db " |____|____|____|____|____|____|____|____|$"
