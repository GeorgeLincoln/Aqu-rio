#Script do Banco
from datetime import datetime
from flask_sqlalchemy import SQLAlchemy
from IoTApp import db

class Aquario (db.Model):
    id = db.Column(
        db.Integer,
        primary_key = True)

    temperatura = db.Column(db.String(80))
    hora = db.Column(db.String(10))
    alarme = db.Column(db.Integer)
    
    def __init__(self, temperatura, hora, alarme):
        self.temperatura = temperatura
        self.hora = hora
        self.alarme = alarme

    def __repr__(self):
        return '{}'.format(self.id)