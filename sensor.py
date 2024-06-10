import serial
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import json

cred = credentials.Certificate('gookey.json')
firebase_admin.initialize_app(cred, {
	'databaseURL': 'https://safetytector-default-rtdb.firebaseio.com'
})

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
	if ser.in_waiting > 0:
		data = ser.readline().decode().strip()
		print('Received data:', data)

		try:
			sensor_data = json.loads(data)
			if 'status' in sensor_data and sensor_data['status'] == 415:
				ref = db.reference('/sensor_data')
				ref.update(sensor_data)
		except json.JSONDecodeError as e:
			print('Error parsing JSON: ', e)
