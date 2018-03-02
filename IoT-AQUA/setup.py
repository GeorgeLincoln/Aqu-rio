#Construção do Banco
from IoTApp import db, models

db.drop_all()
db.create_all()
print('done.')
