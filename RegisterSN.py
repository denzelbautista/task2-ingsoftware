import RegisterSN

print(RegisterSN)

# Crear una instancia de la clase
register = RegisterSN.RegisterSN()

# Registrar una sola lectura
register.register_one("2024-06-20 10:00:00", "AIRQUALITY", 50.0)

# Registrar múltiples lecturas
readings = [
    RegisterSN.DataSN("2024-06-20 10:00:01", "AIRQUALITY", 100.0),
    RegisterSN.DataSN("2024-06-20 10:00:02", "AIRQUALITY", -180.0),
    RegisterSN.DataSN("2024-06-20 10:00:03", "AIRQUALITY", 185.0),
    RegisterSN.DataSN("2024-06-20 10:00:04", "AIRQUALITY", 35.0),
]
register.register_many(readings)

# Obtener el valor acumulado más alto para un tipo de sensor
result = register.highest_accumulate("AIRQUALITY")
print(result)