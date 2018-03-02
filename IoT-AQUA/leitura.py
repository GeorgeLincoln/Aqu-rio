from IoTApp import db, models
from datetime import datetime
import serial
import time
import json


if __name__ == '__main__':
    # Define a porta e o baudrate usado
    porta = '/dev/ttyACM0'
    baud_rate = 9600

    # Cria o objeto_porta e limpa o buffer da serial,
    objeto_porta = serial.Serial(porta, baud_rate)
    objeto_porta.flushInput()

    hora = datetime.now()
    temperatura = str(objeto_porta.readline()).split("'")[1].split("\\")[0]
   
    print(str(objeto_porta.readline()))

    db.session.add(models.Aquario(temperatura, str(hora.hour) + ':' + str(hora.minute), 0))
    db.session.commit()

    db.session
    
    print('Temperatura: ' + temperatura + ' Hora: ' + str(hora.hour) + ':' + str(hora.minute))

    while(True):
        hora = datetime.now()
        nova_temperatura = str(objeto_porta.readline()).split("'")[1].split("\\")[0]
        #if int(float(temperatura)) != int(float(nova_temperatura)):
        temperatura = nova_temperatura
        db.session.add(models.Aquario(temperatura, str(hora.hour) + ':' + str(hora.minute), 0))
        db.session.commit()
        print('Temperatura: ' + temperatura + ' Hora: ' + str(hora.hour) + ':' + str(hora.minute))
        time.sleep(1)
    print(hora)
    objeto_porta.close()

