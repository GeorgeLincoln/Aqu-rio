import pygal
from pygal.style import Style
from pygal import Config

from IoTApp import models

def obter_dados_sensores():
	Lista = models.Aquario.query.all()
	Lista.reverse()
	Lista = Lista[:30]
	Lista.reverse()
	return Lista

def grafico_temperatura():
	try:
		dados_sensores = obter_dados_sensores()
		config = Config()
		config.show_legend = False
		config.human_readable = True
		config.fill = True
		

		custom_style = Style(
			title_font_size=20,
			label_font_size=18,
			background='#ffffff',
			plot_background='#ffffff',
			foreground='#000000',
			foreground_strong='#000000',
			foreground_subtle='#000000',
			opacity='.6',
			opacity_hover='.9',
			transition='400ms ease-in',
			colors=('#3366cc', '#3366cc', '#E95355', '#E87653', '#E89B53'))

		line_chart = pygal.StackedLine(config, fill=True, style=custom_style, 
									   width=2000, x_title='Horário', y_title='Temperatura')
		line_chart.x_labels = list(map(str, [i.hora for i in dados_sensores]))
		#line_chart.add('', [0])
		line_chart.add('Temperatura', list(map(float, [i.temperatura for i in dados_sensores])))
		grafico = line_chart.render_data_uri()
		
		return dados_sensores, grafico

	except Exception as e:
		raise grafico_temperatura()