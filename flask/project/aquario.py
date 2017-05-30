# Autores: George Lincoln e William Vitorino
# Data: 19/05/2017
# Linguagem: Python
# Lendo da porta serial e escrevendo no arquivo
#Ctrl + c para o programa


#importando bibliotecas
from datetime import datetime
import serial
import time
import json


def media(valores):
    return sum(valores) / len(valores)

#Formatação para Json
def getTemperatura(porta):
    """Faz a leitura da temperatura."""
    # TODO: Ajeitar a leitura.
    return str(porta.readline()).split("'")[1].split("\\")[0]

#Formatação da data
def data_atual():
    return "{0}".format(datetime.today().strftime("%d-%m-%Y"))

def esperar():
    while(datetime.today().strftime("%S") != '00'):
        print(datetime.today().strftime("%X"))
        time.sleep(1)

def filtroTemperatura():
    """."""
    temps = []
    for i in range(12):
        # TODO: filtragem de dados do sensor de Temperatura TTC
        # Le os valores passados pelo arduino
        temperatura = 20
        try:
            temperatura = float(getTemperatura(objeto_porta))
            if temperatura > 40 or temperatura < 20:
                temperatura = float(getTemperatura(objeto_porta))
            temps.append(temperatura)
        except Exception as erro:
            print(erro)
            temps.append(20.0)
        print(temps)
        time.sleep(5)
    return temps

def readJson(arquivo):
    """Retorna os dados lidos do arquvo JSON."""
    try:
        with open(arquivo, "r") as file:
            return json.load(file)
    except FileNotFoundError:
        with open(arquivo, "w") as file:
            file.write(json.dumps([]))
        return readJson(arquivo)


def lerSensor():
    """."""
    leituras = readJson("leituras-%s.json" %datetime.today().strftime("%d-%m-%Y"))

    esperar()
    temperatura = filtroTemperatura()
    infos = {'temperatura' : media(temperatura),
            'horario' : datetime.today().strftime("%H:%M").rstrip("'")}
    #Guarda as informacoes na lista de Leituras
    leituras.append(infos)
    return leituras

#Define a porta e o baudrate usado
porta = '/dev/ttyACM0'
baud_rate = 9600

#Cria o objeto_porta, limpa o buffer da serial,
objeto_porta = serial.Serial(porta, baud_rate)
objeto_porta.flushInput();

dados = lerSensor()
#Abre o arquivo para escrever os dados
with open("leituras-%s.json" %datetime.today().strftime("%d-%m-%Y"), "w") as arduino:
    arduino.write(json.dumps(dados))
#Fecha a porta serial
objeto_porta.close()
