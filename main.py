from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List
import RegisterSN

app = FastAPI()

register = RegisterSN.RegisterSN()

class DataSN(BaseModel):
    timestamp: str
    type_of_sensor: str
    read: float

@app.post("/register_one/")
def register_one(data: DataSN):
    try:
        register.register_one(data.timestamp, data.type_of_sensor, data.read)
        return {"message": "Data registered successfully"}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.post("/register_many/")
def register_many(readings: List[DataSN]):
    try:
        data_list = [RegisterSN.DataSN(reading.timestamp, reading.type_of_sensor, reading.read) for reading in readings]
        register.register_many(data_list)
        return {"message": "Data registered successfully"}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.get("/highest_accumulate/{type_of_sensor}")
def highest_accumulate(type_of_sensor: str):
    result = register.highest_accumulate(type_of_sensor)
    if "highest_accumulated_value" in result:
        return result
    else:
        raise HTTPException(status_code=404, detail="Sensor type not found")
