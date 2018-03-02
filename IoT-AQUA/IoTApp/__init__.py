from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_admin import Admin
from flask_admin.contrib.sqla import ModelView
#import secrets

app = Flask(__name__)

app.config['DEBUG'] = True
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///dbaqua.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True 
app.config['SECRET_KEY'] = 'PEIXE'
db = SQLAlchemy(app)

from IoTApp import views, models, mngt

admin = Admin(app, name='IoT-Aqua', template_mode='bootstrap3')
admin.add_view(ModelView(models.Aquario, db.session))