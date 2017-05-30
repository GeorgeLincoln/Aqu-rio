from flask import Flask
# Carregaremos os dados do arquivo JSON, 
# então precisaremos das bibliotecas
import pygal
import json

app = Flask(__name__)
 
@app.route("/")
def home():
    return "Tutsplus : Welcome to PyGal Charting Library !! "
 
if __name__ == "__main__":
    app.run()

@app.route("/bar")
def bar():
    #O código de gráficos estará aqui
    #Mostraremos Year no eixo X e Mark no eixo Y
    
    #Leiamos os dados JSON abrindo o arquivo 
    # em modo de leitura e carreguemos os dados.
    with open('bar.json','r') as bar_file:
    data = json.load(bar_file)
    chart = pygal.Bar()
    #dados para o eixo y
    mark_list = [x['mark'] for x in data]
    [x[year] for in data]
    chart.add('Annual Mark Liste', mark_list)
    #dados para o eixo x
    chart.x.labels = [x['year'] for x in data]

    #Agora, precisamos renderizar a imagem SVG do gráfico de barra em um arquivo. 
    # No Flask, os arquivos estáticos ficam numa pasta chamada static,
    # então criemo-no. Nele, criemos uma pasta images.
    # Adicionemos a seguinte linha de código para salvar a imagem SVG num arquivo.

    chart.render_to_file('static/images/bar_chart.svg')

    