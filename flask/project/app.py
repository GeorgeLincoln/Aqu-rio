# Autores: George Lincoln e William Vitorino
# Data: 19/05/2017
# Linguagem: Python, Flask
# Cria graficos usando o Flask com dados coletados na porta serial

from flask import Flask
from flask import render_template
import pygal
from pygal import Config
from datetime import datetime
import json
from pygal import style

app = Flask(__name__)


@app.route("/")
def home():
    """configuracao do grafico"""
    with open("leituras-%s.json" %datetime.today().strftime("%d-%m-%Y"), 'r')as file:

        info = json.load(file)
        grafico = pygal.Bar(interpolate='cubic', style=style.BlueStyle(
                  value_font_family='googlefont:Raleway',
                  value_font_size=30, value_colors=('black',)),
                  print_values=True,
                  print_values_position='top')
        temperatura = [x['temperatura'] for x in info]
        grafico.x_labels = [x['horario'] for x in info]
        grafico.add("Temperatura", temperatura)
        grafico.render_to_file('static/images/grafico.svg')
        url_img = 'static/images/grafico.svg'


        return render_template('flask.html', image_url=url_img)
if __name__ == "__main__":
    app.run()
