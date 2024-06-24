from fastapi.testclient import TestClient
from main import app, DataSN

client = TestClient(app)

def test_register_one():
    response = client.post("/register_one/", json={
        "timestamp": "2024-06-20 10:00:00",
        "type_of_sensor": "AIRQUALITY",
        "read": 50.0
    })
    assert response.status_code == 200
    assert response.json() == {"message": "Data registered successfully"}

def test_register_many():
    readings = [
        {"timestamp": "2024-06-20 10:00:01", "type_of_sensor": "AIRQUALITY", "read": 100.0},
        {"timestamp": "2024-06-20 10:00:02", "type_of_sensor": "AIRQUALITY", "read": -50.0},
        {"timestamp": "2024-06-20 10:00:03", "type_of_sensor": "AIRQUALITY", "read": 185.0},
        {"timestamp": "2024-06-20 10:00:04", "type_of_sensor": "AIRQUALITY", "read": 35.0}
    ]
    response = client.post("/register_many/", json=readings)
    assert response.status_code == 200
    assert response.json() == {"message": "Data registered successfully"}

def test_highest_accumulate():
    response = client.get("/highest_accumulate/AIRQUALITY")
    assert response.status_code == 200
    assert "highest_accumulated_value" in response.json()

def test_invalid_sensor_type():
    response = client.post("/register_one/", json={"timestamp": "2024-06-20 10:00:00", "type_of_sensor": "INVALID", "read": 50.0})
    assert response.status_code == 400
    assert "Invalid sensor type" in response.json()["detail"]