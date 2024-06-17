Traducción de la librería funcional en ruso

#include <iarduino_ADC_CS1237.h>                                               // Agegamos la librería para el integrado CS1237.
iarduino_ADC_CS1237 adc(13,19);                                                // Declara un objeto para trabajar con iarduino_ADC_CS1237, especificando los pines ( SCLK , DATA ). Puedes inicial cualquier terminal Arduino.
                                                                               // Todas las funciones de la biblioteca son opcionales (excepto iniciar), si los valores predeterminados son convenientes.
void setup(){                                                                  //
     bool i;                                                                   //
     Serial.begin(9600);         while( !Serial );                             // Lineas largas. La función se llama antes de la inicialización begin().
     i=adc.begin();              if( !i ){ Serial.println("Error begin"  ); } // Se inicia el integrado
     i=adc.setPinVrefOut(true);  if( !i ){ Serial.println("Error VrefOut"); } // Activa la salida VrefOut. Posibles valores: true= Activado (predeterminado), falso= apagado. На включённом выходе VrefOut появится сглаженное напряжение питания чипа (Vcc), которое можно подать на вход VrefIn.
     i=adc.setVrefIn(5.0);       if( !i ){ Serial.println("Error VrefIn" ); } // Especifica el voltaje de referencia VrefIn. Predeterminado 5V. Вход VrefIn может по
//   Configurar el ADC                                          //
     i=adc.setPulseWidth(30);    if( !i ){ Serial.println("Error width"  ); } // Especifica el ancho de pulso por la línea SCL. По умолчанию 5мкс. Увеличение требуется только длялучать либо внешнее напряжение от 1.5 до Vcc+0.1, либо напряжение питания чита (Vcc) с выхода VrefOut.
     i=adc.setSpeed(10);         if( !i ){ Serial.println("Error speed"  ); } // Especigica la fercuencia de conversióna 10Hz. Posibles valores: 10, 40, 640, 1280 Hz. Это частота готовности новых данных для чтения. По умолчанию 10 Гц.
     i=adc.setPGA(1);            if( !i ){ Serial.println("Error gain"   ); } // Especifica la ganancia: 1, 2, 64, 128. Prio default 128. Los voltajes medidos están en el rango ±0.5 VrefIn / PGA.
     i=adc.setChannel(1);        if( !i ){ Serial.println("Error channel"); } // Especifica el canal. Canales disponibles: 0, 2, 3. 0 es canal А (Predeterminado), 1-Reserva, 2-Temperatura, 3-Corto circuito interno.
//   Leyendo la configuración del ADC:                                                     //
     bool     pin   = adc.getPinVrefOut();                                     // Obtienen el estado de salida VrefOut. Verdadero = habilitado.
     uint16_t speed = adc.getSpeed();                                          // Obtiene la ganacia actual. La función devuelve la frecuencia de disponibilidad: 10, 40, 640, или 1280 Гц.
     uint8_t  gain  = adc.getPGA();                                            // Obtiene la ganancia actual. La funciómn devuelve los valores: 1, 2, 64, o 128.
     uint8_t  chan  = adc.getChannel();                                        // Obtiene el canal ADC usado: 0, 2, или 3.
     uint16_t width = adc.getPulseWidth();                                     // Obtiene el anchode pulso en us.  La función devuelve la duración de los pulsos y pausas en la línea SCL en us usado por la biblioteca
     float    Vref  = adc.getVrefIn();                                         // Obtiene voltaje de referencia VrefIn usado para calcular el voltaje devuelto por la función getVoltage().
//   Desplegar configuración del ADC                                        //
     Serial.println( (String) "Salida VrefOut "+(pin?" vk ":"abierto")+"abierto."    ); //
     Serial.println( (String) "Velocidad de actualización de datos "+speed+" Hz."    ); //
     Serial.println( (String) "Ganancia "+gain+"х."             ); //
     Serial.println( (String) "Usando "+chan+" Canal CAD."            ); //
     Serial.println( (String) "Anchode pulso en línea SCL "+width+" us."); //
     Serial.println( (String) "Tensión de referencia VrefIn "+Vref+" V."       ); //
}                                                                              //
                                                                               //
void loop(){                                                                   //
//   Mostrar los valores ADC y el voltaje                             //
     int32_t i=adc.analogRead(); Serial.print("ADC="); Serial.print(i);        //   Leemos y mostramos el valor con digno del ADC de 0 a + 8388607
     float   j=adc.getVoltage(); Serial.print(", V="); Serial.print(j,5);      //   Recibimos y emitimos el voltaje en la entrada del ADC de 0 a ±0,5 VrefIn. Vin = ADC*VrefIn/(2^24-1)/PGA.
     Serial.println("V."); delay(1000);                                        //
}                                                                              //
