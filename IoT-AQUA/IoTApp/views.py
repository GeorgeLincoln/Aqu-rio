from IoTApp import app, mngt
from flask import render_template, redirect, url_for, request

@app.route('/') 
@app.route('/home')
def home():
	return render_template('iot_index.html')


@app.route('/dashboard')
def dashboard():
	dados_sensores, grafico = mngt.grafico_temperatura()
	
	return render_template('iot_dashboard.html',  
		Lista = dados_sensores, 
		grafico=grafico)

@app.route('/aquario')
def aquario():
	return render_template('iot_aquario.html')